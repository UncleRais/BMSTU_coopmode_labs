#ifndef SIMPLE_HPP
#define SIMPLE_HPP

#include "../Main/Algorithm.h"

class Simple: public MatrixAlgorithm {	
public:
	template < typename T >
	static std::vector<T> solve(Matr<T> matrix, std::vector<T> vec, T tau, T epsilon = 1e-3);

	template < typename T >
	static void preprocessing(Matr<T>& matrix, std::vector<T>& vec);
};

#endif