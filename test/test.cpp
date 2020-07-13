#include "test.h"

namespace Testing {
    void testRandom( int N, int M, int avg_degree, double densityEM,
                     Kernel k, int stop_step, double r ) {

        Timer<DEVICE> TM_device;
        Timer<HOST>   TM_host;

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
        cudaExpMatrix devExpMatrix(graph_csr, h_expMatrix);
        devExpMatrix.transpose();

        //==========================================================================
        // HOST PROPAGATION
        //==========================================================================
        TM_host.start();
        h_expMatrix.RWR(r, stop_step, &graph_csr);
        TM_host.stop();
        
        TM_host.print("RWR host:   ");

        //==========================================================================
        // CUDA PROPAGATION
        //==========================================================================
        std::cout << "\nRunning RWR cuda";

        TM_device.start();
        devExpMatrix.cudaRWR_N(1, r, stop_step, k);
        TM_device.stop();

        TM_device.print("RWR cuda: ");

        //=========================================================================
        // COMPARE
        //=========================================================================
        if (compareHostDev(devExpMatrix, h_expMatrix)) {
            std::cout << "<> Correct" << '\n';
            std::cout << std::setprecision(1)
                  << "Speedup: " << TM_host.duration() / TM_device.duration()
                  << "x\n\n";
        }

    }

    void testInput(const char* file_graph, const char* file_expMat, int stop_step, double r ) {
        Timer<DEVICE> TM_device;
        Timer<HOST>   TM_host;

        //==========================================================================
        // INITIALIZATION
        //==========================================================================
        int N,M;
        // -------------------------------------------------------------------------
        // INIT INPUT GRAPH
        // -------------------------------------------------------------------------
        int nnz;
        //readUtil::countLines(F_GRAPH_COO, nnz);
        readUtil::readGraphHeader(file_graph, N, nnz);
        GraphCSR graph_csr(N, nnz);
        readUtil::readGraph(file_graph, &graph_csr);
        graph_csr.info();
        graph_csr.ToCSR();
        //graph_csr.degreeAnalisys();
        //graph_csr.print();
        // -------------------------------------------------------------------------
        // INIT INPUT HOST EXPRESSION MATRIX
        // -------------------------------------------------------------------------
        readUtil::readExpMatrixHeader(file_expMat, N, M);
        ExpMatrix h_expMatrix =  ExpMatrix(N, M);
        readUtil::readExpMatrix(file_expMat, h_expMatrix);
        h_expMatrix.info();
        // -------------------------------------------------------------------------
        // INIT DEVICE EXPRESSION MATRIX
        // -------------------------------------------------------------------------
        cudaExpMatrix devExpMatrix(graph_csr, h_expMatrix);
        devExpMatrix.transpose();

        //==========================================================================
        // HOST PROPAGATION
        //==========================================================================
        TM_host.start();
        h_expMatrix.RWR(r, stop_step, &graph_csr);
        TM_host.stop();
        
        TM_host.print("RWR host:   ");

        //==========================================================================
        // CUDA PROPAGATION
        //==========================================================================
        std::cout << "\nRunning RWR cuda";

        TM_device.start();
        devExpMatrix.cudaRWR_N(1, r, stop_step);
        TM_device.stop();

        TM_device.print("RWR cuda: ");

        //=========================================================================
        // COMPARE
        //=========================================================================

        if (compareHostDev(devExpMatrix, h_expMatrix)) {
            std::cout << "<> Correct" << '\n';
            std::cout << std::setprecision(1)
                  << "Speedup: " << TM_host.duration() / TM_device.duration()
                  << "x\n\n";
        }

    }


    bool compareHostDev(cudaExpMatrix& devExpMatrix, ExpMatrix& h_expMatrix, bool printRes) {
        int N = h_expMatrix.N;
        int M = h_expMatrix.M;
        
        if(printRes)
            printPropExpMat(devExpMatrix, h_expMatrix);

        for (int i = 0 ; i < h_expMatrix.N ; ++i) {
            for (int j = 0 ; j < h_expMatrix.M ; ++j) {
                if(std::abs(devExpMatrix.expMatrix.eMatrix[j*N + i] - h_expMatrix.eMatrix[i*M+ j]) 
                   > EPSILON){
                    std::cout << ">< Error: \t\t" 
                             << "cuda: "  << std::setprecision(5) << 
                             devExpMatrix.expMatrix.eMatrix[j*N + i] << '\t'
                             << "host: "  << std::setprecision(5) << 
                             h_expMatrix.eMatrix[i*M+j] << '\n'
                             << "pos: [" << j << ", "<< i << "]\n";
                    return false;
                }
            }
        }
        return true;
    }

    void printPropExpMat(cudaExpMatrix& devExpMatrix, ExpMatrix& h_expMatrix){
        int N = h_expMatrix.N;
        int M = h_expMatrix.M;
        
        for (int i = 0 ; i < N ; ++i) {
            for (int j = 0 ; j < M ; ++j) {
                std::cout <<std::setprecision(5) <<h_expMatrix.eMatrix[i*M + j]<< ' ';
            }
            std::cout <<'\n';
        }
        std::cout <<'\n';

        for (int j = 0 ; j < M ; ++j) {
            for (int i = 0 ; i < N ; ++i) {
                std::cout <<std::setprecision(5)<<devExpMatrix.expMatrix.eMatrix[j*N + i]<< ' ';
            }
            std::cout <<'\n';
        }
    }

    void multipleTest(Kernel K) {
        //int nof_nodes[] {1000, 5000, 10000, 20000};
        //float densityGraph[] {0.01, 0.1, 0.2, 0.5, 0.7, 0.9};
        //double densityEM[] {0.01, 0.1, 0.2, 0.5, 0.7, 0.9};
        //int nof_nodes[] {1000, 2000, 5000, 10000, 20000};
        int nof_nodes[] {2000, 5000};
        float densityGraph[] {0.2};
        double densityEM[] {0.1};
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
                    testRandom(N, M, avg_degree, dEM, K);
                    cudaDeviceSynchronize();
                    std::cout << "------------------------------------------" << '\n';
                }
            }
        }
    }

    void bioTest() {
        Timer<DEVICE> TM_device;
        Timer<HOST>   TM_host;

        //ecoli
        //const char* file_graph = "/home/luca/University/current/architettura/RWR-GPU/RWR/data/bio/ecoli.ppi.txt";
        //Human
        //const char* file_graph = "/home/luca/University/current/architettura/RWR-GPU/RWR/data/bio/human.ppi.txt";
        //
        //const char* file_graph = "/home/luca/University/current/architettura/RWR-GPU/RWR/data/bio/COG.txt";
        //Bio wormNet
        const char* file_graph = "/home/luca/University/current/architettura/RWR-GPU/RWR/data/bio/bio-wormNet.edges";
        int stop_step = 30;
        double r = 0.6;
        //==========================================================================
        // INITIALIZATION
        //==========================================================================
        int N,M;
        // -------------------------------------------------------------------------
        // INIT INPUT GRAPH
        // -------------------------------------------------------------------------
        int nnz;
        //readUtil::countLines(F_GRAPH_COO, nnz);
        readUtil::readGraphHeader(file_graph, N, nnz);
        GraphCSR graph_csr(N, nnz);
        readUtil::readGraph(file_graph, &graph_csr);
        graph_csr.info();
        graph_csr.ToCSR();
        graph_csr.degreeAnalisys();
        //graph_csr.print();
        // -------------------------------------------------------------------------
        // INIT RANDOM HOST EXPRESSION MATRIX
        // -------------------------------------------------------------------------
        double densityEM {0.2};
        M = 300;
        ExpMatrix h_expMatrix =  ExpMatrix::randomExpMatrix(N, M, densityEM);
        h_expMatrix.info();
        // -------------------------------------------------------------------------
        // INIT DEVICE EXPRESSION MATRIX
        // -------------------------------------------------------------------------
        cudaExpMatrix devExpMatrix(graph_csr, h_expMatrix);
        devExpMatrix.transpose();

        //==========================================================================
        // HOST PROPAGATION
        //==========================================================================
        //TM_host.start();
        //h_expMatrix.RWR(r, stop_step, &graph_csr);
        //TM_host.stop();
        //
        //TM_host.print("RWR host:   ");

        //==========================================================================
        // CUDA PROPAGATION
        //==========================================================================
        std::cout << "\nRunning RWR cuda";

        TM_device.start();
        devExpMatrix.cudaRWR_N(1, r, stop_step);
        TM_device.stop();

        TM_device.print("RWR cuda: ");

        //=========================================================================
        // COMPARE
        //=========================================================================

        if (compareHostDev(devExpMatrix, h_expMatrix)) {
            std::cout << "<> Correct" << '\n';
            std::cout << std::setprecision(1)
                  << "Speedup: " << TM_host.duration() / TM_device.duration()
                  << "x\n\n";
        }
    }
} 
