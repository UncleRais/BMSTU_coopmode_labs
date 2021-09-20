#include "../Helpers/Foundation/Foundation.cpp"

int main(int argc, char** argv) 
{
	Matrix<double> matrix({1 ,2 ,3} , {2 , 2});
	//Matrix<double> matrix("settings.dat");
	matrix.printsystem(7 , 4);
	//matrix.inverse();
	// const auto result = Gauss::solve(matrix);
	// matrix.printsystem();
	// print(result, vect);
	// save(result, "Lab1/output", "solution
	return 0;
}