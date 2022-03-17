#include "../../Numerical_methods_5/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Algorithms/heat_transfer_eq_solve/heat_transfer_eq_solve.cpp"
#include "const20.cpp"
#include "flow_and_conductivity.cpp"


int main(int argc, char** argv) 
{
	heat_transfer_eq_solve<double> solution(cond, 1, 1);
	//solution.parameters_info();
	auto sol = solution.NDsolve(0, 0, 300, 10, 1.0);
	std::string path = "./output/solution.dat";
	heat_transfer_eq_solve<double>::save(sol, path);
}