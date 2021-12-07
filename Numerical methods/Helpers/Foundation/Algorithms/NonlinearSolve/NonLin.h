#ifndef NONLIN_HPP
#define NONLIN_HPP

typedef double(*fun)(double);
typedef double(*dfun)(fun, double, double);

class NonLinearSolve
{	
public:

static double df (fun f, double point, double epsilon = 1e-5) {return( (f(point + epsilon) - f(point))/epsilon);};

static double bisection(double a, double b, fun f, double epsilon = 1e-5);

static double newton(double a, double b, fun f, dfun dF = df, double epsilon = 1e-5);
};

#endif