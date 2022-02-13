#ifndef ODE_CPP
#define ODE_CPP
#include "./ODE.h"

template < typename T >
void ODE::NDsolve(std::vector<funtwo> rightpart, T (&cond)[2][2], T epsilon)
{
	std::ofstream file;
	file.open("./output/euler.dat");
	int numberofpoints = 1000; 
	T h = (160.0 - cond[0][0])/(numberofpoints - 1);
	std::vector<T> x1 = {cond[0][1]};
	std::vector<T> x2 = {cond[1][1]};
	x1.reserve(numberofpoints);
	x2.reserve(numberofpoints);
	for(int i = 0; i < numberofpoints - 2; ++i)
	{
		x1.push_back(x1[i] + h * rightpart[0](x1[i], x2[i]) );
		x2.push_back(x2[i] + h * rightpart[1](x1[i], x2[i]) );
		file << x1[i] << ' ' << x2[i] << std::endl;
	}
	file << x1[numberofpoints - 3] << ' ' << x2[numberofpoints - 3] << std::endl;
	file.close();
}

#endif