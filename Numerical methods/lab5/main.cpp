#include "../Helpers/Foundation/Foundation.cpp"
#include "../Helpers/Foundation/Math.cpp"
#include "func20.cpp"

int main(int argc, char** argv) 
{
	std::cout << NonLinearSolve::bisection(-1, 0 , func) << "\n";
	std::cout << NonLinearSolve::newton(-1, 0 , func) << "\n";
}