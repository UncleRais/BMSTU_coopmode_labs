#ifndef RELAX_H
#define RELAX_H

#include "../Main/Algorithm.h"

class Relax: public MatrixAlgorithm {
public:
	template < typename T >
	static std::vector<T> solve(Matr<T> matrix, std::vector<T> vec, T omega, T epsilon = 1e-3);

	//MARK: - Three Diag Matrix represented as 3 vectors
	template < typename T >
	static std::vector<T> solve(T omega, T epsilon = 1e-3);
};

#endif