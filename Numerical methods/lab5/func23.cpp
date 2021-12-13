#ifndef FUNC23
#define FUNC23
#include <cmath>
#include "../Helpers/Foundation/Algorithms/Algorithms.cpp"

double func(double x)
{
	double R1 = sin((-2 * pow(x , 2) - sqrt(10) * x + 1) / 4);
	double R2 = pow((pow(x , 2) + (sqrt(2) + R1) * x - 3)/(R1 * x - 3) , log(2));
	return R1 + R2 - 0.1;
}

double _func1(const Point& x) 
{
	return sqrt(x[0]) * ( sqrt(x[0]+11) + 2 * sqrt(x[1])) - 78 * sqrt(x[1]);
}
double d_func1_dx(const Point& x)
{
	return sqrt(x[0])/(2*sqrt(11 + x[0])) + (sqrt(11 + x[0]) + 2*sqrt(x[1]))/(2*sqrt(x[0]));
}
double d_func1_dy(const Point& x)
{
	return -39/sqrt(x[1]) + sqrt(x[0]/x[1]);
}


double _func2(const Point& x)
{
	return 2 * sqrt(x[0]) + 1.5 * sqrt(x[1]) - 14;
}
double d_func2_dx(const Point& x)
{
	return 1 / sqrt(x[0]);
}
double d_func2_dy(const Point& x)
{
	return 0.75/sqrt(x[1]);
}


#endif