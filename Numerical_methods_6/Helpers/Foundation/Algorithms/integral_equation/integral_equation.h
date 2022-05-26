#ifndef INTEGRAL_EQUATION_H
#define INTEGRAL_EQUATION_H

#include "../../../../../Numerical_methods_5/Helpers/Foundation/Algorithms/Algorithms.cpp"
#include "../../../../../Numerical_methods_6/Helpers/Foundation/Foundation.cpp"


template<typename T>
struct TemplateTypes{
    typedef std::function <T (T)> func1d;
    typedef std::function <T (T , T)> func2d; 
    typedef std::function <T (T)> scal_func_vec1d; 
    typedef std::function <std::array<double, 2> (std::array<double, 2> , std::array<double, 2>)> vec_func_vec2d; 
};

template<class T>
struct integral_equation_parameters final {
	T lambda_;					      //Коэффициент перед интегралом
	TemplateTypes<double>::func1d f_; //Правая часть
	TemplateTypes<double>::func2d K_; //Ядро оператора Фредгольма 
	std::array<T, 2> area_;           //Область интегрирования

	TemplateTypes<double>::scal_func_vec1d F_; //Правая часть как скалярная функция векторного аргумента
	TemplateTypes<double>::vec_func_vec2d  Q_; //Сингулярное ядро

	integral_equation_parameters(const integral_equation_parameters& copy)
	{
		lambda_ = copy.lambda_;
		f_ = copy.f_;
		K_ = copy.K_;
		F_ = copy.F_;
		Q_ = copy.Q_;
		area_ = copy.area_;
	};

	integral_equation_parameters(T lambda, 
								 TemplateTypes<double>::func1d f, 
								 TemplateTypes<double>::func2d K,
								 TemplateTypes<double>::scal_func_vec1d F,
								 TemplateTypes<double>::vec_func_vec2d Q,
								 const std::array<T, 2>& area)
	{
		lambda_ = lambda;
		f_ = f;
		K_ = K;
		F_ = F;
		Q_ = Q;
		area_ = area;
	};
};

template <class T>
class integral_equation {

public:
size_t _sections;
integral_equation_parameters<T> _parameters;

public:
integral_equation(const integral_equation_parameters<T>& params, size_t sections): 
_sections(sections), _parameters(params) {};

void solve_quadrature(const std::string& path);

void solve_simple_iterations(const std::string& path, const double eps = 10e-5);

void solve_degenerate(const std::string& path);

void solve_singular(const std::string& path, size_t sections);

};

#endif