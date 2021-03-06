#ifndef NONLIN_CPP
#define NONLIN_CPP

#include "./NonLin.h"
#include <cmath>
#include <fstream>
#include <iomanip>
#include "../../Foundation.cpp"
#include "../../Math.cpp"
#include "../../Print/Print.cpp"

void NonLinearSolve::convergeArea(const std::vector<vFunc>& F, const std::vector<vFunc>& dF, const size_t max_iterations, const std::string& path, const bool print) {
	std::ofstream file;
	file.open(path + "convergeArea.dat");
	for (double x = -100; x <= 100; ++x)
		for (double y = -100; y <= 100; ++y)
		{
			const auto result = NonLinearSolve::system_newton(F, dF, max_iterations, {x, y});
			if (print) { std::cout << std::setw(5)  << x << " " << " " << std::setw(5) << y << " " << "   " << result[2] << "\n"; }
			file << x << "   " << y << "   " << result[2] << std::endl;
		}
	file.close();
}

double NonLinearSolve::d_vFunc(vFunc f, const Point& point, const Partial& partial, double epsilon)
	{
		std::function<double(const Point&)>result = [f](const Point& _point){ return f(_point);};
		for (size_t i = 0; i < point.size(); ++i) 
		{
			if (!partial[i]) { continue; }
		 	result = [result, partial, epsilon](const Point& _point)
		 	{ 
		 		Point XPlusDelta(_point); 
		 		Point XMinusDelta(_point); 
		 		for (size_t i = 0; i < XPlusDelta.size(); ++i){ XPlusDelta[i] += partial[i] ? epsilon : 0;
		 		XMinusDelta[i] -= partial[i] ? epsilon : 0; };
		 		return (result(XPlusDelta) - result(XMinusDelta))/(2*epsilon);
		 	};
		 	result(point);
		}

		return result(point);
	}

Matr<double> NonLinearSolve::jacobi(const std::vector<vFunc>& F, const Point& point) {
	std::vector<double> values(F.size()*point.size(), 0);
	for (size_t i = 0; i < F.size(); ++i) 
		for (size_t j = 0; j < point.size(); ++j)
		{
			Partial partial(point.size(), false);
			partial[j] = true;
			values[i*point.size()+j] = NonLinearSolve::d_vFunc(F[i], point, partial);
		}
	
	return Matr<double>(values);	
}

Point NonLinearSolve::system_newton(const std::vector<vFunc>& F, const std::vector<vFunc>& dF, const size_t max_iterations, const Point x_0, const double epsilon) {
	Point x_k = x_0;
	Point x_k_next = x_0;
	size_t iterations = 0;
	while ((norm(x_k_next - x_k) > epsilon && iterations <= max_iterations) || iterations == 0) 
	{
		++iterations;
		x_k = x_k_next;
		try 
		{
			Matr<double> dF_k;
			if (dF.size() < 2*F.size()) 
			{
				dF_k = jacobi(F, x_k);

			} else 
			{
				std::vector<double> partials(dF.size(), 0);
				for (size_t i = 0; i < dF.size(); ++i) { partials[i] = dF[i](x_k); }
					dF_k = Matr<double>(partials);
			}
			std::vector<double> F_k;
			for (auto f: F) { F_k.push_back(f(x_k)); }
			for(size_t i = 0; i < 10; i++ ) 
			{
				for(size_t j = 0; j < 10; j++ )
				std::cout << dF_k.atvalue(i,j) << " ";
			std::cout << "\n";
			}

			x_k_next = x_k - dF_k.inversed()*F_k;
		} catch (...) 
		{
			//x_k.push_back(double(max_iterations + 1));
			return x_k;
		}
	}
	//x_k_next.push_back(double(iterations));
	return x_k_next;
}

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


double NonLinearSolve::bisection(double a, double b, fun f, double epsilon, bool count)
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
			if(fabs(f(x)) < epsilon) 
				{
					if(count) std::cout<< "Iterations: " << k - 1<< "\n";
					return x;
				}
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
		if(count) std::cout<< "Iterations: " << k - 1<< "\n";
		return x;
	}

}


double NonLinearSolve::newton(double a, double b, fun f, dfun dF, double epsilon, bool count)
{
double prevx = 0, x = (f(a) * b - f(b) * a) / (f(a) - f(b));
size_t counter = 0;
std::vector<double> appr = {x};
while(fabs(x - prevx) > epsilon)
{
	prevx = x;
	x = prevx - f(prevx) / dF(f , prevx, epsilon);
	appr.push_back(x);
	if(count) counter ++;
}
if(count) std::cout<< "Iterations: " << counter << "\n";
size_t N = appr.size(); 
if(N >= 4) 
	{
		std::cout <<std::setprecision(20)<< appr[N-4] << " " << appr[N-3] << " " << appr[N-2] << " " << appr[N-1] << "\n";
		std::cout << log(fabs(appr[N-2]-appr[N-1])/fabs(appr[N-3]-appr[N-1]))/log(fabs(appr[N-3]-appr[N-1])/fabs(appr[N-4]-appr[N-1])) << "\n";
	}
return x;
}

double NonLinearSolve::chord(double a, double b, fun f, double epsilon, bool count)
{
double left = a, right = b, x;
size_t counter = 0;
std::vector<double> appr = {};
while (fabs(right - left) > epsilon)
    {
    	if (fabs(f(right)) < epsilon) 
    	{
    		if(count) std::cout<< "Iterations: " << counter << "\n";
    		size_t N = appr.size(); 
			if(N >= 4) std::cout <<std::setprecision(20)<< appr[N-4] << " " << appr[N-3] << " " << appr[N-2] << " " << appr[N-1] << "\n";
			std::cout << log(fabs(appr[N-2]-appr[N-1])/fabs(appr[N-3]-appr[N-1]))/log(fabs(appr[N-3]-appr[N-1])/fabs(appr[N-4]-appr[N-1])) << "\n";
    		return right;
    	}
    	if (fabs(f(left)) < epsilon) 
    	{
    		if(count) std::cout<< "Iterations: " << counter << "\n";
    		size_t N = appr.size(); 
			if(N >= 4) std::cout <<std::setprecision(20)<< appr[N-4] << " " << appr[N-3] << " " << appr[N-2] << " " << appr[N-1] << "\n";
			std::cout << log(fabs(appr[N-2]-appr[N-1])/fabs(appr[N-3]-appr[N-1]))/log(fabs(appr[N-3]-appr[N-1])/fabs(appr[N-4]-appr[N-1])) << "\n";
    		return left;
    	}
    	x = right - (right - left) * f(right) / (f(right) - f(left));
    	appr.push_back(x);
    	if( f(x)*f(left) < 0)
    	{
    		right = x; 
    	} else
    	{
    		left = x;
    	}
    	if(count) counter ++;
    }
    if(count) std::cout<< "Iterations: " << counter << "\n";
    size_t N = appr.size(); 
	if(N >= 4) std::cout <<std::setprecision(20)<< appr[N-4] << " " << appr[N-3] << " " << appr[N-2] << " " << appr[N-1] << "\n";
	std::cout << log(fabs(appr[N-2]-appr[N-1])/fabs(appr[N-3]-appr[N-1]))/log(fabs(appr[N-3]-appr[N-1])/fabs(appr[N-4]-appr[N-1])) << "\n";
    return (right - left)/2;
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