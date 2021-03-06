#ifndef INTEGRAL_EQUATION_CPP
#define INTEGRAL_EQUATION_CPP
#include "./integral_equation.h"

#include "../../../../../Numerical_methods_5/Helpers/Foundation/Algorithms/Gauss/Gauss.cpp"
#include "../../../../../Numerical_methods_5/Helpers/Foundation/Matrix/Matr.cpp"

template < typename T > 
void integral_equation<T>::solve_quadrature(const std::string& path, size_t _sections)
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
void integral_equation<T>::solve_simple_iterations(const std::string& path, size_t _sections, const double eps, int iterations)
{
	std::ofstream file;
	file.open(path);
	T h = (_parameters.area_.back() - _parameters.area_.front()) / _sections; 
	size_t number_of_points = _sections + 1;

	std::ofstream errors;
	errors.open("./output/errors.dat");
	std::vector<T> result; result.reserve(number_of_points);
	for(size_t i = 0; i < number_of_points; ++i) result.push_back(_parameters.f_(_parameters.area_.front() + i * h));
	std::vector<T> iterated(number_of_points, T(0));
	const int _iterations = iterations;
	while(iterations > 0) 
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
					const T a_k = (k == 0 || k == number_of_points-1) ? h/2 : h;
					sum += (this->_parameters).lambda_*(this->_parameters).K_(x_i, x_k)*result[k]*a_k;
				}
				return sum;
			}();
			iterated[i] = c_i+f_i;
		}
		const T _norm = norm(result-iterated);
		errors << _iterations - iterations + 1 << " " << _norm << "\n";
		result = iterated;
		// if (_norm<eps) { break; }
		--iterations;
		for(size_t i = 0; i < result.size(); ++i) file << _parameters.area_.front()+i*h << " " << result[i] << " "; 
			file << "\n";
	}
	errors.close();

	file.close();
}

template < typename T > 
void integral_equation<T>::solve_degenerate(const std::string& path, size_t sections)
{
	T h = (_parameters.area_.back() - _parameters.area_.front()) / sections;  
	size_t size = _parameters.phi_.size();
	Matr<T> matrix(size , T{0});
	std::vector<T> right_part; right_part.reserve(size);
	std::vector<T> x; x.reserve(sections);
	for(size_t i = 0; i < sections + 1; ++i) x.push_back(_parameters.area_.front() + (i)*h);

	auto integrate = [this, sections, h, x](std::function<T(T)> f, std::function<T(T)> g) -> T 
    {
        T sum = 0;
        for(size_t i = 0; i < sections; ++i) 
       		//sum += f(x[i]) * g(x[i]);
       		sum += (f(x[i]) * g(x[i]) + f(x[i + 1]) * g(x[i + 1]))/2;
        return(sum*h);
    };

	for(size_t i = 0; i < size; ++i)
	{
		right_part.push_back(integrate(_parameters.psi_[i], _parameters.f_));
		for(size_t j = 0; j < size; ++j)
		{
			matrix.at(i, j) = -_parameters.lambda_ * integrate(_parameters.psi_[i], _parameters.phi_[j]);
		}
		matrix.at(i, i) += T{1};
	}

	auto result = Gauss::solve(matrix, right_part);

	std::ofstream file;
	file.open(path);
	for(size_t i = 0; i < result.size(); ++i) file << result[i] <<"\n"; 
	file.close();

}



template < typename T > 
void integral_equation<T>::solve_singular(const std::string& path, size_t sections)
{
	T length = 2 * pi / sections;
	std::vector<std::array<T,2>> k; k.reserve(sections);
	std::vector<std::array<T,2>> c; c.reserve(sections);
	std::vector<std::array<T,2>> n; n.reserve(sections);
	std::vector<T> right_part; right_part.reserve(sections + 1);
	Matr<T> matrix(sections + 1, T{length});

	for(size_t i = 1; i < sections + 1; ++i)
	{
		T var1 = length*(i-0.5), var2 = length*(i-1);

		k.push_back({ cos(var1) , sin(var1) });
		c.push_back({ cos(var2) , sin(var2) });
		n.push_back({ cos(var1) , sin(var1) });
		right_part.push_back(_parameters.F_(var1));
	}
	right_part.push_back(T{0});

	auto scalar = [](const std::array<T,2>& a, const std::array<T,2>& b) -> T 
    {
        return(a[0]*b[0] + a[1]*b[1]); 
    };

	for(size_t i = 0; i < sections; ++i)
	{
		for(size_t j = 0; j < sections; ++j)
			matrix.at(i, j) *= scalar(_parameters.Q_(k[i], c[j]), n[i]);
		matrix.at(i, sections) = T{1}; 
	}
	matrix.at(sections, sections) = T{0};

	//AlgPrint::printsystem(matrix, right_part);

	auto result = Gauss::solve(matrix, right_part);

	std::ofstream file;
	file.open(path);
	for(size_t i = 0; i < result.size(); ++i) file << c[i][0] << " " << c[i][1] << " " << result[i] << "\n"; 
	file.close();

}
#endif