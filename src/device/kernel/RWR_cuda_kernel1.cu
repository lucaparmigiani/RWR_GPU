#pragma once

__device__ int counter;

__global__
void RWR_init ( double* __restrict__ devExpVec0,
                   int* __restrict__ devF,
                           const int devFSize,
                        const double r,
                               int* devInF) {
    int id = Tid + blockIdx.x * blockDim.x;
    if (id < devFSize) {
        int v = devF[id];
        devInF[v] = 1;
        devExpVec0[v] *= r;
    }
}

__global__
void RWR_CUDA (	int* __restrict__ devNodes,
				int* __restrict__ devEdges,
                int* __restrict__ devDegrees,
                int* __restrict__ devF,
             double* __restrict__ devExpVec1,
             double* __restrict__ devExpVec2,
				        const int devFSize,
                            int* devInF) {

    int id = Tid + blockIdx.x * blockDim.x;
    if (id < devFSize) {
        int localChecker;
        int v = devF[id];
        //devExpVec2[v] -= devExpVec1[v];
        atomicAdd(&devExpVec2[v], -devExpVec1[v]);
        double prop = devExpVec1[v]/devDegrees[v];
        for (int i = devNodes[v] ; i < devNodes[v+1] ; ++i) {
            int e = devEdges[i];
            //devExpVec2[e] += prop;
            atomicAdd(&devExpVec2[e], prop);
            localChecker = *(volatile int*)&devInF[e];
            if (!atomicCAS(&devInF[e], localChecker, 1)) {
                int index = atomicAdd(&counter, 1);
                devF[index] = e;
            }
        }
    }
}

__global__
void RWR_mul ( double* __restrict__ devExpVec0,
               double* __restrict__ devExpVec1,
               double* __restrict__ devExpVec2,
                  int* __restrict__ devF,
                          const int devFSize,
                       const double r) {

    int id = Tid + blockIdx.x * blockDim.x;
    if (id < devFSize) {
        int v = devF[id];
        double tmp = devExpVec2[v]*(1-r) + devExpVec0[v];
        devExpVec2[v] = tmp;
        devExpVec1[v] = tmp;
    }
}

inline void cudaExpMatrix::cudaRWR_Kernel1(double r, int stop_step) {

    std::cout << " (Kernel 1)" << '\n';
    init_kernel1();

    for (int i = 0 ; i < M ; ++i) {

        //Search sources
        int* sources = new int[V];
        int nof_sources = 0;
        for (int j = 0 ; j < V ; j++) {
            double tmp = expMatrix.eMatrix[i*V + j];
            if (tmp != 0) {
                sources[nof_sources++] = j;
            }
        }
        
		reset_kernel1(sources, nof_sources);

        int FrontierSize = nof_sources;
        cudaMemcpyToSymbol(counter, &FrontierSize, sizeof (int));
        int level = 0;

        int offset = i*V;
        cudaMemcpyAsync((void**) devExpVec0, expMatrix.eMatrix + offset, V * sizeof (double), cudaMemcpyHostToDevice);
        cudaMemcpyAsync((void**) devExpVec1, expMatrix.eMatrix + offset, V * sizeof (double), cudaMemcpyHostToDevice);
        cudaMemcpyAsync((void**) devExpVec2, expMatrix.eMatrix + offset, V * sizeof (double), cudaMemcpyHostToDevice);

  
        if(FrontierSize) {
            //int gridDim = min(MAX_CONCURR_TH/BLOCKDIM , DIV(FrontierSize, BLOCKDIM));
            int gridDim = DIV(FrontierSize, BLOCKDIM);
            RWR_init<<<gridDim, BLOCKDIM >>>
                (devExpVec0, devF, FrontierSize, r, devInF);

            while( level < stop_step ) {

                RWR_CUDA<<<gridDim, BLOCKDIM >>>
                    (devNodes, devEdges, devDegrees, devF, devExpVec1, devExpVec2, FrontierSize, devInF);

                cudaMemcpyFromSymbol(&FrontierSize, counter, sizeof (int));
                //cudaMemcpy(FrontierSize, counter, sizeof (int), cudaMemcpyDeviceToHost);
                gridDim = min(MAX_CONCURR_TH/BLOCKDIM , DIV(FrontierSize, BLOCKDIM));


                RWR_mul<<<gridDim, BLOCKDIM >>>
                    (devExpVec0, devExpVec1, devExpVec2, devF, FrontierSize, r);

                level++;
            } 
            cudaMemcpyAsync(expMatrix.eMatrix + i*V, devExpVec2, V * sizeof(double), cudaMemcpyDeviceToHost);
        }
    }

    cudaFree(devF);
    cudaFree(devInF);
    //reset_gpu();
}

void cudaExpMatrix::reset_kernel1(const int Sources[], int nof_sources) {
	cudaMemcpy(devF, Sources, nof_sources * sizeof(int), cudaMemcpyHostToDevice);

    cudaMalloc((void **)&devInF, V*sizeof(int));
    cudaMemset(devInF, 0, V*sizeof(int));

	cudaError("Graph Reset");
}

void cudaExpMatrix::init_kernel1() {
    cudaMalloc(&devNodes,   (V + 1) * sizeof (int));
	cudaMalloc(&devEdges,    E * sizeof (int));
	cudaMalloc(&devDegrees,  V * sizeof (int));

	cudaMemcpy((void**) devNodes,   graph.nodes, (V + 1) * sizeof (int), cudaMemcpyHostToDevice);
	cudaMemcpy((void**) devEdges,   graph.edges,  E * sizeof (int), cudaMemcpyHostToDevice);
	cudaMemcpy((void**) devDegrees, graph.degree, V * sizeof (int), cudaMemcpyHostToDevice);

	cudaMalloc(&devExpVec0, V * sizeof (double));
	cudaMalloc(&devExpVec1, V * sizeof (double));
	cudaMalloc(&devExpVec2, V * sizeof (double));

	cudaError("Graph Allocation");
	
	// --------------- Frontier Allocation -------------------

	size_t free, total;
	cudaMemGetInfo(&free, &total);
    size_t frontierSize = (free) - 20000 * 1024;

	cudaMalloc(&devF, frontierSize);
	allocFrontierSize = frontierSize / sizeof(int);

	cudaError("Graph Frontier Allocation");
}
