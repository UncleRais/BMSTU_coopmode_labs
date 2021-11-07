#include "../Helpers/Foundation/Foundation.cpp"
#include "../Helpers/Foundation/Math.cpp"
#include "func20.cpp"

int main(int argc, char** argv) 
{
	Grid elem(-1 , 1, 10);
	elem.setunifgrid(func);
	elem.calculateSpline(-1 , 1, 5000);
	//elem.setunifgrid(func);
	// elem.calculateLagrange(-1 , 1, 1000);
	// elem.printGrid();
	// std::cout<< "Function norm: " << elem.funcnorm(func) << "\n";
	const std::string var = "20";
	save(elem , "Lab3/output" , "vecx" + var, "vecy" + var, "vecintery" + var);


	// std::vector<double> A = {1 , 2 , 3};
	// std::vector<double> B = {1 , 5 , 3 , 1};
	// std::vector<double> C = {2 , 1 , 1};
	// std::vector<double> D = {5 , 6 , 8, -3};
	// std::cout<< Banish::solve(A , B , C , D);

}