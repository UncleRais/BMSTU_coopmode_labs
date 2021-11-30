#ifndef EIGEN_CPP
#define EIGEN_CPP

#include "./Eigen.h"
#include "../../Math.cpp"
#include <functional>

template < typename T >
std::vector<EigenPair<T>> Eigen::solve(Matr<T> matrix, const std::vector<T> approx, const bool shift, const double eps) 
{
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
	while(matrix.systemSize > 0) 
	{
		const T sigma = shift ? matrix.atvalue(matrix.systemSize - 1, matrix.systemSize - 1) : 0;
		while(!closeToZero(matrix)) 
		{
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
		auto B = copy - identityMatrix(copy.systemSize, lambda);
		// std::cout << B << "\n";
		std::vector<T> x(approx);
		auto y = Gauss::solve(B, x);
		const auto ort = norm(y);
		for (auto& i: y) { i /= ort; }

		//T templamb;  
		size_t it = 0;
		while (it < 300) {
			++it;
			x = y;
			//templamb = (copy * x) * x;
			B = copy - identityMatrix(copy.systemSize, lambda);
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

template < typename T >
EigenPair<T> Eigen::raleigh(Matr<T> matrix, std::vector<T> approx) 
{
	const auto norm_approx = norm(approx);
	for (auto& i: approx) { i /= norm_approx; }

	const size_t iterations = 30;
	T lambda = T(0);
	for (size_t i = 0; i < iterations; ++i) {
		const std::vector<T> buffer = matrix * approx;
		lambda = 0;
		for (size_t j = 0; j < approx.size(); ++j)
		{
			lambda = buffer[i] * approx[i];
		}
		approx = Gauss::solve((matrix - identityMatrix(matrix.systemSize, lambda)), approx);
		const auto ort = norm(approx);
		for (auto& i: approx) { i /= ort; }
	}

	return EigenPair<T>(lambda, approx);
}

#endif