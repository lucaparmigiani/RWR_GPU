#pragma once

#include <vector_types.h>	//int2
#include <cuda_runtime.h>   // make_int2
#include <utility>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <iomanip>      	// setprecision
#include <vector>

enum GraphType {
    ADJ_MAT,
    CSR,
};

class Graph {
	public:
		int V, E, nnz;
        int* degree;

        Graph(const int _V);

		void print();
        void info();
        void degreeAnalisys();
        virtual ~Graph() {};
        static std::vector<int2> randomEdgeList(int nof_nodes, int avg_degree);
};

class GraphAdjM : public Graph{
    public:
        double* adjMatrix; //adjacency matrix

        GraphAdjM(const int _V);
        void normAdjMatrix();
};

class GraphCSR : public Graph {

    public:
		int2* COO_Edges;   //edgelist
		int   *nodes, *edges;
        float *prob;

        GraphCSR(const int _V, const int _nnz);
        GraphCSR(const int _V, std::vector<int2> edgeList);
		void ToCSR();
		void print();
        static GraphCSR GetRandomGraph(int nof_nodes, int avg_degree);
};
