#pragma once

const int SMemMargin = 10000;
extern int num_block;
extern int BLOCK_DIM;

__global__ void RWR_init5 ( double* __restrict__ devExpVec0,
                         const double r,
                            const int V ) {
    const int id = Tid + blockIdx.x * V;
    const int stride = blockDim.x;
    for (int i = id ; i < V*(blockIdx.x+1) ; i+=stride) {
        devExpVec0[i] *= r;
    }
}

__global__ void RWR_CUDA5 (	int* __restrict__ devNodes,
                            int* __restrict__ devEdges,
                            int* __restrict__ devDegrees,
                         double* __restrict__ devExpVec1,
                         double* __restrict__ devExpVec2,
                         double* __restrict__ devExpVec0,
                                 const double r,
                                    const int V,
                                    const int M,
                                    const int VWARP_SZ) {

    __shared__ double vec1SMem[(SMem_Per_SM/4)-SMemMargin];
    __shared__ double vec2SMem[(SMem_Per_SM/4)-SMemMargin];

    const int vid = (Tid / VWARP_SZ);
    const int stride =  blockDim.x / VWARP_SZ;
    const int mod = Tid & (VWARP_SZ-1);
    const int offset = blockIdx.x*V;

    if (vid + offset < V * M) {
        for (int k = vid , m = vid + offset; k < V ; k+=stride , m+=stride) {
            vec1SMem[k] = devExpVec1[m];
        }
        __syncthreads();


        for (int k = vid , m = vid + offset; k < V ; k+=stride , m+=stride) {
            const int start = devNodes[k];
            const int end = devNodes[k+1];
            double sum = 0;
            vec2SMem[k] = 0;
            for (int i = start + mod ; i < end ; i+=VWARP_SZ) {
                const int e = devEdges[i];
                sum += vec1SMem[e]/devDegrees[e + offset];
            }
            atomicAdd(vec2SMem + k, sum * (1-r));
            if(mod == 0)
                devExpVec2[m] = vec2SMem[k] + devExpVec0[m];
        }
    }
}

inline void cudaExpMatrix::cudaRWR_Kernel5(double r, int stop_step) {

    init_kernel5();

    std::cout << " (Kernel 5)" << '\n';
    //int num_block = min(MAX_CONCURR_TH/BLOCKDIM , DIV(V, BLOCKDIM));
    //int num_block = DIV(V, BLOCKDIM);

    timer::Timer<timer::DEVICE> TM;
    double time = 0;

    //int size = MIN_V(16, 32);
    int size = 4; //virtual warp of 4 give best result

    for (int i = 0 ; i < M ; i+=num_block) {
        int level = 0;

        int offset = i*V;
        int margin = MIN_V(M*V, V*num_block);
        
        cudaMemcpyAsync((void**) devExpVec0, expMatrix.eMatrix + offset, margin * sizeof (double), cudaMemcpyHostToDevice);
        cudaMemcpyAsync((void**) devExpVec1, expMatrix.eMatrix + offset, margin * sizeof (double), cudaMemcpyHostToDevice);
        cudaMemsetAsync((void**) devExpVec2, 0, margin * sizeof(double));
        //cudaMemcpyAsync((void**) devExpVec2, expMatrix.eMatrix + offset, V * sizeof (double), cudaMemcpyHostToDevice);
  
        TM.start();
        RWR_init5<<<num_block, BLOCK_DIM >>> (devExpVec0, r, V);
        cudaDeviceSynchronize();

        while( level < stop_step ) {

            RWR_CUDA5<<<num_block, BLOCK_DIM >>> (devNodes, devEdges, devDegrees, 
                                               devExpVec1, devExpVec2, devExpVec0, 
                                               r, V, M, size);
            //cudaDeviceSynchronize();

            double* tmp = devExpVec1;
            devExpVec1 = devExpVec2;
            devExpVec2 = tmp;

            level++;
        } 
        //std::cout << i << '\n';
        TM.stop();
        time += TM.duration();
        cudaMemcpyAsync(expMatrix.eMatrix + offset, devExpVec1, margin * sizeof(double), cudaMemcpyDeviceToHost);
    }
    std::cout <<"time no data copy: " << time << '\n';
}

void cudaExpMatrix::init_kernel5() {
    cudaMalloc(&devNodes,   (V + 1) * sizeof (int));
	cudaMalloc(&devEdges,    E * sizeof (int));
	cudaMalloc(&devDegrees,  V * sizeof (int));

	cudaMemcpy((void**) devNodes,   graph.nodes, (V + 1) * sizeof (int), cudaMemcpyHostToDevice);
	cudaMemcpy((void**) devEdges,   graph.edges,  E * sizeof (int), cudaMemcpyHostToDevice);
	cudaMemcpy((void**) devDegrees, graph.degree, V * sizeof (int), cudaMemcpyHostToDevice);

    cudaDeviceProp devProp;
	cudaGetDeviceProperties(&devProp, 0);
	cudaError("Device Info");
    size_t sharedMemSizePerBlock = devProp.sharedMemPerBlock;
    size_t sharedMemSizePerSM = devProp.sharedMemPerMultiprocessor;
    size_t numSM = devProp.major;
    int numPerSM = sharedMemSizePerSM/sharedMemSizePerBlock;
    num_block = numPerSM*numSM;

    BLOCK_DIM = MaxBlockDim;

	cudaMalloc(&devExpVec0, V * M * num_block * sizeof (double));
	cudaMalloc(&devExpVec1, V * M * num_block * sizeof (double));
	cudaMalloc(&devExpVec2, V * M * num_block * sizeof (double));

	cudaError("Graph Allocation");
}

