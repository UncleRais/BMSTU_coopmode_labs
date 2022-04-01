#include "../../Numerical_methods_5/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Algorithms/heat_transfer_eq_solve/heat_transfer_eq_solve.cpp"
#include "const20.cpp"
#include "flow_and_conductivity.cpp"


int main(int argc, char** argv) 
{
	heat_transfer_eq_solve<double> solution(cond, 1, 1);
	std::string path = "./output/solution.dat";
	//solution.parameters_info();
	solution.NPDsolve_Linear(path, 0, 1, 1000, 50, 1, 1, 1);
	//solution.NPDsolve_Newton(path, 1, 1, 2, 10, 10, 1);
	//solution.NPDsolve_NONLinear(path, true, true, 300, 100, 10, 1, 1, 1);

	//solution.NPDsolve_Linear("./output/solution_exp_3t.dat", 1, 1, 4000, 16, 1, 1, 0);
	//solution.NPDsolve_Linear("./output/solution_exp_2t.dat", 1, 1, 2000, 16, 1, 1, 0);
	//solution.NPDsolve_Linear("./output/solution_exp_3x.dat", 1, 1, 1000, 16, 1, 1, 0);
	//solution.NPDsolve_Linear("./output/solution_exp_2x.dat", 1, 1, 1000, 8, 1, 1, 0);
	//solution.NPDsolve_Linear("./output/solution_exp_1x.dat", 1, 1, 1000, 4, 1, 1, 0);
}