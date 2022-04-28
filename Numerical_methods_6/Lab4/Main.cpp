#include "../../Numerical_methods_5/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Algorithms/poisson_eq_solve/poisson_eq_solve.cpp"

#include "var3.cpp"


int main(int argc, char** argv) 
{
	typedef double type; 

	std::string path = "./output/solution.dat";

	std::array<size_t, 3> N = {8, 8, 10}; //Количество разбиений (x1 / x2 / время)
	type finish = 1.; //Конечное время

	poisson_eq_solve<type> model(f, G, M);
	model.solve(path, N , finish);

	//double N = 100, M = 500;

	// model.solve("./output/solution_1x1t.dat", M, N, numberofresults);
	// model.solve("./output/solution_2x1t.dat", M, 2*N, numberofresults);
	// model.solve("./output/solution_3x1t.dat", M, 4*N, numberofresults);
	// model.solve("./output/solution_1x2t.dat", 2*M, N, numberofresults);
	// model.solve("./output/solution_2x2t.dat", 2*M, 2*N, numberofresults);
	// model.solve("./output/solution_3x2t.dat", 2*M, 4*N, numberofresults);
	// model.solve("./output/solution_1x3t.dat", 4*M, N, numberofresults);
	// model.solve("./output/solution_2x3t.dat", 4*M, 2*N, numberofresults);
	// model.solve("./output/solution_3x3t.dat", 4*M, 4*N, numberofresults);

}