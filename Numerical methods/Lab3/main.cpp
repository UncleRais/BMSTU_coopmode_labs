#include "../Helpers/Foundation/Foundation.cpp"
#include "../Helpers/Foundation/Math.cpp"
#include "func20.cpp"

int main(int argc, char** argv) 
{
	Grid elem(-1 , 1, 100);
	elem.setchebishevgrid(func);
	//elem.printGrid();
	save(elem , "Lab3/output" , "vecx20", "vecy20");
	return 0;
}