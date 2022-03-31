#include "../../Numerical_methods_5/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Algorithms/heat_transfer_eq_solve/heat_transfer_eq_solve.cpp"
#include "const20.cpp"
#include "flow_and_conductivity.cpp"


int main(int argc, char** argv) 
{
	heat_transfer_eq_solve<double> solution(cond, 1, 2);
	std::string path = "./output/solution.dat";
	//solution.parameters_info();
	//solution.NPDsolve_Linear(path, 1, 1, 300, 100, 10, 1, 1);
	//solution.NPDsolve_Newton(path, 1, 1, 2, 10, 10, 1);
	//solution.NPDsolve_NONLinear(path, true, true, 300, 100, 10, 1, 1, 1);
}