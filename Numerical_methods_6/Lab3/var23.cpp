#ifndef var23_cpp
#define var23_cpp

#include <cmath>

double f(double x)
{
return( x * cos(pi * x / 2));
}

double fxx(double x)
{
return( -pi * sin(pi * x / 2) - pi / 2 * pi / 2 * x * cos(pi / 2 * x));
}

double g(double x)
{
return(2 * x * x);
}

double phi(double t)
{
return(0);
}

double xi(double t)
{
return(t * t);
}

#endif