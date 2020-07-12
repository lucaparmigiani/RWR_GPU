#pragma once

#include <iostream>
#include <algorithm>
#include <cstring> //memcpy
#include "graph.h"

class ExpMatrix {
    private:
        void RWR_mul(const double r, const int stop_step, GraphAdjM* graph);
        void nextIterationStep(const double r, double* eMatrix0, GraphAdjM* graph);
        void scalarMultiplication(double*& A, double alph);

        void RWR_graph(const double r, const int stop_step, GraphCSR* graph);

    public:      
        int N; //number of genes       | rows
        int M; //number of experiments | columns

        double* eMatrix;

        ExpMatrix( int rows, int columns);
        ExpMatrix( const ExpMatrix & expMatrix);

        void info();
        void RWR (const double r, const int stop_step, Graph* graph);

        static ExpMatrix randomExpMatrix(int rows, int columns, double density);

        template<int MIN_VALUE, int MAX_VALUE>
        inline int logValueHost(int Value);

};
