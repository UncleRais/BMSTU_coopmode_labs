#include "../Helpers/Foundation/Foundation.cpp"

int main(int argc, char** argv) 
{
	Matrix<double> matrix("settings.dat");
	matrix.printsystem(10);

	MatrixAlgorithm::dot(matrix, matrix.inversed()).printsystem(20);

	AlgPrint::value("condA(inf)= ");
	AlgPrint::value(matrix.norminf()*(matrix.inversed()).norminf());
	AlgPrint::value("condA(1)= ");
	AlgPrint::value(matrix.normfirst()*(matrix.inversed()).normfirst());
	AlgPrint::value("condA(max)= ");
	AlgPrint::value(matrix.normmax()*(matrix.inversed()).normmax());

	auto qr = QR::solve(matrix);
	AlgPrint::value("Solution (QR Decomposition):");
	AlgPrint::container(qr, AlgPrint::vect);
	AlgPrint::value("||Ax - b||:");
	AlgPrint::value(MatrixAlgorithm::misclosure(matrix,qr));
	matrix.makeoutrage(-1);
	save(qr, "Lab1/output", "qr solution");
	qr = QR::solve(matrix);
	AlgPrint::value("Solution (QR Decomposition):");
	AlgPrint::container(qr, AlgPrint::vect);
	AlgPrint::value("||Ax - b||:");
	AlgPrint::value(MatrixAlgorithm::misclosure(matrix,qr));
	matrix.makeoutrage(1);
	AlgPrint::value("\n");
	//save(qr, "Lab1/output", "qr solution");

	auto gauss = Gauss::solve(matrix);
	AlgPrint::value("Solution (Gauss):");
	AlgPrint::container(gauss, AlgPrint::vect);
	AlgPrint::value("||Ax - b||:");
	AlgPrint::value(MatrixAlgorithm::misclosure(matrix,gauss));
	matrix.makeoutrage(-1);
	save(qr, "Lab1/output", "qr solution");
	gauss = Gauss::solve(matrix);
	AlgPrint::value("Solution (Gauss):");
	AlgPrint::container(gauss, AlgPrint::vect);
	AlgPrint::value("||Ax - b||:");
	AlgPrint::value(MatrixAlgorithm::misclosure(matrix,gauss));
	matrix.makeoutrage(1);
	save(gauss, "Lab1/output", "gauss solution");
	return 0;
}