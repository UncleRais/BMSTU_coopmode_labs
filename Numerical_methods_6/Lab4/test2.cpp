#ifndef test2_cpp
#define test2_cpp

#include <cmath>

double f(double x1, double x2)
{
return( 0. );
}

double G1(double x1)
{
return( -1. );
}


double G2(double x1)
{
return( 1. );
}


double G3(double x2)
{
return(1. + x2);
}


double G4(double x2)
{
return(1. + x2);
}

std::vector<std::function <double (double)>> G = {G1,G2,G3,G4};
double M[2] = {1., 1.};

#endif