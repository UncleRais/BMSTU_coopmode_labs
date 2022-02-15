#include "../../Numerical_methods_5/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Foundation.cpp"
#include "../Helpers/Foundation/Algorithms/Algorithms.cpp"
#include "../Helpers/Foundation/Algorithms/ODE/ODE.cpp"
#include "sys20.cpp"


int main(int argc, char** argv) 
{
	typedef double(*funtwo)(std::vector<double>&);
	std::vector<funtwo> rightpart({f1, f2});
	ODE::NDsolve(rightpart, cond, ODE::ExplicitEuler_);
}