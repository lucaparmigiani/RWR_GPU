#include "graph.h"

GraphCSR::GraphCSR(const int _V, const int _nnz) : Graph(_V) {
    nnz = _nnz;
    E = nnz;
    COO_Edges = new  int2[ E ];
    edges     = new   int[ E ];
    nodes     = new   int[ V + 1 ];
    degree    = new   int[ V ]();
    prob      = new float[ V ]();
}

GraphCSR::GraphCSR(const int _V, std::vector<int2> edgeList) : Graph(_V) {
    nnz = edgeList.size()*2;
    E = edgeList.size();
    COO_Edges = new  int2[ 2 * E ];
    edges     = new   int[ 2 * E ];
    nodes     = new   int[ V + 1 ];
    degree    = new   int[ V ]();
    prob      = new float[ V ]();

	for (int i = 0; i < E; i++) {
		int index1 = edgeList[i].x;
		int index2 = edgeList[i].y;
		degree[index1]++;
		degree[index2]++;
	}

	nodes[0] = 0;
	std::partial_sum(degree, degree + V, nodes + 1);
	int* TMP = new int[V]();
	for (int i = 0; i < E; ++i) {
		int index1 = edgeList[i].x;
		int index2 = edgeList[i].y;
		edges[ nodes[index1] + TMP[index1]++ ] = index2;
		edges[ nodes[index2] + TMP[index2]++ ] = index1;
	}
	delete[] TMP;
}

void GraphCSR::ToCSR() {
	std::cout << "        COO To CSR...\t\t" << std::flush;

	nodes[0] = 0;
	std::partial_sum(degree, degree + V, nodes + 1);
	//for (int i = 0; i < V +1; ++i) {
    //    std::cout << nodes[i] << "," ;
    //}
	
	int* TMP = new int[V]();
	for (int i = 0; i < nnz; ++i) {
		int index1 = COO_Edges[i].x;
		int index2 = COO_Edges[i].y;
		edges[ nodes[index1] + TMP[index1]++ ] = index2;
		//edges[ nodes[index2] + TMP[index2]++ ] = index1; // dont need this, edge is already present twice in file.edge
	}
	delete[] TMP;

	std::cout << "Complete!\n\n" << std::flush;
}

void GraphCSR::print() {
    for (int i = 0; i < V; ++i) {
        std::cout << i << ": ";
        for (int j = nodes[i]; j < nodes[i+1]; ++j) {
            std::cout << edges[j] << ',';
        }
        std::cout << '\n';
    }
    for (int i = 0; i < V; ++i) {
        std::cout << i << ": " << degree[i] << '\n';
    }
}

GraphCSR GraphCSR::GetRandomGraph(int nof_nodes, int avg_degree) {
    return GraphCSR(nof_nodes, Graph::randomEdgeList(nof_nodes, avg_degree));
}
