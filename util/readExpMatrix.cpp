#include "readExpMatrix.h"

namespace readUtil {
    void readExpMatrixHeader( const char* file, int& N, int& M){
        std::cout << "Reading Epression matrix header..." << std::flush;
        std::ifstream data(file);
        if (!data.is_open()) {
            std::cout << "Error" << '\n';
            std::exit(EXIT_FAILURE);
        }
        std::string nil;

        //read number of rows
        data >> nil >> N;
        //read number of columns
        data >> nil >> M;
        std::cout << "Complete" << '\n';
    }

    void readExpMatrix(const char* file, ExpMatrix& expMatrix) {

        int N = expMatrix.N;
        int M = expMatrix.M;

        std::cout << "Reading Epression matrix..." << std::flush;
        std::ifstream data(file);
        if (!data.is_open()) {
            std::cout << "Error" << '\n';
            std::exit(EXIT_FAILURE);
        }
        std::string nil;

        // skip the first three line
        data >> nil >> nil;
        data >> nil >> nil;
        for (int i = 0; i < M; ++i ) {
            data >> nil;
        }
        // Read the matrix
        for (int i = 0; i < N; ++i ) {
            //data >> nil >> nil >> nil;
            data >> nil;
            for (int j = 0; j < M; ++j ) {
                data >> expMatrix.eMatrix[i*M + j];
            }
        }
        std::cout << "Complete" << '\n';
    }
}


