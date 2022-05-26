#ifndef test2_1_cpp
#define test2_1_cpp

#include <cmath>

double f(double x)
{
return(exp(x));
}

double K(double x, double s)
{
return( exp(x-s) );
}

std::array<double, 2> M = {0., 1.};

double lambda = 0.5;

#endif