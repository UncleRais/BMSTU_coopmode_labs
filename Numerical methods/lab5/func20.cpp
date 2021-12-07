#ifndef FUNC20
#define FUNC20
#include <cmath>

double func(double x)
{
	double R1 = sin((sqrt(13) * pow(x , 3) - 9 * x - 5 - sqrt(17)) / 10);
	double R2 = tan((pow(x , 2) + x + pow(2 , 0.33333)) / (3 * x - 5));
	return R1 + R2 + 0.6;
}

#endif