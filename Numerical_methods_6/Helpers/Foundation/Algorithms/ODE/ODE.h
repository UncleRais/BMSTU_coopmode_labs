#ifndef ODE_H
#define ODE_H

typedef double(*funtwo)(std::vector<double>&);



class ODE {

public:

enum MethodType {
	ExplicitEuler_,
	ImplicitEuler_,
	Symmetrical_,
	Runge_Kutta_4_,
	Adams_Bashforth_,
};

template < typename T >
static void NDsolve(std::vector<funtwo>& rightpart, std::vector<T>& cond, MethodType name, T epsilon = 1e-3);

template < typename T >
static void ExplicitEuler(std::vector<funtwo>& rightpart, std::vector<T>& cond, T epsilon = 1e-3);

template < typename T >
static void ImplicitEuler(std::vector<funtwo>& rightpart, std::vector<T>& cond, T epsilon = 1e-3);
};

#endif