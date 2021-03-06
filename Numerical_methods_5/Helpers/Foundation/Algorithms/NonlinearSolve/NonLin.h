#ifndef NONLIN_HPP
#define NONLIN_HPP

#include <array>
#include "../Algorithms.cpp"
#include <string>
#include <functional>

//MARK: - 1D
typedef double(*fun)(double);
typedef double(*dfun)(fun, double, double);
typedef std::array<double , 2> segment;

//MARK: - N-D
typedef std::vector<double> Point;
typedef std::vector<bool> Partial;
typedef std::function<double(const Point&)> vFunc;
typedef double(*d_vFunc)(fun, const Point&, const Partial&);
typedef std::array<double, 2> vector2D;

enum method{
	newtonmethod,
	bisectionmethod,
};

class NonLinearSolve {	
public:
	static double df (fun f, double point, double epsilon = 1e-5) {return( (f(point+epsilon)-f(point))/epsilon);};

	static double d_vFunc(vFunc f, const Point& point, const Partial& partial, double epsilon = 2e-8);

	static Matr<double> jacobi(const std::vector<vFunc>& F, const Point& point);

	static Point system_newton(const std::vector<vFunc>& F, const std::vector<vFunc>& dF, const size_t max_iterations, const Point x_0, double epsilon = 1e-5);

	static void convergeArea(const std::vector<vFunc>& F, const std::vector<vFunc>& dF, const size_t max_iterations, const std::string& path, const bool print = false);

	static double bisection(double a, double b, fun f, double epsilon = 1e-5, bool count = false);

	static double newton(double a, double b, fun f, dfun dF = df, double epsilon = 1e-5, bool count = false);

	static double chord(double a, double b, fun f, double epsilon = 1e-5, bool count = false);

	static std::vector<segment> localization(double a, double b, fun f, size_t numberofpoints = 10);

	static std::vector<double> solve(double a, double b, fun f, method name, size_t numberofpoints = 10, double epsilon = 1e-5);
};

#endif