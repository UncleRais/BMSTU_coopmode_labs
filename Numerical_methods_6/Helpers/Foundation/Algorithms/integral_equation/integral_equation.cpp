#ifndef INTEGRAL_EQUATION_CPP
#define INTEGRAL_EQUATION_CPP
#include "./integral_equation.h"

#include "../../../../../Numerical_methods_5/Helpers/Foundation/Algorithms/Gauss/Gauss.cpp"
#include "../../../../../Numerical_methods_5/Helpers/Foundation/Matrix/Matr.cpp"

template < typename T > 
void integral_equation<T>::solve_quadrature(const std::string& path)
{
	T h = (_parameters.area_.back() - _parameters.area_.front()) / _sections; 
	size_t number_of_points = _sections + 1;

	std::vector<T> grid; grid.reserve(number_of_points);
	std::vector<T> right_part; right_part.reserve(number_of_points);
	std::vector<T> coef_a(number_of_points, h);

	for(size_t i = 0; i < number_of_points; ++i) 
	{
		grid.push_back(_parameters.area_.front() + i * h);
		right_part.push_back(_parameters.f_(grid[i]));
	};
	
	Matr<T> matrix(number_of_points, T{0});

	for(size_t i = 0; i < number_of_points; ++i)
	{
		for(size_t k = 0; k < number_of_points; ++k)
			matrix.at(i,k) = -_parameters.lambda_ * _parameters.K_(grid[i], grid[k]) * coef_a[k];
		matrix.at(i, i)  += 1;
	}
	
	auto res = Gauss::solve(matrix, right_part);

	std::ofstream file;
	file.open(path);
	for(size_t i = 0; i < res.size(); ++i) file << grid[i] << " " << res[i] << "\n"; 
	file.close();

}

template < typename T > 
void integral_equation<T>::solve_simple_iterations(const std::string& path)
{
	
}
#endif