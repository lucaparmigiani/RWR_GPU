#pragma once
int num_block;
int BLOCK_DIM;

void cudaExpMatrix::cudaRWR_N(int nof_tests, double r, int stop_step, Kernel k) {
    switch (k) {
        case K1:
		    this->cudaRWR_Kernel1(r, stop_step);
            break;
        case K3:
            this->cudaRWR_Kernel3(r, stop_step);
           break;
        case K3_5:
            cudaDeviceProp devProp;
            cudaGetDeviceProperties(&devProp, 0);
            cudaError("Device Info");
            size_t sharedMemSizePerBlock = devProp.sharedMemPerBlock;
            size_t sharedMemSizePerSM = devProp.sharedMemPerMultiprocessor;
            size_t numSM = devProp.major;
            const int numPerSM = sharedMemSizePerSM/sharedMemSizePerBlock;

            num_block = numPerSM*numSM;
            BLOCK_DIM = MaxBlockDim;
#if   SMEM_KERNEL==0
            this->cudaRWR_Kernel3(r, stop_step);
            //this->cudaRWR_Kernel1(r, stop_step);
#elif SMEM_KERNEL==1
            if(sharedMemSizePerBlock/(numPerSM*2) - 10000 > this->V)
                this->cudaRWR_Kernel5(r, stop_step);
            else
                this->cudaRWR_Kernel3(r, stop_step);
            //this->cudaRWR_Kernel4(r, stop_step);
#endif
            break;
    }
    cudaError("RWR Kernel N");

	std::cout	<< std::setprecision(1) << std::fixed << std::endl
				<< "\t    Number of TESTS:  " << nof_tests << std::endl;

	//if (COUNT_DUP && nof_tests == 1) {
	//	int duplicates;
	//	cudaMemcpyFromSymbol(&duplicates, duplicateCounter, sizeof(int));
	//	std::cout	<< "\t     Duplicates:  " << duplicates << std::endl << std::endl;
	//}
}

void cudaExpMatrix::reset_gpu(){
    cudaFree(this->devNodes);
    cudaFree(this->devEdges);
    cudaFree(this->devDegrees);
	cudaFree(this->devExpVec0);
	cudaFree(this->devExpVec1);
	cudaFree(this->devExpVec2);
}

// ---------------------k AUXILARY FUNCTION ---------------------------------------------

inline void cudaExpMatrix::FrontierDebug(int FrontierSize, bool check) {
    int* F = new int[FrontierSize];
    cudaMemcpy( F, devF, FrontierSize * sizeof(int), cudaMemcpyDeviceToHost);
    std::cout << "Frontier content: ";
    for (int i = 0 ; i < FrontierSize ; ++i) {
        std::cout << F[i] << ' ';
    }
    std::cout << '\n';

    if(check) {
        std::sort (F,F+FrontierSize); 
        for (int i = 0 ; i < FrontierSize-1 ; ++i) {
            if(F[i] == F[i+1]){
                std::cout << "Well...that's bad" << '\n';
                return;
            }
        }
    }
}
