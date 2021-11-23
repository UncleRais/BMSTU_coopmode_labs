#include "../Helpers/Foundation/Foundation.cpp"
#include "../Helpers/Foundation/Math.cpp"

int main(int argc, char** argv) 
{
	Matr<double> matrix;

	init(matrix, "./data/EIGEN20.dat");
	std::cout << matrix << "\n";

	std::cout << Eigen::solve(matrix);

	
	// const std::string var = "20";
	// save(elem , "Lab3/output" , "vecx" + var, "vecy" + var, "vecintery" + var);

}