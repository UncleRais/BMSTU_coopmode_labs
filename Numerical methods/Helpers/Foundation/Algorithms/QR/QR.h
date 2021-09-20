#ifndef QR_HPP
#define QR_HPP

#include "../Main/Algorithm.h"

class QR: public MatrixAlgorithm {
protected:
	template < typename T >
	static Matrix<T> factor(Matrix<T> rMatrix);

	template < typename T >
	static Matrix<T> solveForParts();
public:
	template < typename T >
	static std::vector<T> solve(Matrix<T> matrix);
};

#endif