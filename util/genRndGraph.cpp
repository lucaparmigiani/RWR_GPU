#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <iomanip>
#include "../Eigen/Sparse"

void gen_adj_matrix (int num_nodes, int avg_degree, int std_degree, Eigen::MatrixXd& mat, Eigen::VectorXd& vec){

    std::cout << "Generating random graph...";
    // random gaussian generator with avg and std for degrees
    std::default_random_engine generator;
    generator.seed(time(NULL));
    std::normal_distribution<double> distribution(avg_degree, std_degree);

    // seed for shuffling nodes in order to not have clones
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::vector<int> rnd_nodes;
    for (int i = 0; i < num_nodes; ++i) {
        rnd_nodes.push_back(i);
    }

    for (int i = 0; i < num_nodes; ++i) {
        double degree;
        do { degree = distribution(generator); } while (degree < 0); // cannot be negative
        std::shuffle(rnd_nodes.begin(), rnd_nodes.end(), std::default_random_engine(seed));
        for (int j = 0; j < degree; ++j) {
            if(rnd_nodes[j] == i) // no self loop
                degree++, j++;
            mat(i,rnd_nodes[j]) = 1;
        }
    }

    // Symmetry
    for (int i = 1; i < num_nodes; ++i) {
        for (int j = 0; j < i; ++j) {
            mat(j,i) = mat(i,j);
        }
    }
    mat(0,0) = 0;
    vec = mat.colwise().sum();

    std::cout << "Complete" << '\n';
}

Eigen::MatrixXd gen_exp_matrix(const int rows, const int cols, const double density){
    Eigen::MatrixXd mat(rows,cols);

    srand(time(NULL));
    //const int min = 1;
    //const int max = 1;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            double x = (double)rand()/(double)RAND_MAX;
            if (x < density){
                mat(i,j) = 1;
            }
        }
    }

    return mat;
}

