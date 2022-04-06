#include "../../Numerical_methods_5/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Algorithms/wave_eq_solve/wave_eq_solve.cpp"

#include "var23.cpp"


int main(int argc, char** argv) 
{
	typedef double ty; 
	ty L = 1, time = 10, a = 1;
	std::string path = "./output/solution.dat";

	wave_eq_solve<ty> model(f, fxx, g, phi, xi, L, time, a);
	model.solve(path, 1000, 100, 1);

}