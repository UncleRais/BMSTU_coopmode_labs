#ifndef TASK2
#define TASK2
#include <cmath>

std::vector<double> cond = {0.0, 0.1, 1, 1}; /*{t0 , tn, x1(t0), x2(t0)}*/

double f1 (std::vector<double>& x)
{
	return( 1 - pow(x[1],2) - pow(x[0],2) );
}

double f2 (std::vector<double>& x)
{
	return(2*x[0]);
}

#endif