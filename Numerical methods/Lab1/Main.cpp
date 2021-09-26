#include "../Helpers/Foundation/Foundation.cpp"

int main(int argc, char** argv) 
{
	typedef double T;
	Matr<T> matrix;
	std::vector<T> vec;
	init(matrix, vec, "settings.dat");

	AlgPrint::printsystem(matrix, vec, 15);

	//AlgPrint::container(matrix * matrix.inversed() , AlgPrint::matr);

	AlgPrint::value("condA(inf)= ");
	AlgPrint::value(matrix.norminf()*(matrix.inversed()).norminf());
	AlgPrint::value("condA(1)= ");
	AlgPrint::value(matrix.normfirst()*(matrix.inversed()).normfirst());
	AlgPrint::value("condA(max)= ");
	AlgPrint::value(matrix.normmax()*(matrix.inversed()).normmax());
	AlgPrint::value("condA(estimate)= ");
	AlgPrint::value(matrix.normestimate(vec));
	AlgPrint::value("\n");

	auto qr = QR::solve(matrix, vec);
	AlgPrint::value("Solution (QR Decomposition):");
	AlgPrint::container(qr, AlgPrint::vect);
	AlgPrint::value("||Ax - b||:");
	AlgPrint::value(MatrixAlgorithm::misclosure(matrix,vec ,qr));
	AlgPrint::value("\n");

	makeoutrage(vec , -1.0);

	save(qr, "Lab1/output", "qrSolution");
	qr = QR::solve(matrix ,vec);
	AlgPrint::value("Solution (QR Decomposition) with outrage:");
	AlgPrint::container(qr, AlgPrint::vect);
	AlgPrint::value("||Ax - b||:");
	AlgPrint::value(MatrixAlgorithm::misclosure(matrix, vec, qr));
	AlgPrint::value("\n");

	makeoutrage(vec , 1.0);

	AlgPrint::value("\n");
	save(qr, "Lab1/output", "qrSolutionOutrage");

	auto gauss = Gauss::solve(matrix, vec);
	AlgPrint::value("Solution (Gauss):");
	AlgPrint::container(gauss, AlgPrint::vect);
	AlgPrint::value("||Ax - b||:");
	AlgPrint::value(MatrixAlgorithm::misclosure(matrix, vec, gauss));
	AlgPrint::value("\n");

	makeoutrage(vec , -1.0);

	save(gauss, "Lab1/output", "gaussSolution");
	gauss = Gauss::solve(matrix , vec);
	AlgPrint::value("Solution (Gauss) with outrage:");
	AlgPrint::container(gauss, AlgPrint::vect);
	AlgPrint::value("||Ax - b||:");
	AlgPrint::value(MatrixAlgorithm::misclosure(matrix, vec, gauss));
	AlgPrint::value("\n");

	makeoutrage(vec , 1.0);

	save(gauss, "Lab1/output", "gaussSolutionOutrage");
	return 0;
}