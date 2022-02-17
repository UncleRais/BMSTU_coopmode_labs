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
};

template < typename T >
static void NDsolve(std::vector<funtwo>& rightpart, std::vector<T>& cond, MethodType name, T epsilon = 1e-3);

template < typename T >
static void ExplicitEuler(std::vector<funtwo>& rightpart, std::vector<T>& cond, T epsilon = 1e-3);

template < typename T >
static void ImplicitEuler(std::vector<funtwo>& rightpart, std::vector<T>& cond, T epsilon = 1e-3);

template < typename T >
static void Runge_Kutta_2(std::vector<funtwo>& rightpart, std::vector<T>& cond, T epsilon = 1e-3);
};

#endif