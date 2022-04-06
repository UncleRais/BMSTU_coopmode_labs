#ifndef var20_cpp
#define var20_cpp

#include <cmath>

double f(double x)
{
return( 0.5*pow(x + 1, 2) );
}

double fxx(double x)
{
return( 1 );
}

double g(double x)
{
return((x + 0.5)*cos(pi * x));
}

double phi(double t)
{
return(0.5);
}

double xi(double t)
{
return(2 - 3*t);
}

#endif