#ifndef SIMPLE_CPP
#define SIMPLE_CPP

#include "./Simple.h"
#include <cmath>
#include "../../Foundation.cpp"
#include "../../Math.cpp"
#include "../../Print/Print.cpp"

template < typename T >
void Simple::preprocessing(Matr<T>& matrix, std::vector<T>& vec)
{   //If diag element is negative, we multiply it's row by -1
	for(size_t i = 0; i < matrix.size(); ++i)
	{
		if (matrix.at(i , i) < 0)
		{
			for (size_t j = 0; j < matrix.size(); ++j)
			{
				matrix.at(i , j) *= -1;
			}
			vec[i] *= -1;
		}
	}
}

template < typename T >
std::vector<T> Simple::solve(Matr<T> matrix, std::vector<T> vec, T tau, T epsilon) {
	std::vector<T> result(vec.size(), 1.0);
	preprocessing(matrix , vec);

	Matr<T> C(tau * matrix); // C = tau * A - E
	vec = vec * tau;         // tua * b
	for (size_t i = 0; i < C.size(); ++i)
		C.at(i,i) -= 1;
	T normC = C.norminf();

	std::cout << "NormC = " << normC << "\n";
	
	int counter = 0;
	std::vector<T> previous(vec.size() , 0.0);
	std::cout << "Iter estimate: " << log((1-normC)*epsilon/Math::norm(result - previous))/log(normC) << "\n";
	if(normC <= 1)
	{
		auto criteria = [epsilon](const std::vector<T>& x, const std::vector<T>& y, const T norm) {
			return Math::norm(x - y) >=
			//(1 - norm) * (epsilon) / norm;
			 epsilon;
			// epsilon * Math::norm(y) + 1e-5;
			//epsilon * (Math::norm(y) + 1e-5);
		};

		while(criteria(previous, result, normC))
		{
			previous = result; 
			result = vec - C * result;
			++counter;
		}
	}
	std::cout << "Iterations: " << counter << "\n";

	return result;
}

#endif