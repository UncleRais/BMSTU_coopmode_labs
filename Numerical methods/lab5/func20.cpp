#ifndef FUNC20
#define FUNC20
#include <cmath>
#include "../Helpers/Foundation/Algorithms/Algorithms.cpp"

double func(double x)
{
	double R1 = sin((sqrt(13) * pow(x , 3) - 9 * x - 5 - sqrt(17)) / 10);
	double R2 = tan((pow(x , 2) + x + pow(2 , 0.33333)) / (3 * x - 5));
	return R1 + R2 + 0.6;
}

double _func1(const Point& x)
{
	return 6 * pow(x[0],2) - 7 * pow(x[1],2) - 65;

}
double d_func1_dx(const Point& x)
{
	return 12*x[0];
}
double d_func1_dy(const Point& x)
{
	return -14*x[1];
}


double _func2(const Point& x)
{
	return (13 * x[0] * x[1]) + 41;
}
double d_func2_dx(const Point& x)
{
	return 13 * x[1];
}
double d_func2_dy(const Point& x)
{
	return 13 * x[0];
}


#endif