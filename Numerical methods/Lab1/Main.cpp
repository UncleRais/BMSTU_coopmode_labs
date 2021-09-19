#include "../Helpers/Foundation/Foundation.cpp"


int main(int argc, char** argv) 
{
	Matrix<double> matrix("settings.dat");
	const auto result = Gauss().solve(matrix);
	matrix.printsystem();
	print(result, vect);
	save(result, "Lab1/data", "solution");
	return 0;
}