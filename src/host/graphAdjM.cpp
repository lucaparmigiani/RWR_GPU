#include "graph.h"

GraphAdjM::GraphAdjM(const int _V) : Graph(_V) {
    adjMatrix = new double[V * V];
    degree    = new int[V]();
}

void GraphAdjM::normAdjMatrix(){
    // Normalize adjMatrix through rows
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            adjMatrix[i*V + j] /= degree[j];
        }
    }
}


