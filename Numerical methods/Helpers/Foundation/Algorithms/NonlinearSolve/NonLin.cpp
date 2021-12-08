#ifndef NONLIN_CPP
#define NONLIN_CPP

#include "./NonLin.h"
#include <cmath>
#include "../../Foundation.cpp"
#include "../../Math.cpp"
#include "../../Print/Print.cpp"

std::vector<segment> NonLinearSolve::localization(double a, double b, fun f, size_t numberofpoints)
{
	std::vector<segment> res;

	double h = (b - a)/numberofpoints, left, right;

	segment points;

	for (size_t i = 0; i < numberofpoints; ++i)
	{
		left = a + i*h;
		right = a + (i + 1) * h; 
		if (f(left) * f(right) < 0 )
		{
			points[0] = left;
			points[1] = right;
			res.push_back(points);
		}
	}

	return res;

}


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

std::vector<double> NonLinearSolve::solve(double a, double b, fun f, method name, size_t numberofpoints, double epsilon)
{
	std::vector<segment> segments = NonLinearSolve::localization(a, b, f, numberofpoints);
	std::vector<double> solutions;
	double sol, left, right; 
	for(auto& seg: segments)
	{
		left = seg[0];
		right = seg[1];
		switch(name) 
		{
		case newtonmethod: 
			sol = NonLinearSolve::newton(left, right, f, df, epsilon); 
			break;
		case bisectionmethod: 
			sol = NonLinearSolve::bisection(left, right, f, epsilon); 
			break;
		default:
			break;
		};
		solutions.push_back(sol);
	}
	return solutions;
}
#endif