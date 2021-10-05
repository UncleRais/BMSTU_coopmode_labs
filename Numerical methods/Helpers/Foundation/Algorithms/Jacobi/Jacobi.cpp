#ifndef JACOBI_CPP
#define JACOBI_CPP

#include "./Jacobi.h"
#include <cmath>
#include "../../Foundation.cpp"
#include "../../Math.cpp"
#include "../../Print/Print.cpp"

template < typename T >
std::vector<T> Jacobi::solve(Matr<T> matrix, std::vector<T> vec, T epsilon) {
	std::vector<T> result(vec.size(), 1.0);
	
	Matr<T> C(matrix.size() , 0.0);
	for(size_t i = 0; i < C.size(); ++i)
	{
		T diagelem = matrix.at(i, i);
		for(size_t j = 0; j < C.size(); ++j)
			if(i != j)
			{
				C.at(i, j) = - matrix.at(i , j) / diagelem;
			}
		vec[i] /= diagelem; 
	}
	T condC = C.norminf();

	std::cout << "CondC = " << condC << "\n";
	
	int counter = 0;
	std::vector<T> previous(vec.size() , 0.0);
	if(condC <= 1)
	{
		while(Math::norm(previous - result) >= (1 - condC) * (epsilon)/condC )
		{
			previous = result; 
			result = vec + C * result;
			++counter;
		}
	}
	std::cout << "Iterations: " << counter << "\n";

	return result;
}

#endif