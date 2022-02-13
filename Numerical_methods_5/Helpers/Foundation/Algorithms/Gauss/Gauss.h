#ifndef GAUSS_HPP
#define GAUSS_HPP

#include "../Main/Algorithm.h"

class Gauss: public MatrixAlgorithm {
protected:
	template < typename T >
	static std::vector<SwappingElement> forwardMove(Matr<T>& matrix, std::vector<T>& vec);

	template < typename T >
	static std::vector<T> backwardMove(Matr<T>& matrix, const std::vector<T>& vec, const std::vector<SwappingElement>& journal);
public:
	template < typename T >
	static std::vector<T> solve(Matr<T> matrix, std::vector<T> vec, bool uppertriangular = false);
};

#endif