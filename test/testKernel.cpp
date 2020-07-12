#include "test.h"

namespace Testing {
    bool compareDevDev(cudaExpMatrix& devExpMatrixK1, cudaExpMatrix& devExpMatrixK2, 
                       bool printRes){
        int N = devExpMatrixK1.expMatrix.N;
        int M = devExpMatrixK1.expMatrix.M;
        
        //if(printRes)
        //    printPropExpMat(devExpMatrixK1, devExpMatrixK2);

        for (int i = 0 ; i < N ; ++i) {
            for (int j = 0 ; j < M ; ++j) {
                if(std::abs(devExpMatrixK1.expMatrix.eMatrix[j*N + i] - 
                            devExpMatrixK2.expMatrix.eMatrix[j*N+ i]) 
                   > EPSILON){
                    std::cout << ">< Error: \t\t" 
                             << "kernel1: "  << std::setprecision(5) << 
                             devExpMatrixK1.expMatrix.eMatrix[j*N + i] << '\t'
                             << "kernel2: "  << std::setprecision(5) << 
                             devExpMatrixK2.expMatrix.eMatrix[j*N + i] << '\t'
                             << "pos: [" << j << ", "<< i << "]\n";
                    return false;
                }
            }
        }
        return true;


        }

    void testRandomKernel( int N, int M, int avg_degree, double densityEM,
                           Kernel k1, Kernel k2, int stop_step, double r ) {

        Timer<DEVICE>   TM_device1;
        Timer<DEVICE>   TM_device2;

        //==========================================================================
        // INITIALIZATION
        //==========================================================================
        // -------------------------------------------------------------------------
        // INIT RANDOM GRAPH
        // -------------------------------------------------------------------------
        std::vector<int2> edgeList = Graph::randomEdgeList(N, avg_degree);
        GraphCSR graph_csr = GraphCSR(N, edgeList);
        graph_csr.info();
        //graph_csr.print();
        graph_csr.degreeAnalisys();
        // -------------------------------------------------------------------------
        // INIT RANDOM HOST EXPRESSION MATRIX
        // -------------------------------------------------------------------------
        ExpMatrix h_expMatrix =  ExpMatrix::randomExpMatrix(N, M, densityEM);
        h_expMatrix.info();
        // -------------------------------------------------------------------------
        // INIT DEVICE EXPRESSION MATRIX
        // -------------------------------------------------------------------------
        cudaExpMatrix devExpMatrixK1(graph_csr, h_expMatrix);
        devExpMatrixK1.transpose();
        cudaExpMatrix devExpMatrixK2(graph_csr, h_expMatrix);
        devExpMatrixK2.transpose();

        //==========================================================================
        // CUDA PROPAGATION KERNEL k1
        //==========================================================================
        std::cout << "\nRunning RWR cuda";

        TM_device1.start();
        devExpMatrixK1.cudaRWR_N(1, r, stop_step, k1);
        TM_device1.stop();

        TM_device1.print("RWR cuda: ");
        
        //==========================================================================
        // CUDA PROPAGATION KERNEL k2
        //==========================================================================
        std::cout << "\nRunning RWR cuda";

        TM_device2.start();
        devExpMatrixK2.cudaRWR_N(1, r, stop_step, k2);
        TM_device2.stop();

        TM_device2.print("RWR cuda: ");

        //=========================================================================
        // COMPARE
        //=========================================================================
        if (compareDevDev(devExpMatrixK1, devExpMatrixK2)) {
            std::cout << "<> Correct" << '\n';
            std::cout << std::setprecision(1)
                  << "Speedup: " << TM_device1.duration() / TM_device2.duration()
                  << "x\n\n";
        }

    }


    void Kernel1VsKernel3(){
        int nof_nodes[] {1000, 2000, 5000, 10000};
        float densityGraph[] {0.2, 0.5, 0.8};
        double densityEM[] {0.1, 0.5, 0.8};
        int M = 120;
        for (int i = 0; i < sizeof(nof_nodes)/sizeof(int); ++i) {
            for (int j = 0; j < sizeof(densityGraph)/sizeof(float); ++j) {
                for (int k = 0; k < sizeof(densityEM)/sizeof(double); ++k) {
                    int N = nof_nodes[i];
                    int avg_degree = (densityGraph[j]) * ((N-1)/2);
                    double dEM = densityEM[k];
                    testRandomKernel(N, M, avg_degree, dEM, Kernel::K1, Kernel::K3);
                }
            }
        }
    }

    void Kernel3VsKernel5(){
        int nof_nodes[] {1000, 2000};
        float densityGraph[] {0.2, 0.5, 0.8};
        double densityEM[] {0.1, 0.5, 0.8};
        int M = 120;
        for (int i = 0; i < sizeof(nof_nodes)/sizeof(int); ++i) {
            for (int j = 0; j < sizeof(densityGraph)/sizeof(float); ++j) {
                for (int k = 0; k < sizeof(densityEM)/sizeof(double); ++k) {
                    int N = nof_nodes[i];
                    int avg_degree = (densityGraph[j]) * ((N-1)/2);
                    double dEM = densityEM[k];
                    std::cout << "Nodes: "<< N << '\n';
                    std::cout << "Density graph: "<< densityGraph[j]<< '\n';
                    std::cout << "Density exp matrix: "<< dEM << '\n';
                    testRandomKernel(N, M, avg_degree, dEM, Kernel::K1, Kernel::K3);
                    cudaDeviceSynchronize();
                    std::cout << "------------------------------------------" << '\n';
                }
            }
        }
    }

    //void VirtualWarp(){

    //}
} 
