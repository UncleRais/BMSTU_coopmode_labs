#include "../Helpers/Foundation/Foundation.cpp"
#include "../Helpers/Foundation/Math.cpp"
#include "funcsin.cpp"

int main(int argc, char** argv) 
{
	std::vector<double> points = NonLinearSolve::solve(-100 , 100, func, NonLinearSolve::newtonmethod, 100);
	std::cout << points;
	//std::cout << NonLinearSolve::bisection(-1, 1 , func) << "\n";
	//std::cout << NonLinearSolve::newton(-1, 1 , func) << "\n";
}