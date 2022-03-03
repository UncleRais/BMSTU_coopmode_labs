#ifndef ODE_H
#define ODE_H

#include "../../../../../Numerical_methods_5/Helpers/Foundation/Foundation.cpp"
#include "../../../../../Numerical_methods_6/Helpers/Foundation/Foundation.cpp"
#include <string>

typedef double(*funtwo)(std::vector<double>&);
typedef std::vector<std::vector<double>> Portrait;

class ODE {
public:
enum MethodType {
	ExplicitEuler_,
	ImplicitEuler_,
	Symmetrical_,
	Runge_Kutta_4_,
	Runge_Kutta_4_adaptive_,
	Runge_Kutta_2_,
	Adams_Bashforth_,
	Forecast_correction_,
};

template < typename T >
static Portrait NDsolve(const std::vector<funtwo>& rightpart, const std::vector<T>& cond,
 MethodType name, T h = 0.1, T epsilon = 1e-3);

template < typename T >
static void Phase(const std::vector<funtwo>& rightpart,
 const std::vector<T>& cond, MethodType name, T epsilon = 1e-3);
template < typename T >
static Portrait ExplicitEuler(const std::vector<funtwo>& rightpart, int timestamps,
						  int systemsize, T h, std::vector<std::vector<T>>& x, T epsilon = 1e-3);
template < typename T >
static Portrait ImplicitEuler(const std::vector<funtwo>& rightpart, int timestamps,
						  int systemsize, T h, std::vector<std::vector<T>>& x, T epsilon = 1e-3);
template < typename T >
static Portrait Symmetrical(const std::vector<funtwo>& rightpart, int timestamps,
						  int systemsize, T h, std::vector<std::vector<T>>& x, T epsilon = 1e-3);
template < typename T >
static Portrait Runge_Kutta_2(const std::vector<funtwo>& rightpart, int timestamps,
						  int systemsize, T h, std::vector<std::vector<T>>& x, T epsilon = 1e-3);
template < typename T >
static Portrait Runge_Kutta_4(const std::vector<funtwo>& rightpart, int timestamps,
						  int systemsize, T h, std::vector<std::vector<T>>& x, T epsilon = 1e-3);
template < typename T >
static Portrait Runge_Kutta_4_adaptive(const std::vector<funtwo>& rightpart, const std::vector<T>& cond, int timestamps,
						  			   int systemsize, T h, std::vector<std::vector<T>>& x, T epsilon = 1e-3);
template < typename T >
static Portrait Adams_Bashforth(const std::vector<funtwo>& rightpart, int timestamps,
						   int systemsize, T h, std::vector<std::vector<T>>& x, T epsilon = 1e-3);
template < typename T >
static Portrait Forecast_correction(const std::vector<funtwo>& rightpart, int timestamps,
						        int systemsize, T h, std::vector<std::vector<T>>& x, T epsilon = 1e-3);
template < typename T >
static void save(std::vector<std::vector<T>>& portrait, std::string path);

template < typename T >
static void save(std::vector<T>& portrait, std::string path);

};

#endif