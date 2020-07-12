#pragma once

#include <sstream>
#include <iostream>
#include "fUtil.h"
#include "cudaUtil.cuh"
#include "graph.h"
#include "expMatrix.h"
#include "Timer.cuh"
#include "../../config.h"
#include "definition.cuh"

enum Kernel{
    K1,
    K3,
    K3_5
};

class cudaExpMatrix {
		GraphCSR graph;

		int*  devNodes, *devEdges, *devDegrees;
		int*  devF;

        double* devExpVec1, *devExpVec2, *devExpVec0;

		int V, E;
        int M;
		int allocFrontierSize;

	public:
        ExpMatrix expMatrix;
		int* devInF;

		cudaExpMatrix(GraphCSR& graph, ExpMatrix& expMatrix);


		void reset_kernel1(const int Sources[], int nof_sources = 1);
		void init_kernel1();
		void init_kernel3();
		void init_kernel4();
		void init_kernel5();
		inline void cudaRWR_Kernel1(double r, int stop_step);
		inline void cudaRWR_Kernel3(double r, int stop_step);
		inline void cudaRWR_Kernel4(double r, int stop_step);
		inline void cudaRWR_Kernel5(double r, int stop_step);

		void cudaRWR_N(int nof_tests, double r, int stop_step, Kernel k = Kernel::K3_5);
        void reset_gpu();
        void transpose();

	private:
        inline void FrontierDebug(int F2Size, bool check = false);

		template<int MIN_VALUE, int MAX_VALUE>
		inline int logValueHost(int Value);
};
