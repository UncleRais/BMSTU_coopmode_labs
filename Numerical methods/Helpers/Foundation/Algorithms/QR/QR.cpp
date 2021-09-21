#ifndef QR_CPP
#define QR_CPP

#include "./QR.h"

template < typename T >
std::vector<T> QR::solve (Matrix<T> matrix) {
	T c = 0;
	T s = 0;
	Matrix<T> rMatrix(matrix);
	for(size_t k = 0; k < rMatrix.size() - 1; ++k)
	{
		for(size_t i = k + 1; i < rMatrix.size(); ++i)
		{
			const T divider = sqrt( pow(rMatrix.atvalue(k, k), 2) + pow(rMatrix.atvalue(i, k), 2) );
			c = rMatrix.atvalue(k, k) / divider;
			s = rMatrix.atvalue(i, k) / divider;
			const T bk_prev = rMatrix.rightValue(k);
			const T bi_prev = rMatrix.rightValue(i);
			rMatrix.rightValueRef(k) = c * bk_prev + s * bi_prev;
			rMatrix.rightValueRef(i) = -s * bk_prev + c * bi_prev;
			for(size_t j = 0; j < rMatrix.size(); ++j)
			{
				const T a_kj = rMatrix.atvalue(k, j);
				const T a_ij = rMatrix.atvalue(i, j);
				rMatrix.at(k, j) = c * a_kj + s * a_ij;
				rMatrix.at(i, j) = -s * a_kj + c * a_ij;
			}
		}
	}
	rMatrix.printsystem(15);

	const Matrix<T> qMatrix = MatrixAlgorithm::dot(matrix, rMatrix.inversed()).transposed();

	qMatrix.printsystem(15);

	return {};
}

#endif