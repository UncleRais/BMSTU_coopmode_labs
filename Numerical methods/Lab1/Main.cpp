#include "../Helpers/Matrix.hpp"

int main(int argc, char** argv) {
	Matrix<double> a("settings.dat");
	a.print(10);
	a.GaussMethod();
	return 0;
}