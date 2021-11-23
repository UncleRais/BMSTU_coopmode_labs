#include "../Helpers/Foundation/Foundation.cpp"
#include "../Helpers/Foundation/Math.cpp"

int main(int argc, char** argv) 
{
	Matr<double> matrix;

	init(matrix, "./data/EIGEN20.dat");
	std::cout << matrix << "\n";

	const auto eigenValues = Eigen::solve(matrix);
	std::cout << eigenValues << "\n";

	// const std::string var = "20";
	// save(elem , "Lab3/output" , "vecx" + var, "vecy" + var, "vecintery" + var);

}