#ifndef FUNC2
#define FUNC2
#include <cmath>
#include "../Helpers/Foundation/Algorithms/Algorithms.cpp"

double _func1(const Point& x) 
{
	return exp(x[0])-x[1]+4;
}


double _func2(const Point& x)
{
	return pow(x[0],2)-2*x[1]-3;
}

#endif