#ifndef test1_cpp
#define test1_cpp

#include <cmath>

double f(double x)
{
return(0.5 * (1. + sin(x)));
}

double K(double x, double s)
{
return(0.5 * (1. - x*cos(x*s)));
}

std::array<double, 2> M = {0., 1.};

double lambda = 1.;

#endif