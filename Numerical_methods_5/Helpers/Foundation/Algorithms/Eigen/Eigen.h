#ifndef EIGEN_H
#define EIGEN_H

#include "../Main/Algorithm.h"

template < typename T >
struct EigenPair {
	T value;
	std::vector<T> vector;

	EigenPair<T>(T value_ = 0, std::vector<T> vector_ = {}) {
		value = value_;
		vector = vector_;
	}
};

class Eigen {
public:
	template < typename T >
	static std::vector<EigenPair<T>> solve(
		Matr<T> matrix, const std::vector<T> approx, const bool shift = true,  const bool Hess = false, const double epsilon = 10e-3
	);

	template < typename T >
	static EigenPair<T> raleigh(Matr<T> matrix, std::vector<T> approx);
};

#endif