#ifndef HEAT_TRANSFER_EQ_SOLVE_CPP
#define HEAT_TRANSFER_EQ_SOLVE_CPP
#include "./heat_transfer_eq_solve.h"

template < typename T >
Portrait ODE::NDsolve(const std::vector<funtwo>& rightpart, 
				  	  const std::vector<T>& cond, 
				  	  MethodType name, 
				  	  T h,
				 	  T epsilon)
{
	int systemsize = rightpart.size(); 
	int timestamps = (cond[1] - cond[0])/h + 1;
	std::vector<std::vector<T>> x;
	x.push_back({});
	for(int i = 0; i < systemsize; ++i)
	{
		x[0].push_back(cond[i + 2]);
	} 
	Portrait end;
	return(end);
}

template < typename T >
void ODE::save(std::vector<std::vector<T>>& portrait, std::string path) {
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
void ODE::save(std::vector<T>& portrait, std::string path) {
	std::ofstream file;
	file.open(path);
	int counter = 0;
	for(const auto &value: portrait) { file << ++counter << ' ' << value << std::endl;  }
	file.close();
}

#endif