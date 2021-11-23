#ifndef EIGEN_CPP
#define EIGEN_CPP

#include "./Eigen.h"
#include <functional>

template < typename T >
std::vector<T> Eigen::values(Matr<T> matrix, const bool shift, const double eps) {
	std::function<bool(const Matr<T>&)> closeToZero = [eps](const Matr<T>& A)
	{
		for(size_t i = 0; i < A.systemSize - 1; ++i)
			if (fabs(A.atvalue(A.systemSize - 1, i)) > eps)
				return false;

		return true;
	};

	std::vector<T> lambdas;
	lambdas.reserve(matrix.systemSize);

	while(matrix.systemSize > 0) {
		const T sigma = shift ? matrix.atvalue(matrix.systemSize - 1, matrix.systemSize - 1) : 0;
		while(!closeToZero(matrix)) {
			const auto identity = identityMatrix(matrix.systemSize, sigma);
			matrix =  QR::semblance(matrix - identity) + identity;
		}
		lambdas.push_back(matrix.atvalue(matrix.systemSize - 1, matrix.systemSize - 1));
		matrix.minor();
	}

	std::sort(lambdas.begin(), lambdas.end());

	return lambdas;
}

template < typename T >
std::vector<T> Eigen::vectors(std::vector<T>) {

	return {};
}

#endif