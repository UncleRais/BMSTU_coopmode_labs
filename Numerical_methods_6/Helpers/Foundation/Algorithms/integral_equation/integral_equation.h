#ifndef INTEGRAL_EQUATION_H
#define INTEGRAL_EQUATION_H

#include "../../../../../Numerical_methods_5/Helpers/Foundation/Algorithms/Algorithms.cpp"
#include "../../../../../Numerical_methods_6/Helpers/Foundation/Foundation.cpp"


template<typename T>
struct TemplateTypes{
    typedef std::function <T (T)> func1d;
    typedef std::function <T (T , T)> func2d; 
    typedef std::function <std::array<double, 2> (std::array<double, 2> , std::array<double, 2>)> vec_func_vec2d; 
	typedef std::vector<func1d> vector_func1d;
};

template<class T>
struct integral_equation_parameters final {
	T lambda_;					      //Коэффициент перед интегралом
	TemplateTypes<double>::func1d f_; //Правая часть
	TemplateTypes<double>::func2d K_; //Ядро оператора Фредгольма 
	std::array<T, 2> area_;           //Область интегрирования

	TemplateTypes<double>::vector_func1d phi_, psi_; //Массивы функций вырожденного ядра

	TemplateTypes<double>::func1d F_; //Правая часть для задачи сингулярного ядра
	TemplateTypes<double>::vec_func_vec2d  Q_; //Сингулярное ядро

	integral_equation_parameters(const integral_equation_parameters& copy)
	{
		lambda_ = copy.lambda_;
		f_ = copy.f_;
		K_ = copy.K_;
		phi_ = copy.phi_;
		psi_ = copy.psi_;
		F_ = copy.F_;
		Q_ = copy.Q_;
		area_ = copy.area_;
	};

	integral_equation_parameters(T lambda, 
								 TemplateTypes<double>::func1d f, 
								 TemplateTypes<double>::func2d K,
								 TemplateTypes<double>::vector_func1d phi,
								 TemplateTypes<double>::vector_func1d psi,
								 TemplateTypes<double>::func1d F,
								 TemplateTypes<double>::vec_func_vec2d Q,
								 const std::array<T, 2>& area)
	{
		lambda_ = lambda;
		f_ = f;
		K_ = K;
		phi_ = phi;
		psi_ = psi;
		F_ = F;
		Q_ = Q;
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

void solve_degenerate(const std::string& path, size_t sections);

void solve_singular(const std::string& path, size_t sections);

};

#endif