#include "../../Numerical_methods_5/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Algorithms/heat_transfer_eq_solve/heat_transfer_eq_solve.cpp"
#include "lab.cpp"


int main(int argc, char** argv) 
{
	heat_transfer_eq_solve<double> solution(cond, 1, 3);
	std::string path = "./output/solution.dat";
	//solution.parameters_info();
	solution.NPDsolve_Linear(path, 0, 0, 5000, 50, 100, 1, 0);
	//solution.NPDsolve_Newton(path, 1, 1, 2, 10, 10, 1);
	//solution.NPDsolve_NONLinear(path, false, false, 5000, 50, 500, 1, 1, 1);

	double method = 1, N = 1000, M = 1000;

	solution.NPDsolve_Linear("./output/solution_1x1t.dat", 0, 0, M, N, 100, 1, method);
	solution.NPDsolve_Linear("./output/solution_2x1t.dat", 0, 0, M, 2*N, 100, 1, method);
	solution.NPDsolve_Linear("./output/solution_3x1t.dat", 0, 0, M, 4*N, 100, 1, method);
	solution.NPDsolve_Linear("./output/solution_1x2t.dat", 0, 0, 2*M, N, 100, 1, method);
	solution.NPDsolve_Linear("./output/solution_2x2t.dat", 0, 0, 2*M, 2*N, 100, 1, method);
	solution.NPDsolve_Linear("./output/solution_3x2t.dat", 0, 0, 2*M, 4*N, 100, 1, method);
	solution.NPDsolve_Linear("./output/solution_1x3t.dat", 0, 0, 4*M, N, 100, 1, method);
	solution.NPDsolve_Linear("./output/solution_2x3t.dat", 0, 0, 4*M, 2*N, 100, 1, method);
	solution.NPDsolve_Linear("./output/solution_3x3t.dat", 0, 0, 4*M, 4*N, 100, 1, method);

}