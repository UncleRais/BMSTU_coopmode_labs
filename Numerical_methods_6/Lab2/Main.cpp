#include "../../Numerical_methods_5/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Algorithms/heat_transfer_eq_solve/heat_transfer_eq_solve.cpp"
#include "const20.cpp"
#include "flow_and_conductivity.cpp"


int main(int argc, char** argv) 
{
	heat_transfer_eq_solve<double> solution(cond, 1, 1);
	//solution.parameters_info();
	std::string path = "./output/solution.dat";
	solution.NDsolve(path, 0, 1, 300, 10, 10, 0.1, 1/2);
}