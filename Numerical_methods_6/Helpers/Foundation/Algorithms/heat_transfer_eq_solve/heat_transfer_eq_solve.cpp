#ifndef HEAT_TRANSFER_EQ_SOLVE_CPP
#define HEAT_TRANSFER_EQ_SOLVE_CPP

#include <climits>
#include <limits> 

#include "./heat_transfer_eq_solve.h"


template < typename T >
 /*Не могу заменить std::vector<std::vector<T>> на Portrait, выдает ошибку, надо исправить*/
Portrait<T> heat_transfer_eq_solve<T>::NDsolve(int left, int right, int NumTime, int NumX, 
											   T LatterTime, T sigma)
{ 
	int NumberOfResults = 30;
	T h = L/(NumX - 1);
	T tau = LatterTime/(NumTime - 1);
	T coef_cp = tau/(h * c * rho);
	T omega_plus, omega_minus, mu_left, mu_right; 

	Portrait<T> result;
	std::vector<T> prev(NumX, T0), actual(NumX, 0), coef_a(NumX - 1);

	for(int i = 0; i < NumX - 1; i++)
		coef_a[i] = K(0, i + h/2);

	result.reserve(NumberOfResults);
	result.push_back(prev);

	//Явный метод на четырехточечном шаблоне
	if( sigma < std::numeric_limits<T>::min()) 
	{
		for(int j = 1; j < NumTime; ++j)
		{
			omega_minus = coef_a[0] * (prev[1] - prev[0]) / h;
			mu_left = prev[0] + 2 * (omega_minus - P(j*tau))*coef_cp;
			for(int i = 1; i < NumX - 1; ++i)
			{
				omega_plus = coef_a[i] * (prev[i + 1] - prev[i]) / h;
				actual[i] = prev[i] + coef_cp * (omega_plus - omega_minus);
				omega_minus = omega_plus;
			}
			mu_right = prev[NumX - 1] + 2 * (P(j*tau) - omega_minus)*coef_cp;
			
			actual[0] = left * mu_left + (1 - left) * T0;
			actual[NumX - 1] = right * mu_right  + (1 - right) * T0;
			if(j % NumberOfResults) result.push_back(actual);
			prev = actual;
		}

	}
	else
	//Неявный метод на шеститочечном шаблоне (sigma = 1, четырехточечный)
	{

	}
	return(result);
}

template < typename T >
void heat_transfer_eq_solve<T>::parameters_info() const
{
	std::cout << "Beam characteristics:\n";
	std::cout << "c = " << c << ", rho = " << rho << ", L = " << L <<";\n"; 
	std::cout << "Boundary conditions:\n";
	std::cout << "alpha = " << alpha << ", beta = " << beta << ", gamma = " << gamma << ",\n";
	std::cout << "x1 = " << x1 << ", x2 = " << x2 << ", k1 = " << k1 << ", k2 = " << k2 << ",\n";
	std::cout << "Q = " << Q << ", t0 = " << t0 << ", T0 = " << T0 << ";\n";
}

template < typename T >
void heat_transfer_eq_solve<T>::save(const std::vector<std::vector<T>>& portrait, const std::string path)
{
	std::ofstream file;
	file.open(path);
	for(const auto &point: portrait)
	{
		for(const auto &coordinate: point)
		{
			file << coordinate << ' ';
		}
		file << std::endl;
	}
	file.close();
}

template < typename T >
void heat_transfer_eq_solve<T>::save(const std::vector<T>& portrait, const std::string path)
{
	std::ofstream file;
	file.open(path);
	int counter = 0;
	for(const auto &value: portrait) { file << ++counter << ' ' << value << std::endl;  }
	file.close();
}

#endif