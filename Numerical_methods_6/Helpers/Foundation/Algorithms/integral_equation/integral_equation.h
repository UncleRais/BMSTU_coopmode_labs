#ifndef INTEGRAL_EQUATION_H
#define INTEGRAL_EQUATION_H

#include "../../../../../Numerical_methods_5/Helpers/Foundation/Algorithms/Algorithms.cpp"
#include "../../../../../Numerical_methods_6/Helpers/Foundation/Foundation.cpp"


template<typename T>
struct TemplateTypes{
    typedef std::function <T (T)> func1d;
    typedef std::function <T (T , T)> func2d; 
};

template<class T>
struct integral_equation_parameters final {
	T lambda_;					      //Коэффициент перед интегралом
	TemplateTypes<double>::func1d f_; //Правая часть
	TemplateTypes<double>::func2d K_; //Ядро оператора Фредгольма 
	std::array<T, 2> area_;           //Область интегрирования

	integral_equation_parameters(const integral_equation_parameters& copy)
	{
		lambda_ = copy.lambda_;
		f_ = copy.f_;
		K_ = copy.K_;
		area_ = copy.area_;
	};

	integral_equation_parameters(T lambda, 
								 TemplateTypes<double>::func1d f, 
								 TemplateTypes<double>::func2d K,
								 const std::array<T, 2>& area)
	{
		lambda_ = lambda;
		f_ = f;
		K_ = K;
		area_ = area;
	};
};

template <class T>
class integral_equation {

public:
integral_equation_parameters<T> _parameters;

public:
integral_equation(const integral_equation_parameters<T>& params): _parameters(params) {};

void solve_quadrature(const std::string& path, size_t sections);

void solve_simple_iterations(const std::string& path, size_t sections, const double eps = 10e-5, int iterations = 3);

};

#endif