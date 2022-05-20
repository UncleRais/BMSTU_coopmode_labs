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
	coef_a.front() = h/2;
	coef_a.back() = h/2;

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
void integral_equation<T>::solve_simple_iterations(const std::string& path, const double eps)
{
	T h = (_parameters.area_.back() - _parameters.area_.front()) / _sections; 
	size_t number_of_points = _sections + 1;

	std::vector<T> result(number_of_points, T(0));
	std::vector<T> iterated(number_of_points, T(0));;
	while(true) 
	{
		for(size_t i = 0; i < number_of_points; ++i)
		{
			const T x_i = _parameters.area_.front()+i*h;
			const T f_i = _parameters.f_(x_i);
			const T c_i = [this, &h, &number_of_points, &x_i, &result]() -> T {
				T sum = T(0);
				for(size_t k = 0; k < number_of_points; ++k)
				{
					const T x_k = (this->_parameters).area_.front()+k*h;
					const T a_k = h;
					sum += (this->_parameters).lambda_*(this->_parameters).K_(x_i, x_k)*result[k]*a_k;
				}
				return sum;
			}();
			iterated[i] = c_i+f_i;
		}
		const T _norm = norm(result-iterated);
		result = iterated;
		if (_norm<eps) { break; }
	}
	std::ofstream file;
	file.open(path);
	for(size_t i = 0; i < result.size(); ++i) file << _parameters.area_.front()+i*h << " " << result[i] << "\n"; 
	file.close();
}
#endif