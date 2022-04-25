#ifndef var3_cpp
#define var3_cpp
//3 = 20 - 17

#include <cmath>

double f(double x1, double x2)
{
return( 3. );
}

double G1(double x1)
{
return( 1.);
}


double G2(double x1)
{
return( 1. );
}


double G3(double x2)
{
return(1. + 0.5 * pow(x2 - 1,2));
}


double G4(double x2)
{
return(1. + 0.5 * pow(x2 - 1,2));
}

std::vector<std::function <double (double)>> G = {G1,G2,G3,G4};
double M[2] = {2., 2.};


#endif