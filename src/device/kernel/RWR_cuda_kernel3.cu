#pragma once

__global__ void RWR_init3 ( double* __restrict__ devExpVec0,
                         const double r,
                            const int V ) {
    const int id = Tid + blockIdx.x * blockDim.x;
    if (id < V) {
        devExpVec0[id] *= r;
    }
}

__global__ void RWR_CUDA3 (	int* __restrict__ devNodes,
                            int* __restrict__ devEdges,
                            int* __restrict__ devDegrees,
                         double* __restrict__ devExpVec1,
                         double* __restrict__ devExpVec2,
                         double* __restrict__ devExpVec0,
                                 const double r,
                                    const int V,
                                    const int VWARP_SZ) {

    const int id = Tid + blockIdx.x * blockDim.x;
    const int stride =  blockDim.x * gridDim.x / VWARP_SZ;
    //const int stride =  DIV(V, VWARP_SZ);
    const int vid = id / VWARP_SZ;
    const int mod = Tid & (VWARP_SZ-1);
    for (int k = vid ; k < V ; k+=stride) {
        const int start = devNodes[k];
        const int end = devNodes[k+1];
        double sum = 0;
        devExpVec2[k] = 0;
        for (int i = start + mod ; i < end ; i+=VWARP_SZ) {
            const int e = devEdges[i];
            sum += devExpVec1[e]/devDegrees[e];
        }
        //atomicAdd(devExpVec2 + k, sum);
        atomicAdd(devExpVec2 + k, sum * (1-r));
        //devExpVec2[id] = sum * (1-r) + devExpVec0[id];
        if(mod == 0)
            devExpVec2[k] += devExpVec0[k];
            //devExpVec2[k] *= (1-r);  
    }
//    int id = Tid + blockIdx.x * blockDim.x;
//    if (id < V) {
//        double sum = 0;
//        for (int i = devNodes[id] ; i < devNodes[id+1] ; ++i) {
//            int e = devEdges[i];
//            sum += devExpVec1[e]/devDegrees[e];
//        }
//        devExpVec2[id] = sum * (1-r) + devExpVec0[id];
//    }
}

inline void cudaExpMatrix::cudaRWR_Kernel3(double r, int stop_step) {

    init_kernel3();

    std::cout << " (Kernel 3)" << '\n';
    //int gridDim = min(MAX_CONCURR_TH/BLOCKDIM , DIV(V, BLOCKDIM));
    int gridDim = DIV(V, BLOCKDIM);

    timer::Timer<timer::DEVICE> TM;
    //int mean;
    double time = 0;

    int size = 4; //virtual warp of 4 give best result

    for (int i = 0 ; i < M ; ++i) {
        int level = 0;

        int offset = i*V;
        cudaMemcpyAsync((void**) devExpVec0, expMatrix.eMatrix + offset, V * sizeof (double), cudaMemcpyHostToDevice);
        cudaMemcpyAsync((void**) devExpVec1, expMatrix.eMatrix + offset, V * sizeof (double), cudaMemcpyHostToDevice);
        cudaMemsetAsync((void**) devExpVec2, 0, V*sizeof(double));
  
        TM.start();
        RWR_init3<<<gridDim, BLOCKDIM >>> (devExpVec0, r, V);

        while( level++ < stop_step ) {

            RWR_CUDA3<<<gridDim, BLOCKDIM >>> (devNodes, devEdges, devDegrees, 
                                               devExpVec1, devExpVec2, devExpVec0, 
                                               r, V, size);
            //cudaDeviceSynchronize();

            double* tmp = devExpVec1;
            devExpVec1 = devExpVec2;
            devExpVec2 = tmp;

        } 
        TM.stop();
        time += TM.duration();
        cudaMemcpyAsync(expMatrix.eMatrix + offset, devExpVec1, V * sizeof(double), cudaMemcpyDeviceToHost);
        //std::cout << '\n';
        //for (int j = 0 ; j < V ; ++j) {
        //    std::cout << std::setprecision(5) << expMatrix.eMatrix[j + offset] << ',';
        //}
    }
    std::cout <<"time no data copy: " << time << '\n';
}

void cudaExpMatrix::init_kernel3() {
    cudaMalloc(&devNodes,   (V + 1) * sizeof (int));
	cudaMalloc(&devEdges,    E * sizeof (int));
	cudaMalloc(&devDegrees,  V * sizeof (int));

	cudaMemcpy((void**) devNodes,   graph.nodes, (V + 1) * sizeof (int), cudaMemcpyHostToDevice);
	cudaMemcpy((void**) devEdges,   graph.edges,  E * sizeof (int), cudaMemcpyHostToDevice);
	cudaMemcpy((void**) devDegrees, graph.degree, V * sizeof (int), cudaMemcpyHostToDevice);

	cudaMalloc(&devExpVec0, V * M * sizeof (double));
	cudaMalloc(&devExpVec1, V * M * sizeof (double));
	cudaMalloc(&devExpVec2, V * M * sizeof (double));

	cudaError("Graph Allocation");
}

