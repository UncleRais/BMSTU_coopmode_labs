#include "../../Numerical_methods_5/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Algorithms/integral_equation/integral_equation.cpp"
#include "../../Numerical_methods_5/Helpers/Foundation/Algorithms/Gauss/Gauss.cpp"

#include <ctime>


#include "test2.cpp"
#include "test3.cpp"
#include "degenerate.cpp"



int main(int argc, char** argv) 
{
    const integral_equation_parameters<double> params(lambda, f, K, phi, psi, F, Q, M);		//Параметры уравнения
	std::string path = "./output/solution_";			
	std::string format = ".dat";			   
	size_t N = 100; 														//Количество разбиений 

	integral_equation<double> model(params);

	size_t start_time =  clock();
	model.solve_quadrature(path + "quad" + format, N);
	size_t end_time = clock(); 
	std::cout << "solve_quadrature Time: "<< end_time - start_time << "\n"; 

	start_time =  clock();
	model.solve_simple_iterations(path + "simple" + format, N, 1e-10, 10);
	end_time = clock(); 
	std::cout << "solve_simple_iterations Time: "<< end_time - start_time << "\n"; 

	start_time =  clock();
	model.solve_degenerate(path + "degenerate" + format, 80);
	end_time = clock(); 
	std::cout << "solve_degenerate Time: "<< end_time - start_time << "\n"; 

	start_time =  clock();
	model.solve_singular(path + "singular" + format, 200);
	end_time = clock(); 
	std::cout << "solve_singular Time: "<< end_time - start_time << "\n"; 

	model.solve_quadrature(path + "h" + format, 4*N);
	model.solve_quadrature(path + "2h" + format, 2*N);
	model.solve_quadrature(path + "4h" + format, N);

 }