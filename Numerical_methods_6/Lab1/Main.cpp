#include "../../Numerical_methods_5/Helpers/Foundation/Foundation.cpp"
#include "../../Numerical_methods_6/Helpers/Foundation/Foundation.cpp"
#include "../Helpers/Foundation/Algorithms/Algorithms.cpp"
#include "../Helpers/Foundation/Algorithms/ODE/ODE.cpp"
// #include "task1.cpp"
// #include "task3.cpp"
#include "sys20.cpp"
#include <time.h> 


/*
ExplicitEuler_,
ImplicitEuler_,
Symmetrical_,
Runge_Kutta_2_,
Runge_Kutta_4_,
Adams_Bashforth_,
Forecast_correction_,
Runge_Kutta_4_adaptive_,
*/
int main(int argc, char** argv) 
{
	typedef double(*funtwo)(std::vector<double>&);
	std::vector<funtwo> rightpart({f1, f2});
	double h = 10e-2;
	Portrait solution,s1,s2,s3;

	// clock_t start = clock();
	// solution = ODE::NDsolve(rightpart, cond, ODE::ExplicitEuler_, h, 1e-7);
	// clock_t end = clock();
	// ODE::save(solution, "./output/solution.dat");
	// double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	// std::cout <<" The time: "<< seconds << " seconds \n";

	clock_t start2 = clock();
	solution = ODE::Phase(rightpart, cond, ODE::ExplicitEuler_, h, 1e-3);
	clock_t end2 = clock();
	ODE::save(solution, "./output/phase.dat");
	double seconds2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
	std::cout <<" The time: "<< seconds2 << " seconds \n";

	// clock_t start2 = clock();
	// solution = ODE::Phase({f1, f2, f3}, cond, ODE::ExplicitEuler_, h, 1e-3);
	// clock_t end2 = clock();
	// ODE::save(solution, "./output/phase3d.dat");
	// double seconds2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
	// std::cout <<" The time: "<< seconds2 << " seconds \n";

	// double hh = 0.03;
	// double q = 0.5;
	// s1 = ODE::NDsolve(rightpart, cond, ODE::Runge_Kutta_4_, hh, 1e-3);
	// s2 = ODE::NDsolve(rightpart, cond, ODE::Runge_Kutta_4_, q * hh, 1e-3);
	// s3 = ODE::NDsolve(rightpart, cond, ODE::Runge_Kutta_4_, q * q * hh, 1e-3);
	// double x1 = s1[16][0], x2 = s2[32][0], x3 = s3[64][0];
	// std::cout << "Order : " << log((x3 - x2)/(x2 - x1))/log(q) << "\n";
}