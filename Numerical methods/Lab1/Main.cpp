#include "../Helpers/Matrix.hpp"

int main(int argc, char** argv) {
	Matrix<double> a("settings.dat");
	a.print(20);
	return 0;
}