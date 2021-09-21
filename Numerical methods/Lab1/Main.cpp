#include "../Helpers/Foundation/Foundation.cpp"

int main(int argc, char** argv) 
{
	Matrix<double> matrix("settings.dat");
	const auto qr = QR::solve(matrix);
	AlgPrint::value("Solution (QR Decomposition):");
	AlgPrint::container(qr, AlgPrint::vect);
	AlgPrint::value("\n");
	save(qr, "Lab1/output", "qr solution");

	const auto gauss = Gauss::solve(matrix);
	AlgPrint::value("Solution (Gauss):");
	AlgPrint::container(gauss, AlgPrint::vect);
	save(gauss, "Lab1/output", "gauss solution");

	return 0;
}