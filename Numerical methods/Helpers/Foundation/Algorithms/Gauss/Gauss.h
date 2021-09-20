#ifndef GAUSS_HPP
#define GAUSS_HPP

#include "../Main/Algorithm.h"

class Gauss: public MatrixAlgorithm {
protected:
	template < typename T >
	static std::vector<SwappingElement> factor(Matrix<T>& matrix);

	template < typename T >
	static std::vector<T> backwardMove(Matrix<T>& matrix, const std::vector<SwappingElement>& journal);
public:
	template < typename T >
	static std::vector<T> solve(Matrix<T> matrix);
};

#endif