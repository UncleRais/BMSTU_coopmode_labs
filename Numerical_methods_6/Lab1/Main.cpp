#include "../../Numerical_methods_5/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Foundation.cpp"
#include "../Helpers/Foundation/Algorithms/Algorithms.cpp"
#include "../Helpers/Foundation/Algorithms/ODE/ODE.cpp"
#include "task2.cpp"

/*
ExplicitEuler_,
ImplicitEuler_,
Symmetrical_,
Runge_Kutta_4_,
Runge_Kutta_2_,
Adams_Bashforth_,orecast_correction_,
*/
int main(int argc, char** argv) 
{
	typedef double(*funtwo)(std::vector<double>&);
	std::vector<funtwo> rightpart({f1, f2});
	ODE::NDsolve(rightpart, cond, ODE::Runge_Kutta_4_adaptive_);
	// ODE::NDsolve(rightpart, cond, ODE::Symmetrical_);
}