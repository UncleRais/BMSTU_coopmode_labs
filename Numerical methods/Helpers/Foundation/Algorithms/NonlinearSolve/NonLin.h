#ifndef NONLIN_HPP
#define NONLIN_HPP

typedef double(*fun)(double);
typedef double(*dfun)(fun, double, double);
typedef std::array<double , 2> segment;

enum method{
	newtonmethod,
	bisectionmethod,
};

class NonLinearSolve
{	
public:
enum method
{
	newtonmethod,
	bisectionmethod,
};

static double df (fun f, double point, double epsilon = 1e-5) {return( (f(point + epsilon) - f(point))/epsilon);};

static double bisection(double a, double b, fun f, double epsilon = 1e-5);

static double newton(double a, double b, fun f, dfun dF = df, double epsilon = 1e-5);

static std::vector<segment> localization(double a, double b, fun f, size_t numberofpoints = 10);

static std::vector<double> solve(double a, double b, fun f, method name, size_t numberofpoints = 10, double epsilon = 1e-5);
};

#endif