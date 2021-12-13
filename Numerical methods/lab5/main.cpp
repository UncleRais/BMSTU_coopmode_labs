#include "../Helpers/Foundation/Foundation.cpp"
#include "../Helpers/Foundation/Math.cpp"
// #include "funcsin.cpp"
#include "func20.cpp"

int main(int argc, char** argv) 
{
	const std::vector<vFunc> F = {_func1, _func2};
	// std::cout << NonLinearSolve::d_vFunc(_func1, {2,1}, {true, true});
	// std::cout << NonLinearSolve::jacobi(F, {3, 3});
	std::cout << NonLinearSolve::system_newton(F);
	// std::vector<double> points = NonLinearSolve::solve(-100 , 100, func, NonLinearSolve::newtonmethod, 100);
	// std::cout << points;
	//std::cout << NonLinearSolve::bisection(-1, 1 , func) << "\n";
	//std::cout << NonLinearSolve::newton(-1, 1 , func) << "\n";
}