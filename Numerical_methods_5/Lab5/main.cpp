#include "../Helpers/Foundation/Foundation.cpp"
#include "../Helpers/Foundation/Math.cpp"
// #include "funcsin.cpp"
#include "funcx.cpp"

int main(int argc, char** argv) 
{
	//const std::vector<vFunc> F = {_func1, _func2};
	//const std::vector<vFunc> dF = {d_func1_dx, d_func1_dy, d_func2_dx, d_func2_dy};
	//NonLinearSolve::convergeArea(F, {}, 20,"./data/", false);
	// std::cout << NonLinearSolve::system_newton(F, dF, 30, {-47.5, 30.5});
	// std::vector<double> points = NonLinearSolve::solve(-100 , 100, func, NonLinearSolve::newtonmethod, 100);
	// std::cout << points;
	double a = -2, b = 5.5;
	auto f = func1;
	std::cout << NonLinearSolve::localization(a, b, f, 10000);
	NonLinearSolve::chord(a, b, f, 1e-9, true);
	NonLinearSolve::newton(a, b, f,  NonLinearSolve::df, 1e-9, true);
	NonLinearSolve::bisection(a, b, f, 1e-9, true);
	std::cout << func(a) <<" " << func(b);
}