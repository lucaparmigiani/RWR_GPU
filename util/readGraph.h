#pragma once

#include <iostream>     // std::cout, std::fixed, peek()
#include <string>
#include <fstream>      // std::ifstream
#include <sstream>
#include <cuda_runtime.h>
#include "graph.h"

namespace readUtil {
    void countLines(const char* file, int& nnz);
    void readGraph(const char* file, Graph* graph);
    void readGraphHeader( const char* file, int& N, int& E);
}

void readEdgeList( const char* file, GraphCSR* graph );

void readMatrixAdj(const char* file, GraphAdjM* graph);
