#include "graph.h"

Graph::Graph(const int _V) : V(_V) {
    degree    = new int[V]();
}


void Graph::info(){
    std::cout << "Graph info:"<< '\n';
    std::cout << "\tNumber of Nodes\t\t" << V << '\n';
    std::cout << "\tNumber of Edges\t\t" << E << '\n';
    std::cout << "\tNumber of Non zero\t"  << nnz << '\n';
}


void Graph::degreeAnalisys() {
	float avg = (float) nnz / V;
    float sum = 0;
    for (int i = 0; i < V; ++i) {
        sum += std::pow(degree[i] - avg, 2);
    }
    float stdDev = std::sqrt(sum/V);
	std::pair<int*, int*> minmax = std::minmax_element(degree, degree + V);
	std::cout << std::setprecision(3)
			  << "          Avg:  " << avg    << std::endl
			  << "     Std. Dev:  " << stdDev << std::endl
			  << "          Min:  " << *minmax.first    << "\t\t" << std::endl
			  << "          Max:  " << *minmax.second    << "\t\t" << std::endl;
	std::cout << std::endl;
}

std::vector<int2> Graph::randomEdgeList(int nof_nodes, int avg_degree){
    std::cout << "Generating random edge list..." << std::flush;
    if(avg_degree > nof_nodes){
        std::cout << "Warning: Average degree > number of nodes" << '\n';
        std::cout << "Setting Average degree = N-1" << '\n';
        avg_degree = nof_nodes-1;
    }

    int E = avg_degree * nof_nodes;
    std::vector<int2> edgeList;
    double prop_edge = (double)(E/2)/(nof_nodes*(nof_nodes-1)/2);

    srand(time(NULL));

    int c = 0;
    //Undirected
    for (int i = 0; i < nof_nodes-1; ++i) {
        for (int j = i+1; j < nof_nodes; ++j) {
            double x = (double)rand()/(double)RAND_MAX;
            if (x <= prop_edge){
                edgeList.push_back(make_int2(i,j));
            }
        }
    }
    std::cout << "Complete" << '\n';
    return edgeList;
}
