#include "../Helpers/Matrix.hpp"

int main(int argc, char** argv) {
	Matrix<double> a("settings.dat");
	a.print(10,4);
	const auto result = a.linearSolveGauss(gauss);
	for (const auto& x: result) {
		std::cout << x << ";  ";
	}
	std::cout << std::endl;

	return 0;
}