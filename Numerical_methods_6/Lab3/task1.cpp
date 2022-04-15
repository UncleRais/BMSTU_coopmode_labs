#ifndef task1_cpp
#define task1_cpp

#include <cmath>

double f(double x)
{
	if( -1/3. <= x && x <= 1/3.)
	{
		return(1);
	}
	else
	{
		return(0);
	};
}

// double fxx(double x, double h)
// {
// return(0);
// }

double fxx(double x, double h)
{
return((f(x + h) - 2 * f(x) + f(x - h)) / (h * h));
}

double g(double x)
{
return(0);
}

double phi(double t)
{
return(0);
}

double xi(double t)
{
return(0);
}

#endif