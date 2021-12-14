#include "../Helpers/Foundation/Foundation.cpp"
#include "../Helpers/Foundation/Math.cpp"
// #include "funcsin.cpp"
#include "func23.cpp"

int main(int argc, char** argv) 
{
	const std::vector<vFunc> F = {_func1, _func2};
	const std::vector<vFunc> dF = {d_func1_dx, d_func1_dy, d_func2_dx, d_func2_dy};
	NonLinearSolve::convergeArea(F, {}, 20,"./data/", false);
	// std::cout << NonLinearSolve::system_newton(F, dF, 30, {-47.5, 30.5});
	// std::vector<double> points = NonLinearSolve::solve(-100 , 100, func, NonLinearSolve::newtonmethod, 100);
	// std::cout << points;
	//std::cout << NonLinearSolve::bisection(-1, 1 , func) << "\n";
	//std::cout << NonLinearSolve::newton(-1, 1 , func) << "\n";
}