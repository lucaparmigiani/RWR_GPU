#include "cudaExpMatrix.cuh"

cudaExpMatrix::cudaExpMatrix(GraphCSR& _graph, ExpMatrix& _expMatrix) : graph(_graph), expMatrix(_expMatrix) {
	V = graph.V;
	E = graph.nnz;
    M = expMatrix.M;
}

cudaExpMatrix::cudaExpMatrix(GraphCSR& _graph, ExpMatrix& _expMatrix, GraphEdgeList& _graph_edgeList) : graph(_graph), expMatrix(_expMatrix), graph_edgeList(_graph_edgeList) {
	V = graph.V;
	E = graph.nnz;
    M = expMatrix.M;
}


#include "util/cuda_transpose.cu"

#include "kernel/RWR_cuda_kernel1.cu"
#include "kernel/RWR_cuda_kernel3.cu"
#include "kernel/RWR_cuda_kernel4.cu"
#include "kernel/RWR_cuda_kernel5.cu"
#include "kernel/RWR_cuda_kernel6.cu"

#include "cuda_RWR.cu"
