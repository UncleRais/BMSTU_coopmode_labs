#include "../Helpers/Foundation/Foundation.cpp"

int main(int argc, char** argv) 
{
	Matrix<double> matrix("settings.dat");
	const auto result = QR::solve(matrix);

	// matrix.printInverse(15 , 6);
	// Matrix<double> matrix({1 , 2 , 3 , 4} , {2 , 2});
	// matrix.changerightvalues({3 , 3});
	// const auto result = Gauss::solve(matrix);
	// matrix.printsystem();
	// print(result, vect);
	// save(result, "Lab1/output", "solution
	return 0;
}