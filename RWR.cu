#include <iostream>
#include <iomanip>
#include <cmath>                // std::abs
#include <chrono>
#include <vector>
#include "Timer.cuh"
#include "expMatrix.h"
#include "readExpMatrix.h"
#include "readGraph.h"
#include "cudaExpMatrix.cuh"
#include "test/test.h"

int main() {


    //==========
    // TESTING
    //==========
    //BIO
    //Testing::bioTest();
    //Testing::testInput(F_GRAPH_COO, F_EM);
    //ecoli.ppi
    //Testing::testRandom(4787, 300, 169, 0.2);
    //human.ppi
    //Testing::testRandom(19354, 300, 608, 0.2);
    //bio-wormNet
    //Testing::testRandom(16347, 300, 47, 0.2);
    //COG
    Testing::testRandom(308518, 300, 204, 0.2);

    ///* Kernel 1 vs sequential *///
    //std::cout << "Kernel 1 vs sequential" << '\n';
    //Testing::multipleTest(Kernel::K1);
    // Kernel 3 vs sequential
    //std::cout << "Kernel 3 vs sequential" << '\n';
    //Testing::multipleTest(Kernel::K3);
    // Kernel 3-5 vs sequential
    //std::cout << "Kernel 3+5 vs sequential" << '\n';
    //Testing::multipleTest(Kernel::K3_5);
    ///* Kernel 1 vs Kernel 3*///
    //std::cout << "Kernel 3 vs Kernel 1" << '\n';
    //Testing::Kernel1VsKernel3();
    //Testing::Kernel3VsKernel5();
}
