#include "expMatrix.h"

ExpMatrix::ExpMatrix( int rows, int columns) : N(rows), M(columns){
    eMatrix = new double[N * M];
}

ExpMatrix::ExpMatrix( const ExpMatrix & expMatrix) {
    N = expMatrix.N;
    M = expMatrix.M;
    eMatrix = new double[N * M];
    std::memcpy(eMatrix, expMatrix.eMatrix, sizeof(double) * N * M);
}


void ExpMatrix::RWR (const double r, const int stop_step, Graph* graph){
    if(GraphAdjM* g = dynamic_cast<GraphAdjM*>(graph)) {
        RWR_mul(r, stop_step, g);
    }
    if(GraphCSR* g = dynamic_cast<GraphCSR*>(graph)) {
        RWR_graph(r, stop_step, g);
    }
}

void ExpMatrix::info(){
    std::cout << "Number of experiment\t\t"<< M << '\n';
    std::cout << "Number of rows\t\t\t" << N << '\n';
}

void ExpMatrix::print() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            std::cout << eMatrix[i*M + j] << ' ';
        }
        std::cout << '\n';
    }
}

// RWR with matrix multiplication
//=========================================================================

// eMatrixT+1 = (1 - r) * adjMatrix %*% eMatrixT + r * eMatrix
void ExpMatrix::RWR_mul(const double r, const int stop_step, GraphAdjM* graph){

    //Normalizza matrice adiacenza per avere la probabilità di propagazione
    graph->normAdjMatrix();

    // eMatrix0 = r * eMatrix
    double* eMatrix0 = new double[N * M];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            eMatrix0[i*M + j] = eMatrix[i*M + j] * r;
        }
    }

    for (int i = 0; i < stop_step; ++i) {
        nextIterationStep(r, eMatrix0, graph);
    }

    delete[] eMatrix0;
}


void ExpMatrix::nextIterationStep(const double r, double* eMatrix0, GraphAdjM* graph){
    double* eMatrix1 = new double[N * M];

    double ir = 1-r;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            double sum = 0;
            for (int k = 0; k < N; k++)
                sum += graph->adjMatrix[i*N + k] * eMatrix[k*M + j];
            eMatrix1[i*M + j] = sum * ir + eMatrix0[i*M + j];
        }
            //std::cout << "\r" << i << "/"<< N-1 << std::flush;
    }

    delete[] eMatrix;
    eMatrix = eMatrix1;

}

// RWR with graph CSR
//=========================================================================
void ExpMatrix::RWR_graph(const double r, const int stop_step, GraphCSR* graph){
    int V = graph->V;

    double* eMatrix0 = new double[N * M];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            eMatrix0[i*M + j] = eMatrix[i*M + j] * r;
        }
    }

    // Version with ingoing heat
    double* eMatrix1 = new double[N * M];
    for (int k = 0; k < stop_step; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int l = 0; l < M; ++l) {
                double sum = 0;
                for (int j = graph->nodes[i]; j < graph->nodes[i+1]; ++j) {
                    int e = graph->edges[j];
                    sum += eMatrix[e*M + l]/graph->degree[e];
                }
                eMatrix1[i*M + l] = sum*(1-r) + eMatrix0[i*M +l];
            }
        }

        double* tmp = eMatrix;
        eMatrix = eMatrix1;
        eMatrix1 = tmp;
    }
    
    
    // Version with outgoing heat
    //for (int k = 0; k < stop_step; ++k) {
    //    double* eMatrix1 = new double[N * M];
    //    std::copy(eMatrix, eMatrix+N*M, eMatrix1);

    //    for (int i = 0; i < V; ++i) {
    //        for (int j = graph.nodes[i]; j < graph.nodes[i+1]; ++j) {
    //            for (int l = 0; l < M; ++l) {
    //                int e = graph.edges[j];
    //                eMatrix1[e*M + l] += eMatrix[i*M + l]/graph.degree[i];
    //            }
    //        }
    //        for (int l = 0; l < M; ++l) {
    //            eMatrix1[i*M + l] -= eMatrix[i*M + l];
    //        }
    //    }
    //    for (int i = 0; i < V; ++i) {
    //        for (int l = 0; l < M; ++l) {
    //            eMatrix1[i*M + l] = eMatrix1[i*M + l]*(1-r) + eMatrix0[i*M + l];
    //        }
    //    }
    //    delete[] eMatrix;
    //    eMatrix = eMatrix1;
    //}

    delete[] eMatrix0;
}

ExpMatrix ExpMatrix::randomExpMatrix(int rows, int columns, double density){
    ExpMatrix mat(rows, columns);

    srand(time(NULL));
    //const int min = 1;
    //const int max = 1;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            double x = (double)rand()/(double)RAND_MAX;
            if (x < density){
                mat.eMatrix[i*columns + j] = 1;
            }
            else
                mat.eMatrix[i*columns + j] = 0;

        }
    }

    return mat;
}

