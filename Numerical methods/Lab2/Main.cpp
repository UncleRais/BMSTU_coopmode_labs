#include "../Helpers/Foundation/Foundation.cpp"

int main(int argc, char** argv) 
{
	typedef double T;
	Matr<T> matrix;
	std::vector<T> vec;
	init(matrix, vec, "settings.dat");
	AlgPrint::printsystem(matrix , vec);

	std::vector<T> res = Gauss::solve(matrix , vec);
	std::cout << "Gauss method:\n" <<  res << "\n";
	std::cout << "Misclosure: " << MatrixAlgorithm::misclosure(matrix, vec, res) << "\n\n";

	//for var 20 tau = 0.0081;    for var 23 tau = 0.0089
	AlgPrint::drawline(50);
	T epsilon = 1e-7;
	std::cout << "Precision: " << epsilon << "\n";
	AlgPrint::drawline(50);

	std::cout << "Simple iteration method:\n";
	res = Simple::solve(matrix , vec, 0.0089, epsilon);
	std::cout << res << "\n";
	std::cout << "Misclosure: " << MatrixAlgorithm::misclosure(matrix, vec, res) << "\n\n";

	AlgPrint::drawline(50);

	std::cout << "Jacobi method:\n";
	res = Jacobi::solve(matrix , vec, epsilon);
	std::cout << res << "\n";
	std::cout << "Misclosure: " << MatrixAlgorithm::misclosure(matrix, vec, res) << "\n\n";

	AlgPrint::drawline(50);
	return 0;
}