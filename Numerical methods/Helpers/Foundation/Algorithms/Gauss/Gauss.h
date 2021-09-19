#ifndef GAUSS_HPP
#define GAUSS_HPP

#include "../Main/Algorithm.h"

// enum FactorizationResult {
// 	successfully,
// 	notInvertible
// };

class Gauss: public MatrixAlgorithm {
public:
	// template < typename T >
	// static FactorizationResult factor(Matrix<T>& matrix);

	template < typename T >
	static std::vector<T> solve(Matrix<T> matrix);
};

#endif