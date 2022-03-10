#ifndef OSC
#define OSC
#include <cmath>

std::vector<double> cond = {0.0, 1000.0, 1.0, 0.0}; /*{t0 , tn, x1(t0), x2(t0)}*/
double k = 10 , m = 0.7;


double f1 (std::vector<double>& x)
{
	return( x[1] );
}

double f2 (std::vector<double>& x)
{
	return(- k / m * x[0] );
}

#endif