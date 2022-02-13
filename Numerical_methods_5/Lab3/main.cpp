#include "../Helpers/Foundation/Foundation.cpp"
#include "../Helpers/Foundation/Math.cpp"
#include "funcxx.cpp"

int main(int argc, char** argv) 
{
	Grid elem(-1 , 1, 4);
	//elem.setunifgrid(func);
	elem.setchebishevgrid(func);
	//elem.calculateLagrange(-1, 1, 1000);
	elem.calculateSpline(-1 , 1, 1000);
	// elem.printGrid();

	// std::vector<double> norms = {};
	// int n = 64;

	// Grid elem1(-1.25, 1.25, n);
	// elem1.setunifgrid(func);
	// elem1.calculateSpline(-1.25 , 1.25, 1000);
	// norms.push_back(elem1.funcnorm(func));

	// Grid elem2(-1.25 , 1.25, 2 * n);
	// elem2.setunifgrid(func);
	// elem2.calculateSpline(-1.25 , 1.25, 1000);
	// norms.push_back(elem2.funcnorm(func));
	
	// std::cout << "Order: " << -log2(norms[1]/norms[0])<< "\n";
	
	const std::string var = "20";
	save(elem , "Lab3/output" , "vecx" + var, "vecy" + var, "vecintery" + var);

}