#include "readGraph.h"

namespace readUtil {
    void countLines(const char* file, int& nnz){
        int number_of_lines = 0;
        std::ifstream myfile(file);

        std::string line;
        while (std::getline(myfile, line))
            ++number_of_lines;
        nnz = number_of_lines;
    }

    void readGraphHeader( const char* file, int& N, int& E){
        std::cout << "Reading Graph Edgelist header..." << std::flush;
        std::ifstream data(file);
        if (!data.is_open()) {
            std::cout << "Error" << '\n';
            std::exit(EXIT_FAILURE);
        }
        std::string nil;

        //read number of Nodes
        data >> N;
        //read number of Edges
        data >> E;
        std::cout << "Complete" << '\n';
    }


    void readGraph(const char* file, Graph* graph){
        if(GraphAdjM* g = dynamic_cast<GraphAdjM*>(graph)) {
            readMatrixAdj(file, g);
        }
        if(GraphCSR* g = dynamic_cast<GraphCSR*>(graph)) {
            readEdgeList(file, g);
        }
    }
}


void readMatrixAdj(const char* file, GraphAdjM* graph){
    int N = graph->V;

    std::cout << "Reading Adjacency Matrix" << std::flush;
    std::ifstream data(file);
    if (!data.is_open()) {
        std::cout << "Error opening file: " << file << '\n';
        std::exit(EXIT_FAILURE);
    }
    std::string nil;

    // skip the first line
    for (int i = 0; i < N; ++i ) {
        data >> nil;
    }
    // Read the matrix
    for (int i = 0; i < N; ++i) {
        data >> nil;
        for (int j = 0; j < N; ++j) {
            data >> graph->adjMatrix[i*N + j];
            if (graph->adjMatrix[i*N + j]){
                graph->degree[i]++;
            }
        }
    }
    std::cout << "\tComplete" << '\n';
}


void readEdgeList(const char* file, GraphCSR* graph) {
    std::cout << "Reading Edge list" << '\n';
    std::ifstream fin(file);
    if (!fin.is_open()) {
        std::cout << "Error opening file: " << file << '\n';
        std::exit(EXIT_FAILURE);
    }

    std::string nil;
    //skip first line
    fin >> nil >> nil; 

    for (int i = 0; i < graph->nnz; ++i) {
        int index1, index2;
        fin >> index1 >> index2;
        graph->COO_Edges[i] = make_int2(--index1, --index2);

        graph->degree[index1]++;
	}
}

