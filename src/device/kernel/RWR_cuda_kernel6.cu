#pragma once

__global__ void RWR_init6 ( double* __restrict__ devExpVec0,
                                    const double r,
                                       const int V ) {
    const int id = Tid + blockIdx.x * blockDim.x;
    if (id < V) {
        devExpVec0[id] *= r;
    }
}

__global__ void RWR_CUDA6 (	int* __restrict__ devNodes,
                            int* __restrict__ devEdgeU,
                            int* __restrict__ devEdgeV,
                            int* __restrict__ devDegrees,
                         double* __restrict__ devExpVec1,
                         double* __restrict__ devExpVec2,
                         double* __restrict__ devExpVec0,
                                 const double r,
                                    const int E) {

    const int id = Tid + blockIdx.x * blockDim.x;
    //const int stride =  blockDim.x * gridDim.x;
    //for (int k = id ; k < E ; k+=stride) {
    if (id < E) {
        
        const int u = devEdgeU[id];
        const int v = devEdgeV[id];
        const double info_prop = (devExpVec1[u]/devDegrees[u])*(1-r);
        //printf("%d:(%d,%d|%d) ",id, u, v, devNodes[u]);

        atomicAdd(devExpVec2 + v, info_prop);
        //if(id % devNodes[u] == 0 || id == 0 )
        //    devExpVec2[u] += devExpVec0[u];
    }
}

__global__ void RWR_restart( double* __restrict__ devExpVec1,
                             double* __restrict__ devExpVec2,
                             double* __restrict__ devExpVec0,
                                    const int V,
                                    const int level) {
    const int id = Tid + blockIdx.x * blockDim.x;
    if (id < V) {
        devExpVec2[id] += devExpVec0[id];
        //if (level > 1)
        //    devExpVec2[id] -= devExpVec1[id];
    }
}

inline void cudaExpMatrix::cudaRWR_Kernel6(double r, int stop_step) {

    init_kernel6();

    std::cout << " (Kernel 6)" << '\n';
    //int gridDim = min(MAX_CONCURR_TH/BLOCKDIM , DIV(V, BLOCKDIM));
    int gridDimE = DIV(E, BLOCKDIM);
    int gridDimV = DIV(V, BLOCKDIM);

    timer::Timer<timer::DEVICE> TM;
    //int mean;
    double time = 0;

    for (int i = 0 ; i < M ; ++i) {
        int level = 0;

        int offset = i*V;
        cudaMemcpyAsync((void**) devExpVec0, expMatrix.eMatrix + offset, V * sizeof (double), cudaMemcpyHostToDevice);
        cudaMemcpyAsync((void**) devExpVec1, expMatrix.eMatrix + offset, V * sizeof (double), cudaMemcpyHostToDevice);
  
        TM.start();
        RWR_init6<<<gridDimV, BLOCKDIM >>> (devExpVec0, r, V);

        while( level++ < stop_step ) {

            cudaMemsetAsync((void**) devExpVec2, 0, V*sizeof(double));

            RWR_CUDA6<<<gridDimE, BLOCKDIM >>> (devNodes, devEdgeU, devEdgeV, devDegrees, 
                                               devExpVec1, devExpVec2, devExpVec0, 
                                               r, E);
            //cudaDeviceSynchronize();
            RWR_restart<<<gridDimV, BLOCKDIM >>>(devExpVec1, devExpVec2, devExpVec0, V, level);


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

void cudaExpMatrix::init_kernel6() {
    cudaMalloc(&devNodes,   (V + 1) * sizeof (int));
	cudaMalloc(&devEdgeU,    E * sizeof (int));
	cudaMalloc(&devEdgeV,    E * sizeof (int));
	cudaMalloc(&devDegrees,  V * sizeof (int));

	cudaMemcpy((void**) devNodes,   graph.nodes, (V + 1) * sizeof (int), cudaMemcpyHostToDevice);
	cudaMemcpy((void**) devEdgeU,   graph_edgeList.edgeU,  E * sizeof (int), cudaMemcpyHostToDevice);
	cudaMemcpy((void**) devEdgeV,   graph_edgeList.edgeV,  E * sizeof (int), cudaMemcpyHostToDevice);
	cudaMemcpy((void**) devDegrees, graph.degree, V * sizeof (int), cudaMemcpyHostToDevice);

	cudaMalloc(&devExpVec0, V * M * sizeof (double));
	cudaMalloc(&devExpVec1, V * M * sizeof (double));
	cudaMalloc(&devExpVec2, V * M * sizeof (double));

	cudaError("Graph Allocation");
}

