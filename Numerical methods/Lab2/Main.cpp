#include "../Helpers/Foundation/Foundation.cpp"

int main(int argc, char** argv) 
{
	typedef double T;
	Matr<T> matrix;
	std::vector<T> vec;
	init(matrix, vec, "settings.dat");
	AlgPrint::printsystem(matrix , vec);
	std::cout << "Gauss method:" <<  Gauss::solve(matrix , vec) << "\n";
	std::cout << "Simple iteration method:\n" << Simple::solve(matrix , vec, 0.0081, 1e-3) << "\n";
	return 0;
}