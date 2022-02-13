#ifndef RELAX_CPP
#define RELAX_CPP

#include "Relax.h"
#include <cmath>
#include "../../Foundation.cpp"
#include "../../Math.cpp"
#include "../../Print/Print.cpp"

template < typename T >
std::vector<T> Relax::solve(Matr<T> matrix, std::vector<T> vec, T omega, T epsilon)
 {
	Matr<T> G1 = -omega * matrix.diagonal().inversed() * matrix.lower();
	Matr<T> G2 = (1 - omega) * identityMatrix<T>(vec.size()) - omega * matrix.diagonal().inversed() * matrix.upper();
	T normG1 = G1.norminf();
	T normG2 = G2.norminf();

	std::cout << "Norm G1 = " << normG1 << "\n";
	std::cout << "Norm G2 = " << normG2 << "\n";

	int counter = 0;

  	if (normG1 + normG2 < 1) 
  	{
  		std::vector<T> result(vec.size(), 1.0);
		std::vector<T> previous(vec.size() , 0.0);
		T q = normG2/(1 - normG1);
		std::cout << "Iter estimate: " << log((1-q)*epsilon/Math::norm(result - previous))/log(q) << "\n";

		auto criteria = [epsilon](const std::vector<T>& x, const std::vector<T>& y, const T norm1, const T norm2) {
			return Math::norm(x - y) >=
			(1 - norm1 - norm2) * (epsilon) / norm2;
			//epsilon;
			// epsilon * Math::norm(y) + 1e-5;
			//epsilon * (Math::norm(y) + 1e-5);
		};


		while(criteria(previous, result, normG1, normG2)) 
		{
			previous = result;

			for (size_t i = 0; i < vec.size(); ++i) 
			{
				T sumJ = 0;
				for (size_t j = 0; j < vec.size(); ++j) 
				{
					if (j == i) 
						continue;

					sumJ += result[j] * matrix.at(i, j) / matrix.at(i, i);
				}

				result[i] = - omega * sumJ + (1 - omega) * previous[i] + omega * vec[i] / matrix.at(i, i);
			}
			++counter;
		}
	std::cout << "Iterations: " << counter << "\n";
	return result;
	}
return{};
}

template < typename T >
std::vector<T> Relax::solve(T omega, T epsilon) {
	const size_t variant = 23;
	const size_t n = 200 + variant;
	const T a_i = 1;
	const T b_i = 4;
	const T c_i = 1;

	std::vector<T> A(n, a_i);
	std::vector<T> B(n, b_i);
	std::vector<T> C(n, c_i);

	std::vector<T> D(n, 6);
	std::vector<T> X(n, 0);
	for(size_t i = 0; i < n; ++i) {
		D[i] = 10 - 2 * fmod(i, 2);
		X[i] = 2 - fmod(i, 2);
	}
	D[n - 1] = 9 - 3 * fmod(n, 2);

	/*
		| x 0 0 0 0 |     | 0 0 0 0 |      |  0  0  0  0  |
		| 0 x 0 0 0 |     | y 0 0 0 |   =  |  xy 0  0  0  |
		| 0 0 x 0 0 |     | 0 y 0 0 | 	   |  0  xy 0  0  |
		| 0 0 0 x 0 |  .  | 0 0 y 0 |	   |  0  0  xy 0  |
	*/
	const T normG1 = fabs(-omega * a_i / b_i);
	const T normG2 = fmax(fabs(-omega * c_i / b_i), fabs(1 - omega));

	std::cout << "Norm G1 = " << normG1 << "\n";
	std::cout << "Norm G2 = " << normG2 << "\n";

	if (normG1 + normG2 < 1) {
		std::vector<T> result(n, 0.0);
		std::vector<T> previous(n , 1.0);
		while(Math::norm(result - previous) > epsilon * (1 - normG1 - normG2) / normG2 ) {
			previous = result;
			for (size_t i = 0; i < n; ++i) {
				result[i] = (1 - omega) * previous[i] + omega  * D[i] / b_i;
				if (i > 0)
					result[i] -= omega * a_i / b_i * previous[i - 1]; 

				if (i < n)
					result[i] -= omega * a_i / b_i * previous[i + 1];
			}
		}

		std::cout << X << "\n";

		return  result;
	} 

	return {};
}

#endif