#ifndef ODE_H
#define ODE_H

#include "../../../../../Numerical_methods_5/Helpers/Foundation/Foundation.cpp"
#include "../../../../../Numerical_methods_6/Helpers/Foundation/Foundation.cpp"

typedef double(*funtwo)(std::vector<double>&);

class ODE {
public:
enum MethodType {
	ExplicitEuler_,
	ImplicitEuler_,
	Symmetrical_,
	Runge_Kutta_4_,
	Runge_Kutta_2_,
	Adams_Bashforth_,
	Forecast_correction_,
};

template < typename T >
static void NDsolve(const std::vector<funtwo>& rightpart, const std::vector<T>& cond, MethodType name, T epsilon = 1e-3);

template < typename T >
static void ExplicitEuler(const std::vector<funtwo>& rightpart, const std::vector<T>& cond, int timestamps,
						  int systemsize, T h, std::vector<std::vector<T>>& x, T epsilon = 1e-3);
template < typename T >
static void ImplicitEuler(const std::vector<funtwo>& rightpart, const std::vector<T>& cond, int timestamps,
						  int systemsize, T h, std::vector<std::vector<T>>& x, T epsilon = 1e-3);
template < typename T >
static void Symmetrical(const std::vector<funtwo>& rightpart, const std::vector<T>& cond, int timestamps,
						  int systemsize, T h, std::vector<std::vector<T>>& x, T epsilon = 1e-3);
template < typename T >
static void Runge_Kutta_2(const std::vector<funtwo>& rightpart, const std::vector<T>& cond, int timestamps,
						  int systemsize, T h, std::vector<std::vector<T>>& x, T epsilon = 1e-3);
template < typename T >
static void Runge_Kutta_4(const std::vector<funtwo>& rightpart, const std::vector<T>& cond, int timestamps,
						  int systemsize, T h, std::vector<std::vector<T>>& x, T epsilon = 1e-3);
template < typename T >
static void Adams_Bashforth(const std::vector<funtwo>& rightpart, const std::vector<T>& cond, int timestamps,
						   int systemsize, T h, std::vector<std::vector<T>>& x, T epsilon = 1e-3);
template < typename T >
static void Forecast_correction(const std::vector<funtwo>& rightpart, const std::vector<T>& cond, int timestamps,
						        int systemsize, T h, std::vector<std::vector<T>>& x, T epsilon = 1e-3);
};

#endif