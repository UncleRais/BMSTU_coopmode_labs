#ifndef JACOBI_HPP
#define JACOBI_HPP

#include "../Main/Algorithm.h"

class Jacobi: public MatrixAlgorithm {	
public:
	template < typename T >
	static std::vector<T> solve(Matr<T> matrix, std::vector<T> vec, T epsilon = 1e-3);
};

#endif