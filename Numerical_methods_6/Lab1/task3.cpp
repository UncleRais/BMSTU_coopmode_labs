#ifndef TASK3
#define TASK3
#include <cmath>

std::vector<double> cond = {0.0, 0.1, 1, 1, 1}; /*{t0 , tn, x1(t0), x2(t0)}*/

double f1 (std::vector<double>& x)
{
	return( 10.0*(x[1] - x[0]) );
}

double f2 (std::vector<double>& x)
{
	return(x[0]*(28.0 - x[2]) - x[1]);
}

double f3 (std::vector<double>& x)
{
	return(x[0] * x[1] - 8.0/3.0 * x[2]);
}

#endif