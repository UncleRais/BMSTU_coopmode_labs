#include "../../Numerical_methods_5/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Algorithms/poisson_eq_solve/poisson_eq_solve.cpp"

#include "test3.cpp"


int main(int argc, char** argv) 
{
	typedef double type; 

	std::string path = "./output/solution.dat";

	std::array<size_t, 3> N = {30, 30, 1000}; //Количество разбиений (x1 / x2 / время)
	type finish = 1.; //Конечное время

	poisson_eq_solve<type> model(f, G, IndG, M);
	model.solve(path, N , finish);

	//double N = 100, M = 500;

	model.solve("./output/solution_1x1y.dat", {5, 5, 1000} , finish);
	model.solve("./output/solution_2x1y.dat", {10, 5, 1000} , finish);
	model.solve("./output/solution_3x1y.dat", {20, 5, 1000} , finish);
	model.solve("./output/solution_1x2y.dat", {5, 10, 1000} , finish);
	model.solve("./output/solution_2x2y.dat", {10, 10, 1000} , finish);
	model.solve("./output/solution_3x2y.dat", {20, 10, 1000} , finish);
	model.solve("./output/solution_1x3y.dat", {5, 20, 1000} , finish);
	model.solve("./output/solution_2x3y.dat", {10, 20, 1000} , finish);
	model.solve("./output/solution_3x3y.dat", {20, 20, 1000} , finish);
}