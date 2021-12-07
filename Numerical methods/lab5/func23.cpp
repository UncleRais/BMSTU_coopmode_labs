#ifndef FUNC23
#define FUNC23
#include <cmath>

double func(double x)
{
	double R1 = sin((-2 * pow(x , 2) - sqrt(10) * x + 1) / 4);
	double R2 = pow((pow(x , 2) + (sqrt(2) + R1) * x - 3)/(R1 * x - 3) , log(2));
	return R1 + R2 - 0.1;
}

#endif