#ifndef QR_HPP
#define QR_HPP

#include "../Main/Algorithm.h"

class QR: public MatrixAlgorithm {

public:
	template < typename T >
	static std::vector<T> solve(Matr<T> matrix, std::vector<T> vec, bool printQR = false);

	template < typename T >
	static Matr<T> semblance(Matr<T> matrix);
};

#endif