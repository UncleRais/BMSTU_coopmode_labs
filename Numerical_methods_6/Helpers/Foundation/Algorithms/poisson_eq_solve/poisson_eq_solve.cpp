#ifndef POISSON_EQ_SOLVE_CPP
#define POISSON_EQ_SOLVE_CPP

//#include <climits>
//#include <limits> 


#include "../../../../../Numerical_methods_5/Helpers/Foundation/Algorithms/Banish/Banish.cpp"
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

	std::vector<std::vector<T>> actual;
	std::vector<std::vector<T>> phi(N[1]+1, std::vector<T>(N[0]+1, 0));
	std::vector<std::vector<T>> prev(N[1]+1, std::vector<T>(N[0]+1, 0));

	//Векторы для прогонок
	std::vector<T> A0(N[0], hh1);
	std::vector<T> B0(N[0] + 1, -2 * (tautau + hh1));
	std::vector<T> C0(N[0], hh1);
	std::vector<T> F0(N[0] + 1);

	std::vector<T> A1(N[1], hh2);
	std::vector<T> B1(N[1] + 1, -2 * (tautau + hh2));
	std::vector<T> C1(N[1], hh2);
	std::vector<T> F1(N[1] + 1);

	//Расчет правой части уравнения на сетке 
	for(size_t i = 0; i < N[0] + 1; ++i)
		for(size_t j = 0; j < N[1] + 1; ++j)
			phi[i,j] = f(i * h1, j * h2);

	//Операторы схем
	T scheme1 = [hh1](size_t i, size_t j, std::vector<std::vector<T>> y){return(hh1 * (y[i+1,j] - 2*y[i,j] + y[i-1,j]));};	
	T scheme2 = [hh2](size_t i, size_t j, std::vector<std::vector<T>> y){return(hh2 * (y[i,j+1] - 2*y[i,j] + y[i,j-1]));};	

	//Расчет первого слоя


	//Осноной расчет
	for(double k = 1; k < N[2] + 1; ++k)
	{	
		for(size_t i = 0; i < N[0] + 1; ++i)
		{
			for( size_t j = 1; j < N[1]; ++j)
			{

			};
		};


		for(size_t j = 0; i < N[1] + 1; ++i)
		{
			for( size_t i = 1; j < N[0]; ++j)
			{

			};
		};
		prev = Banish::solve(A , C , B , F);
	}



	file.close();
} 

#endif