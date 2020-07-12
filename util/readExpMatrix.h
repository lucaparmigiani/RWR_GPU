#pragma once

#ifndef READ_EXP_MAT_H
#define READ_EXP_MAT_H

#include <iostream>     // std::cout, std::fixed, peek()
#include <string>
#include <fstream>      // std::ifstream
#include <sstream>
#include "expMatrix.h"

namespace readUtil {
    void readExpMatrixHeader( const char* file, int& N, int& M);

    void readExpMatrix(const char* file, ExpMatrix& expMatrix);
}
#endif
