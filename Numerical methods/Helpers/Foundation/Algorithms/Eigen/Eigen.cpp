#ifndef EIGEN_CPP
#define EIGEN_CPP

#include "./Eigen.h"
#include "../../Math.cpp"
#include <functional>

template < typename T >
std::vector<EigenPair<T>> Eigen::solve(Matr<T> matrix, const bool shift, const double eps) {
	std::function<bool(const Matr<T>&)> closeToZero = [eps](const Matr<T>& A)
	{
		for(size_t i = 0; i < A.systemSize - 1; ++i)
			if (fabs(A.atvalue(A.systemSize - 1, i)) > eps)
				return false;

		return true;
	};

	Matr<T> copy(matrix);
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

	std::vector<std::vector<T>> vectors;
	vectors.reserve(lambdas.size());
	for (const auto& lambda: lambdas)
	{
		const auto B = copy - identityMatrix(copy.systemSize, lambda);
		// std::cout << B << "\n";
		std::vector<T> x(copy.systemSize, 0); x[0] = 1;
		auto y = Gauss::solve(B, x);
		const auto ort = norm(y);
		for (auto& i: y) { i /= ort; }

		size_t it = 0;
		while (it < 6) {
			++it;
			x = y;
			y = Gauss::solve(B, x);
			const auto ort = norm(y);
			for (auto& i: y) { i /= ort; }
		}
		vectors.push_back(x);
	}

	std::vector<EigenPair<T>> pairs(lambdas.size());
	for (size_t i = 0; i < lambdas.size(); ++i) {
		pairs[i] = EigenPair<T>(lambdas[i], vectors[i]);
	}

	return pairs;
}

#endif