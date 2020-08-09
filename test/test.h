#include <iostream>
#include <iomanip>
#include <cmath>                // std::abs
#include <chrono>
#include <vector>
#include "expMatrix.h"
#include "readExpMatrix.h"
#include "readGraph.h"
#include "cudaExpMatrix.cuh"
#include "graph.h"

//REAL
//#define F_EM        "/home/luca/University/current/architettura/RWR-GPU/RWR/data/mutation/geno.csv"
//#define F_GRAPH_ADJ "/home/luca/University/current/architettura/RWR-GPU/RWR/data/mutation/net.csv"
//#define F_GRAPH_COO "/home/luca/University/current/architettura/RWR-GPU/RWR/data/mutation/net.edges"
//#define F_GRAPH_COO "/home/luca/University/current/architettura/RWR-GPU/RWR/data/K562_HiChIP_Net.clean.mtx"
//DUMMY
#define F_EM        "/home/luca/University/current/architettura/RWR-GPU/RWR/data/mutation/dummy/dummy.exp"
//#define F_GRAPH_ADJ "/home/luca/University/current/architettura/RWR-GPU/RWR/data/mutation/dummy/dummy.adj"
#define F_GRAPH_COO "/home/luca/University/current/architettura/RWR-GPU/RWR/data/mutation/dummy/dummy.edge"

using namespace timer;

namespace Testing {
    void testRandom( int N, int M, int avg_degree, double densityEM, Kernel k=K3_5,
                int stop_step=30, double r=0.6 );
    void testRandomEdgeList(const char* file_graph, const char* file_expMat, int stop_step=30, double r=0.6 );
    void testInput(const char* file_graph, const char* file_expMat, int stop_step=30, double r=0.6 );
    void printPropExpMat(cudaExpMatrix& devExpMatrix, ExpMatrix& h_expMatrix);
    bool compareHostDev(cudaExpMatrix& devExpMatrix, ExpMatrix& h_expMatrix, bool printRes=false);
    void multipleTest(Kernel k);
    void bioTest();

    //Kernel testing
    bool compareDevDev(cudaExpMatrix& devExpMatrixK1, cudaExpMatrix& devExpMatrixK2, 
                       bool printRes=false);
    void testRandomKernel( int N, int M, int avg_degree, double densityEM,
                           Kernel k1, Kernel k2, int stop_step=30, double r=0.6 );
    void Kernel1VsKernel3();
    void Kernel3VsKernel5();
}
