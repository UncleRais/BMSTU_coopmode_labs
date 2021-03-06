#ifndef POISSON_EQ_SOLVE_CPP
#define POISSON_EQ_SOLVE_CPP

//#include <limits> 
#include <typeinfo>


#include "../../../../../Numerical_methods_5/Helpers/Foundation/Algorithms/Banish/Banish.cpp"
//#include "../../../../../Numerical_methods_5/Helpers/Foundation/Algorithms/NonLinearSolve/NonLin.cpp"
#include "./poisson_eq_solve.h"

template < typename T >
T sqr(T x){return(pow(x,2));};

template <typename T >
T norm(const std::vector<std::vector<T>>& a, const std::vector<std::vector<T>>& b, T h1, T h2)
{
	size_t N = a.size(), M = a[0].size();
	T res = 0;
	if(N == b.size()&&M == b[0].size())
		for(size_t i = 0; i < N; ++i)
			for(size_t j = 0; j < M; ++j)
				//if(fabs(a[i][j] - b[i][j]) > res) res = fabs(a[i][j] - b[i][j]);
				res+= sqr(a[i][j] - b[i][j])*h1*h2;
	return sqrt(res);
}

template < typename T > 
void poisson_eq_solve<T>::solve(const std::string path, const std::array<size_t, 2>& N, T tau, T eps)
{
	std::ofstream file, fnorms;
	file.open(path);
	fnorms.open("./output/norms.dat");

	//const T tau = 0.001;//sqrt(sqr(L[0])/sqr(N[0]) + sqr(L[1])/sqr(N[1])) / sqrt(1/sqr(L[0]) + 1/sqr(L[1])) / pi/100;

	const T h1 = L[0] / N[0], h2 = L[1] / N[1];   //Шаги
	const T hh1 = 1 / sqr(h1), hh2 = 1 / sqr(h2), tautau = 1 / tau; //Вспомогательные переменные
	//std::cout << h1 << " " << h2 << " " << tau << "\n";

	std::vector<std::vector<T>> phi(N[1]+1, std::vector<T>(N[0]+1, 0));
	std::vector<std::vector<T>> actual(N[1]+1, std::vector<T>(N[0]+1, 0));
	//Напоминание: i - выбор строки , j - выбор столбца. prev[i][j]

	//Расчет правой части уравнения на сетке 
	for(size_t i = 0; i < N[1] + 1; ++i)
		for(size_t j = 0; j < N[0] + 1; ++j)
			phi[i][j] = f(i * h2, j * h1);

	//Операторы схем
	auto sch1 = [hh1](size_t i, size_t j, const std::vector<std::vector<T>>& y){return( hh1 * (y[i][j+1] - 2*y[i][j] + y[i][j-1]) );};	
	auto sch2 = [hh2](size_t i, size_t j, const std::vector<std::vector<T>>& y){return( hh2 * (y[i+1][j] - 2*y[i][j] + y[i-1][j]) );};	

	//Векторы для прогонок
	std::vector<T> A0(N[0], hh1);
	std::vector<T> B0(N[0] + 1, -2 * (tautau + hh1));
	std::vector<T> C0(N[0], hh1);
	std::vector<T> F0(N[0] + 1);

	std::vector<T> A1(N[1], hh2);
	std::vector<T> B1(N[1] + 1, -2 * (tautau + hh2));
	std::vector<T> C1(N[1], hh2);
	std::vector<T> F1(N[1] + 1);

	std::vector<T> yj(N[1] + 1);

	actual[0][0] = G[0](0);
	actual[N[1]][0] = G[1](0);
	actual[0][N[0]] = G[0](0);
	actual[N[1]][N[0]] = G[1](N[0]*h1);

	std::vector<std::vector<T>> prev = actual;

	std::vector<T> norms = {100, 90};
	size_t k = 1;
	//Осноной расчет
	while(norms[k]  >= eps*(1 - norms[k] / norms[k-1])) //*(1 - norms[k] / norms[k-1])      norms[k]  >= eps
	{	
		//Идем по строкам
		for(size_t i = 1; i < N[1]; ++i)
		{
			if(IndG[2])
			{ //Условие 2 рода
			B0[0] = (1/h1 + h1/2); C0[0] = -1/h1; F0[0] = (G[2](i*h2) + h1/2);
			// B0[0] = - (2* tautau + hh1);
			// F0[0] =  -(2* tautau * prev[i][0] + sch2(i,0,prev) + phi[i][0] + G[2](i*h2)/h1);
			}
			else
			{ //Условие 1 рода
			B0[0] = -1; C0[0] = 0; F0[0] = -G[2](i*h2);
			};

			for( size_t j = 1; j < N[0]; ++j)
			{
				F0[j] = -(tautau * 2 * prev[i][j] + sch2(i,j,prev) + phi[i][j]);
			};

			if(IndG[3])
			{ //Условие 2 рода
			A0[N[0] - 1] = -1/h1; B0[N[0]] = 1/h1 + h1/2; F0[N[0]] = (G[3](i*h2) + h1/2);
			// B0[N[0]] = - (2*tautau + hh1);
			// F0[N[0]] = -(2*tautau * prev[i][N[0]] + sch2(i,N[0],prev) + phi[i][N[0]] + G[3](i*h2)/h1);
			}
			else
			{ //Условие 1 рода
			A0[N[0] - 1] = 0; B0[N[0]] = -1; F0[N[0]] = -G[3](i*h2);
			};
	
			actual[i] = Banish::solve(A0, B0, C0, F0);
		};
		//
		prev = actual;
		//Идем по столбцам
		for(size_t j = 1; j < N[0]; ++j)
		{
			if(IndG[1])
			{ //Условие 2 рода
				B1[0] = -(1/h2 + h2/2); C1[0] = 1/h2; F1[0] = -(G[1](j*h1) + h2/2);
				// B1[0] = - (2 * tautau + hh2);
				// F1[0] = -(tautau * 2 * prev[0][j] + sch1(0,j,prev) + phi[0][j] + G[1](j*h1)/h2);
			}
			else
			{ //Условие 1 рода
				B1[0] = -1; C1[0] = 0; F1[0] = -G[1](j*h1);
			};

			for(size_t i = 1; i < N[1]; ++i)
			{
				F1[i] = -(tautau * 2 * prev[i][j] + sch1(i,j,prev) + phi[i][j]);
			};

			if(IndG[0])
			{ //Условие 2 рода
				A1[N[1] - 1] = -1/h2; B1[N[1]] = 1/h2 + h2/2; F1[N[1]] = G[0](j*h1) + h2/2;
				// B1[N[1]] = - (2 * tautau + hh2);
				// F1[N[1]] = -(tautau * 2 * prev[N[1]][j] + sch1(N[1],j,prev) + phi[N[1]][j] + G[0](j*h1)/h2);
			}
			else
			{ //Условие 1 рода
				A1[N[1] - 1] = 0; B1[N[1]] = -1; F1[N[1]] = -G[0](j*h1);
			};

			yj = Banish::solve(A1, B1, C1, F1);
			for(size_t i = 0; i < N[1] + 1; ++i)
			{
				actual[i][j] = yj[i];
			}
		};
		//
		k++;
		norms.push_back(norm(actual, prev, h1, h2));
		prev = actual;
	}

	// for(size_t i = 0; i < N[1] + 1; ++i)
	// {
	// 	std::cout << "| ";
	// 	for(size_t j = 0; j < N[0] + 1; ++j)
	// 		std::cout <<std::setw(7)<<std::setprecision(3)<< prev[i][j] << " ";
	// 	std::cout << "|\n";
	// }

	// std::cout << "|\n";

	// for(size_t i = 0; i < N[1] + 1; ++i)
	// {
	// 	std::cout << "| ";
	// 	for(size_t j = 0; j < N[0] + 1; ++j)
	// 		std::cout <<std::setw(7)<<std::setprecision(3)<< actual[i][j] << " ";
	// 	std::cout << "|\n";
	// }

	std::cout << "iters = " << k << "\n";
	std::cout << "finish = " << k * tau << "\n";
	//std::cout << norms;

 	for(size_t i = 0; i < N[1] + 1; ++i)
 	{
		for(size_t j = 0; j < N[0] + 1; ++j)
			file << actual[i][j] << ' ';
		file << std::endl;
	};

	for(size_t i = 0; i < norms.size(); ++i)
		fnorms << norms[i] << " ";

	file << N[0] << " " << L[0] << std::endl;
	file << N[1] << " " << L[1] << std::endl;
	file.close();
	fnorms.close();
} 

#endif