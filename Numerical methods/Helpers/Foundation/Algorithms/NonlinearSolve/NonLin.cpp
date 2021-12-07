#ifndef NONLIN_CPP
#define NONLIN_CPP

#include "./NonLin.h"
#include <cmath>
#include "../../Foundation.cpp"
#include "../../Math.cpp"
#include "../../Print/Print.cpp"

double NonLinearSolve::bisection(double a, double b, fun f, double epsilon)
{
	if(fabs(f(a)) < epsilon) return a;
	if(fabs(f(b)) < epsilon) return b;
	if (f(a) * f(b) > 0) 
	{
		std::cout << "Couldn't find a point. The necessary condition is not satisfied." << "\n";
		return 0;
	}
	{
		double eps = 2 * epsilon, delta = b - a;
		double left = a, right = b , x = (b + a) / 2;
		size_t k = 1;
		while( delta/(pow(2, k)) > eps )
		{
			if(fabs(f(x)) < epsilon) return x;
			if(f(x) * f(left) < 0)
			{
			right = x;
			} else
			{
			left = x;
			}
			x = (right + left) / 2;
			k++;
		}
		return x;
	}

}


double NonLinearSolve::newton(double a, double b, fun f, dfun dF, double epsilon)
{
double prevx = 0, x = (f(a) * b - f(b) * a) / (f(a) - f(b));
while(fabs(x - prevx) > epsilon)
{
	prevx = x;
	x = prevx - f(prevx) / dF(f , prevx, epsilon);
}
return x;
}

#endif