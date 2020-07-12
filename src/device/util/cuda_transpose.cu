#pragma once

const int BLOCK_SIZE_X = 32;
const int BLOCK_SIZE_Y = 32;

__global__
void matrixTransposeKernelShM(const double* d_matrix_in,
                                    double* d_matrix_out,
                                       int  N, int M ) {

    __shared__ int sh_matrix[BLOCK_SIZE_X*BLOCK_SIZE_Y];

    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if(x < N && y < M){
        sh_matrix[threadIdx.x +  threadIdx.y * BLOCK_SIZE_Y]= d_matrix_in[x*M + y];

        __syncthreads();
        d_matrix_out[y*N + x] = sh_matrix[threadIdx.x +  threadIdx.y * BLOCK_SIZE_Y];
    }
}

void cudaExpMatrix::transpose(){
    double *d_matrix_out, *d_matrix_in;
    std::cout << "\nTransposing expression matrix...";
    cudaMalloc( &d_matrix_in , V*M * sizeof(double));
    cudaMalloc( &d_matrix_out, M*V * sizeof(double));

    cudaMemcpy( d_matrix_in, expMatrix.eMatrix, V*M * sizeof(double), cudaMemcpyHostToDevice);

    cudaError("Matrix Allocation Trasposition");


    dim3 num_blocks(V/BLOCK_SIZE_X, V/BLOCK_SIZE_Y, 1);
    if (V%BLOCK_SIZE_X) {
        num_blocks.x++;
        num_blocks.y++;
    }
    dim3 block_size(BLOCK_SIZE_X , BLOCK_SIZE_Y, 1);

    matrixTransposeKernelShM<<< num_blocks, block_size >>>(d_matrix_in, d_matrix_out, V, M);

    cudaError("Matrix Trasposition");
    //double* h_matrix_tmp = new double[M*V];
    cudaMemcpy( expMatrix.eMatrix, d_matrix_out, M*V*sizeof(double), cudaMemcpyDeviceToHost);

    cudaError("Matrix Trasposition copy output");

    cudaFree( d_matrix_in  );
    cudaFree( d_matrix_out );
    std::cout << "Complete" << '\n';

    //for (int i = 0 ; i < M ; ++i) {
    //    for (int j = 0 ; j < V ; ++j) {
    //        std::cout << h_matrix_tmp[i*V + j] << ' ';
    //    }
    //    std::cout << '\n';
    //}
}
