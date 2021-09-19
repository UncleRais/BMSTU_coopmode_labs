#ifndef GAUSS_HPP
#define GAUSS_HPP

#include "../Main/Algorithm.h"

class Gauss: public MatrixAlgorithm {
public:
	template < typename T >
	static std::vector<T> solve(Matrix<T>& matrix);
};

#endif