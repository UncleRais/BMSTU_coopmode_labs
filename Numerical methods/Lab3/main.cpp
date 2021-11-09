#include "../Helpers/Foundation/Foundation.cpp"
#include "../Helpers/Foundation/Math.cpp"
#include "func23.cpp"

int main(int argc, char** argv) 
{
	Grid elem(-5 , 5, 32);
	// elem.setunifgrid(func);
	elem.setchebishevgrid(func);
	// elem.calculateLagrange(-1, 1, 1000);
	elem.calculateSpline(-1 , 1, 1000);
	//elem.setunifgrid(func);
	// elem.calculateLagrange(-1 , 1, 1000);
	// elem.printGrid();
	std::cout<< "Function norm: " << elem.funcnorm(func) << "\n";
	const std::string var = "20";
	save(elem , "Lab3/output" , "vecx" + var, "vecy" + var, "vecintery" + var);

}