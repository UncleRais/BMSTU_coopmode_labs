#ifndef QR_CPP
#define QR_CPP

#include "./QR.h"
#include "../../Print/Print.cpp"

template < typename T >
std::vector<T> QR::solve (Matr<T> matrix, std::vector<T> vec, bool printQR) {
	T c = 0;
	T s = 0;
	Matr<T> rMatrix(matrix);
	std::vector<T> oldvec(vec);
	for(size_t k = 0; k < rMatrix.size() - 1; ++k)
	{
		for(size_t i = k + 1; i < rMatrix.size(); ++i)
		{
			const T divider = sqrt( pow(rMatrix.atvalue(k, k), 2) + pow(rMatrix.atvalue(i, k), 2) );
			c = rMatrix.atvalue(k, k) / divider;
			s = rMatrix.atvalue(i, k) / divider;
			const T bk_prev = vec[k];
			const T bi_prev = vec[i];
			vec[k] = c * bk_prev + s * bi_prev;
			vec[i] = -s * bk_prev + c * bi_prev;
			for(size_t j = 0; j < rMatrix.size(); ++j)
			{
				const T a_kj = rMatrix.atvalue(k, j);
				const T a_ij = rMatrix.atvalue(i, j);
				rMatrix.at(k, j) = c * a_kj + s * a_ij;
				rMatrix.at(i, j) = -s * a_kj + c * a_ij;
			}
		}
	}

	Matr<T> qMatrix(matrix * rMatrix.inversed());
	const std::vector<T> bStar = Gauss::solve(qMatrix ,oldvec);

	if (printQR)
	{
		std::cout << "Q: \n" << qMatrix << "\n";
		std::cout << "R: \n" << rMatrix << "\n";
		std::cout << "QR: \n" << qMatrix * rMatrix << "\n";
	}

	return Gauss::solve(rMatrix, bStar, true);
}

template < typename T >
Matr<T> QR::semblance(Matr<T> matrix, const bool Hess) 
{
	T c = 0;
	T s = 0;
	Matr<T> rMatrix(matrix);
	size_t wherestop, from;
	for(size_t k = 0; k < rMatrix.size() - 1; ++k)
	{
		wherestop = Hess ? k + 2 : rMatrix.size();
		for(size_t i = k + 1; i < wherestop; ++i)
		{
			const T divider = sqrt( pow(rMatrix.atvalue(k, k), 2) + pow(rMatrix.atvalue(i, k), 2) );
			c = rMatrix.atvalue(k, k) / divider;
			s = rMatrix.atvalue(i, k) / divider;
			from = Hess ? i - 1 : 0;
			for(size_t j = from; j < rMatrix.size(); ++j)
			{
				const T a_kj = rMatrix.atvalue(k, j);
				const T a_ij = rMatrix.atvalue(i, j);
				rMatrix.at(k, j) = c * a_kj + s * a_ij;
				rMatrix.at(i, j) = -s * a_kj + c * a_ij;
			}
		}
	}
	Matr<T> qMatrix(matrix * rMatrix.inversed());
	return qMatrix * matrix * qMatrix.transposed();
}

#endif