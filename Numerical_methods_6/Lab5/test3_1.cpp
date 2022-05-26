#ifndef test3_cpp
#define test3_cpp

#include <cmath>

double F(double phi)
{
return( sin(10 * phi) );
}

std::array<double, 2> Q(std::array<double, 2> r, std::array<double, 2> p)
{
	double div = 2 * pi * (pow(r[1] - p[1],2) + pow(r[0] - p[0],2));
return {-(r[1] - p[1])/div, (r[0] - p[0])/div};
}

#endif