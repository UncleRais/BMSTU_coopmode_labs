#include "../../Numerical_methods_5/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Algorithms/integral_equation/integral_equation.cpp"
#include "../../Numerical_methods_5/Helpers/Foundation/Algorithms/Gauss/Gauss.cpp"

#include <ctime>

#include "test2.cpp"


int main(int argc, char** argv) 
{
    const integral_equation_parameters<double> params(lambda, f, K, M);		//Параметры уравнения
	std::string path = "./output/solution22.dat";							//Путь
	size_t N = 100; 														//Количество разбиений 

	integral_equation<double> model(params, N);

	size_t start_time =  clock();
	// model.solve_quadrature(path);
	model.solve_simple_iterations(path);
	size_t end_time = clock(); 
	std::cout << "Time: "<< end_time - start_time << "\n"; 

	// Matr<double> matrix({1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1});
	// std::vector<double> vec = {0,0,3,0};
	// auto res = Gauss::solve(matrix, vec);
	// std::cout << res;

 }