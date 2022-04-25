#include "../../Numerical_methods_5/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Algorithms/wave_eq_solve/wave_eq_solve.cpp"

#include "test1.cpp"


int main(int argc, char** argv) 
{
	typedef double ty; 
	ty start = 0, L = 1, time = 1, a = 1;
	std::string path = "./output/solution.dat";
	size_t timestamps = 1000, sections = 400, numberofresults = 10;

	std::cout << "gamma = " <<  a * time / timestamps * sections / (L - start) << "\n";

	wave_eq_solve<ty> model(f, fxx, g, phi, xi, start, L, time, a);
	model.solve(path, timestamps, sections, numberofresults);

	double N = 100, M = 500;

	model.solve("./output/solution_1x1t.dat", M, N, numberofresults);
	model.solve("./output/solution_2x1t.dat", M, 2*N, numberofresults);
	model.solve("./output/solution_3x1t.dat", M, 4*N, numberofresults);
	model.solve("./output/solution_1x2t.dat", 2*M, N, numberofresults);
	model.solve("./output/solution_2x2t.dat", 2*M, 2*N, numberofresults);
	model.solve("./output/solution_3x2t.dat", 2*M, 4*N, numberofresults);
	model.solve("./output/solution_1x3t.dat", 4*M, N, numberofresults);
	model.solve("./output/solution_2x3t.dat", 4*M, 2*N, numberofresults);
	model.solve("./output/solution_3x3t.dat", 4*M, 4*N, numberofresults);

}