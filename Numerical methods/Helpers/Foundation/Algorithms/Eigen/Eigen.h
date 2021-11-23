#ifndef EIGEN_H
#define EIGEN_H

#include "../Main/Algorithm.h"

class Eigen {
public:
	template < typename T >
	static std::vector<T> solve(Matr<T> matrix, const bool shift = true, const double epsilon = 10e-3);
};

#endif