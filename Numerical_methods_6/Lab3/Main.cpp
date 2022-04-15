#include "../../Numerical_methods_5/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Algorithms/wave_eq_solve/wave_eq_solve.cpp"

#include "task1.cpp"


int main(int argc, char** argv) 
{
	typedef double ty; 
	ty start = -2, L = 2, time = 10, a = 0.98;
	std::string path = "./output/solution.dat";
	size_t timestamps = 1000, sections = 400, numberofresults = 1;

	std::cout << "gamma = " <<  a * time / timestamps * sections / (L - start) << "\n";

	wave_eq_solve<ty> model(f, fxx, g, phi, xi, start, L, time, a);
	model.solve(path, timestamps, sections, numberofresults);

}