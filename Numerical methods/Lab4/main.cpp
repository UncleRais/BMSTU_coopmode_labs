#include "../Helpers/Foundation/Foundation.cpp"
#include "../Helpers/Foundation/Math.cpp"

int main(int argc, char** argv) 
{
	//Matr<double> matrix;

	//init(matrix, "./data/EIGEN20.dat");

	Matr<double> matrix({ 2, 2, 3, 5, 6, 5, 7, 8, 9});


	const std::vector<double> approx = {1 ,0 ,0};
	auto eigenValues = Eigen::solve(matrix, approx, false);
	std::cout << eigenValues << "\n";
    eigenValues = Eigen::solve(matrix.toHessenberg(), approx, false);
	std::cout << eigenValues << "\n";

	// const std::vector<double> approx = {1 ,0 ,0};
	// auto eigenValues = Eigen::solve(matrix, approx, false);
	// std::cout << eigenValues << "\n";
 //    eigenValues = Eigen::solve(matrix.transposed(), approx, false);
	// std::cout << eigenValues << "\n";

	// const std::string var = "20";
	// save(elem , "Lab3/output" , "vecx" + var, "vecy" + var, "vecintery" + var);

}