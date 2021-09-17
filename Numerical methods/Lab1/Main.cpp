#include "../Helpers/Foundation/Foundation.cpp"

int main(int argc, char** argv) 
{
	Matrix<double> a("settings.dat");
	a.printsystem(10,4);
	const auto result =  MatrixAlgorithms<double>::linearSolve(a);
	for (const auto& x: result) {
		std::cout << x << ";  ";
	}
	std::cout << std::endl;
	return 0;
}

// ---------------------------------------------
// |      28.86     -0.008      2.406      19.24 | 30.46
// |      14.44     -0.001      1.203      9.624 | 18.25
// |      120.2     -0.032      10.02      80.14 | 128.2
// |     -57.71      0.016     -4.812     -38.48 | -60.91
// ---------------------------------------------
// 1.487;  1000;  -18.08;  2.03;  