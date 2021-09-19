#include "../Helpers/Foundation/Foundation.cpp"

int main(int argc, char** argv) 
{
	Matrix<double> matrix("settings.dat");
	const auto result = MatrixAlgorithms<double>::linearSolve(matrix);
	matrix.printsystem();
	print(result, vect);
	save<double>(result, "Lab1/data", "solution");
	return 0;
}