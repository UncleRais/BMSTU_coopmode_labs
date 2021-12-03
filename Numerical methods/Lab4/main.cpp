#include "../Helpers/Foundation/Foundation.cpp"
#include "../Helpers/Foundation/Math.cpp"

int main(int argc, char** argv) 
{
	Matr<double> matrix;

	init(matrix, "./data/EIGEN20.dat");

	 //Matr<double> matrix({1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1});


	const std::vector<double> approx = {0.01196 ,-0.04856 , -0.1471, 0.9879};

	// auto eigenValues = Eigen::solve(matrix, approx, false, false);
	// std::cout << eigenValues << "\n";
	// eigenValues = Eigen::solve(matrix.transposed(), approx, false, false);
	// std::cout << eigenValues << "\n";
	// eigenValues = Eigen::solve(matrix, approx, true, false);
	// std::cout << eigenValues << "\n";
	 // auto eigenValues = Eigen::solve(matrix.toHessenberg(), approx, false, true);
	 // std::cout << eigenValues << "\n";
 //    eigenValues = Eigen::solve(matrix.toHessenberg(), approx, true, true);
	// std::cout << eigenValues << "\n";

	//std::cout << Eigen::raleigh(matrix, approx);

	// const std::vector<double> approx = {1 ,0 ,0};
	// auto eigenValues = Eigen::solve(matrix, approx, false);
	// std::cout << eigenValues << "\n";
 //    eigenValues = Eigen::solve(matrix.transposed(), approx, false);
	// std::cout << eigenValues << "\n";

	// const std::string var = "20";
	// save(elem , "Lab3/output" , "vecx" + var, "vecy" + var, "vecintery" + var);

}