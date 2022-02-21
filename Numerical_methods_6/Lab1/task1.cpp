#ifndef TASK1
#define TASK1
#include <cmath>

std::vector<double> cond = {0.0, 0.2, 2, 2}; /*{t0 , tn, x1(t0), x2(t0)}*/

double f1 (std::vector<double>& x)
{
	return( 2*x[0] + pow(x[1],2) - 1 );
}

double f2 (std::vector<double>& x)
{
	return(6*x[0] - pow(x[1],2) + 1);
}

#endif