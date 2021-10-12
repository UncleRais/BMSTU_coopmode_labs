#ifndef RELAX_CPP
#define RELAX_CPP

#include "Relax.h"
#include <cmath>
#include "../../Foundation.cpp"
#include "../../Math.cpp"
#include "../../Print/Print.cpp"

template < typename T >
std::vector<T> Relax::solve(Matr<T> matrix, std::vector<T> vec, T omega, T epsilon) {

	Matr<T> G1 = -omega * matrix.diagonal().inversed() * matrix.lower();
	Matr<T> G2 = (1 - omega) * identityMatrix<T>(vec.size()) - omega * matrix.diagonal().inversed() * matrix.upper();
	T normG1 = G1.norminf();
	T normG2 = G2.norminf();

	std::cout << "Norm G1 = " << normG1 << "\n";
	std::cout << "Norm G2 = " << normG2 << "\n";
	
	std::vector<T> result(vec.size(), 0.0);
	std::vector<T> previous(vec.size() , 1.0);

	int counter = 0;

  	if (normG1 + normG2 < 1) {
		while(Math::norm(result - previous) > epsilon * (1 - normG1 - normG2) / normG2 ) {
			previous = result;

			for (size_t i = 0; i < vec.size(); ++i) {
				T sumJ = 0;
				for (size_t j = 0; j + 1 < i; ++j) {
					sumJ += result[j] * matrix.at(i, j) / matrix.at(i, i);
				}
				result[i] = - omega * sumJ + (1 - omega) * previous[i] + omega * vec[i] / matrix.at(i, i);
			}
			++counter;
		}
	}
	std::cout << "Iterations: " << counter << "\n";

	 return result;
}

#endif