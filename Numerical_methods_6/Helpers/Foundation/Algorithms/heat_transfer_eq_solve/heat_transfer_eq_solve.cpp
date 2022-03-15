#ifndef HEAT_TRANSFER_EQ_SOLVE_CPP
#define HEAT_TRANSFER_EQ_SOLVE_CPP
#include "./heat_transfer_eq_solve.h"

template < typename T >
Portrait heat_transfer_eq_solve<T>::NDsolve(T epsilon)
{
	Portrait result;
	return(result);
}

template < typename T >
void heat_transfer_eq_solve<T>::parameters_info()
{
	std::cout << "Beam characteristics:\n";
	std::cout << "c = " << c << ", rho = " << rho << ", L = " << L <<";\n"; 
	std::cout << "Boundary conditions:\n";
	std::cout << "alpha = " << alpha << ", beta = " << beta << ", gamma = " << gamma << ",\n";
	std::cout << "x1 = " << x1 << ", x2 = " << x2 << ", k1 = " << k1 << ", k2 = " << k2 << ",\n";
	std::cout << "Q = " << Q << ", t0 = " << t0 << ", T0 = " << T0 << ";\n";
}

template < typename T >
void heat_transfer_eq_solve<T>::save(std::vector<std::vector<T>>& portrait, std::string path) {
	std::ofstream file;
	file.open(path);
	for(const auto &point: portrait)
	{
		for(const auto &coordinate: point)
		{
			file << coordinate << ' ';
		}
		file << std::endl;
	}
	file.close();
}

template < typename T >
void heat_transfer_eq_solve<T>::save(std::vector<T>& portrait, std::string path) {
	std::ofstream file;
	file.open(path);
	int counter = 0;
	for(const auto &value: portrait) { file << ++counter << ' ' << value << std::endl;  }
	file.close();
}

#endif