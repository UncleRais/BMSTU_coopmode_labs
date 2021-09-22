#ifndef QR_HPP
#define QR_HPP

#include "../Main/Algorithm.h"

class QR: public MatrixAlgorithm {

public:
	template < typename T >
	static std::vector<T> solve(Matrix<T> matrix);
};

#endif