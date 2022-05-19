#ifndef test2_cpp
#define test2_cpp

#include <cmath>

double f(double x)
{
return(sqrt(x) + pow(x,2));
}

double K(double x, double s)
{
return(0.5 * (1 - x*cos(x*s)));
}

std::array<double, 2> M = {0.1, 1.};

double lambda = 1.;

#endif