#ifndef POISSON_EQ_SOLVE_CPP
#define POISSON_EQ_SOLVE_CPP

//#include <climits>
//#include <limits> 


//#include "../../../../../Numerical_methods_5/Helpers/Foundation/Algorithms/Banish/Banish.cpp"
//#include "../../../../../Numerical_methods_5/Helpers/Foundation/Algorithms/NonLinearSolve/NonLin.cpp"
#include "./poisson_eq_solve.h"

template < typename T > 
void poisson_eq_solve<T>::solve(const std::string path, const std::array<size_t, 3>& N, T finish)
{
	std::ofstream file;
	file.open(path);

	const T h1 = L[0] / N[0], h2 = L[1] / N[1], tau = finish / N[2];   //Шаги
	const T hh1 = 1/ pow(h1 , 2), hh2 = 1 / pow(h2, 2), tautau = 1 / tau; //Вспомогательные переменные
	//std::cout << h1 << " " << h2 << " " << tau << "\n";

	std::vector<std::vector<T>> actual(N[1]+1, std::vector<T>(N[0]+1, 0));
	std::vector<std::vector<T>> prev;

	std::vector<T> A(N[]);
	std::vector<T> B;
	std::vector<T> C;
	std::vector<T> F;

	for(double k = 0; k < N[2] + 1; ++k)
	{	

	}



	file.close();
} 

#endif