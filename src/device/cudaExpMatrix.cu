#include "cudaExpMatrix.cuh"

cudaExpMatrix::cudaExpMatrix(GraphCSR& _graph, ExpMatrix& _expMatrix) : graph(_graph), expMatrix(_expMatrix) {
	V = graph.V;
	E = graph.nnz;
    M = expMatrix.M;
}


#include "util/cuda_transpose.cu"

#include "kernel/RWR_cuda_kernel1.cu"
#include "kernel/RWR_cuda_kernel3.cu"
#include "kernel/RWR_cuda_kernel4.cu"
#include "kernel/RWR_cuda_kernel5.cu"

#include "cuda_RWR.cu"
