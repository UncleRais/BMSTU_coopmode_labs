#include "../Helpers/Foundation/Foundation.cpp"
#include "../Helpers/Foundation/Math.cpp"
#include "func20.cpp"

int main(int argc, char** argv) 
{
	Grid elem(-1 , 1, 15);
	elem.setunifgrid(func);
	elem.calculateLagrange(-1 , 1, 100);
	//elem.printGrid();
	save(elem , "Lab3/output" , "vecx20", "vecy20", "vecintery20");
	return 0;
}