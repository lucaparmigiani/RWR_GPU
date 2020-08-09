#include "graph.h"

GraphEdgeList::GraphEdgeList() : Graph(0) {
}

GraphEdgeList::GraphEdgeList(const int _V, const int _nnz) : Graph(_V) {
    nnz = _nnz;
    E = nnz;
    COO_Edges = new  int2[ E ];
    edgeU     = new   int[ E ];
    edgeV     = new   int[ E ];
    nodes     = new   int[ V + 1 ];
    degree    = new   int[ V ]();
    prob      = new float[ V ]();
}

GraphEdgeList::GraphEdgeList(const int _V, std::vector<int2> edgeList) : Graph(_V) {
    // Here E is just for undirect graph, so it's E = edgeList.size()
    nnz = edgeList.size()*2;
    E = edgeList.size();
    edgeU     = new   int[ nnz ];
    edgeV     = new   int[ nnz ];
    COO_Edges = new  int2[ 2 * E ];
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
        edgeU[ nodes[index1] + TMP[index1] ]   = index1;
        edgeV[ nodes[index1] + TMP[index1]++ ] = index2;
		edgeU[ nodes[index2] + TMP[index2]   ] = index2;
		edgeV[ nodes[index2] + TMP[index2]++ ] = index1;
	}
	delete[] TMP;
}

void GraphEdgeList::print() {
    for (int i = 0; i < nnz; ++i) {
        std::cout << edgeU[i] << " "  << edgeV[i] << '\n';
    }
    for (int i = 0; i < V; ++i) {
        std::cout << i << ": " << degree[i] << '\n';
    }
}

GraphEdgeList GraphEdgeList::GetRandomGraph(int nof_nodes, int avg_degree) {
    return GraphEdgeList(nof_nodes, Graph::randomEdgeList(nof_nodes, avg_degree));
}
