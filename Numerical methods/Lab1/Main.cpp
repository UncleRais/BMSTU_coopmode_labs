#include "../Helpers/Matrix.hpp"

int main(int argc, char** argv) {
	Matrix<double> a("settings.dat");
	a.print(10,4);
	a.GaussMethod();
	a.print(10,4);
	return 0;
}