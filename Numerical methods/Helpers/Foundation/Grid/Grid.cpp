#ifndef GRID_CPP
#define GRID_CPP
#include "./Grid.h"
#include "../Foundation.cpp"
#include <functional>

double Grid::unifgrid(size_t i, double leftval, double rightval, size_t numberofpoints) const
{
	return (leftval + i * (rightval - leftval) / (numberofpoints - 1)); 
};

double Grid::chebishevgrid(size_t i, double leftval, double rightval, size_t numberofpoints) const
{
return ( (leftval + rightval)/2 - (rightval - leftval)/2 * cos(pi * (2 * i + 1)/(2 * numberofpoints)) ) ; 
}

void Grid::printGrid(int width, int prec) const
{
	std::cout << "Table:\n";
	AlgPrint::drawline(5 + numberofpoints_ * (width + 1));
	std::cout << "i    |";
	for(size_t i = 0; i < numberofpoints_; ++i)
	{
		std::cout << std::setprecision(prec) << std::setw(width) << i + 1 << "|";
	}
	std::cout<<"\n";
	AlgPrint::drawline(5 + numberofpoints_ * (width + 1));
	std::cout << "x    |";
	for(size_t i = 0; i < numberofpoints_; ++i)
	{
		std::cout << std::setprecision(prec) << std::setw(width) << points_x[i] << "|";
	}
	std::cout<<"\n";
	AlgPrint::drawline(5 + numberofpoints_ * (width + 1));
	std::cout << "f(x) |";
	for(size_t i = 0; i < numberofpoints_; ++i)
	{
		std::cout << std::setprecision(prec) << std::setw(width) << points_y[i] << "|";
	}
	std::cout<<"\n";
	AlgPrint::drawline(5 + numberofpoints_ * (width + 1));
	std::cout << "L(x) |";
	for(size_t i = 0; i < numberofpoints_; ++i)
	{
		std::cout << std::setprecision(prec) << std::setw(width) << interpolationLagrange(points_x[i]) << "|";
	}
	std::cout<<"\n";
	AlgPrint::drawline(5 + numberofpoints_ * (width + 1));
	std::cout << "y*(x)|";
	for(size_t i = 0; i < numberofpoints_; ++i)
	{
		std::cout << std::setprecision(prec) << std::setw(width) << points_inter_y[i] << "|";
	}
	std::cout<<"\n";
	AlgPrint::drawline(5 + numberofpoints_ * (width + 1));
};

void Grid::setunifgrid(fun f)
{
	double y , x;
	for(size_t i = 0; i < numberofpoints_ ; ++i)
	{
		x = unifgrid(i, leftval_ , rightval_, numberofpoints_);
		y = f(x);
		points_x.push_back(x);
		points_y.push_back(y);
	}
};

void Grid::setchebishevgrid(fun f)
{
	double y , x;
	for(size_t i = 0; i < numberofpoints_; ++i)
	{
		x = chebishevgrid(i, leftval_ , rightval_, numberofpoints_);
		y = f(x);
		points_x.push_back(x);
		points_y.push_back(y);
	}
};

double Grid::coefLagrange(size_t numcoef, double point) const
{
	double coef = 1;
	double value = points_x[numcoef];
	for(size_t i = 0; i < numberofpoints_; ++i)
		if(i != numcoef)
		{
			coef *= (point - points_x[i])/(value - points_x[i]);
		}

	return coef;
}

double Grid::interpolationLagrange(double point) const
{
	double res = 0;
	for(size_t i = 0; i < numberofpoints_; ++i)
	{
		res += points_y[i] * coefLagrange(i, point);
	}

	return res;
}

void Grid::calculateLagrange(double leftval, double rightval, size_t numberofpoints)
{
	double intery , x;
	points_inter_y.reserve(numberofpoints);
	for(size_t i = 0; i < numberofpoints ; ++i)
	{
		x = unifgrid(i, leftval_ , rightval_, numberofpoints);
		intery = interpolationLagrange(x);
		points_inter_y.push_back(intery);
	}
}

double Grid::funcnorm(fun f)
{
	double maxval = 0;
	double value, left = points_x[0], right = points_x[size() - 1];
	size_t numberofpoints = intersize();
	for(size_t i = 0; i < numberofpoints; ++i)
	{
		value = f(unifgrid(i , left, right, numberofpoints - 1));
		if(fabs(value - points_inter_y[i]) > maxval) maxval = fabs(value - points_inter_y[i]);
	}
	return maxval;
}

size_t Grid::findIndex(double point) const
{
	for (size_t i = 1; i < numberofpoints_; ++i)
		if(point < points_x[i])
			return i;
	return 0;
}

double Grid::interpolationSpline(double point, const std::vector<double>& a, 
	const std::vector<double>& b, const std::vector<double>& c, const std::vector<double>& d) const
{
	size_t i = findIndex(point);
	double value = point - points_x[i];
	return a[i] + b[i] * value + c[i] * pow(value , 2) / 2 + d[i] * pow(value , 3) / 6 ;
}


void Grid::calculateSpline(double leftval, double rightval, size_t numberofpoints) {
	typedef std::function<double(size_t)> func;
	func h = [this](size_t index) 
	{  
		if (index < 1) 
		{
			return 0.;
		}
		return double(this->points_x[index] - this->points_x[index - 1]);
	};

	//MARK: - Samarsky (page 143 –> formula for c_i coefficients). These are just for convenience!
	func coeffC_i_Minus_1 = h;

	func coeffC_i = [h](size_t index) 
	{ 
		return (-2) * (h(index) + h(index + 1));
	};

	func coeffC_i_Plus_1 = [h](size_t index) { 
		return h(index + 1);
	};

	func coeffF_i = [this, h](size_t index) { 
		return (-6.) * double( (this->points_y[index + 1] - this->points_y[index]) / h(index + 1) -  (this->points_y[index] - this->points_y[index - 1]) / h(index) );
	};

	// //MARK: - Forward move
	const size_t N = numberofpoints_ - 1;
	const size_t n = N - 1;
	std::vector<double> alpha(n + 2, 0);
	std::vector<double> beta(n + 2, 0);

	/// i = 1
	alpha[2] = coeffC_i_Plus_1(1) / coeffC_i(1); // alpha_2
	beta[2]  = coeffF_i(1) / coeffC_i(1); // beta_2

	/// i = 2...n-1 and i == n
	double value;
	for (size_t i = 2; i <= n; ++i) 
	{ 
		value = coeffC_i(i) - coeffC_i_Minus_1(i) * alpha[i];
		alpha[i + 1] = coeffC_i_Plus_1(i) / value;
		beta[i + 1]  = (coeffF_i(i) + coeffC_i_Minus_1(i) * beta[i]) / value;
	}

	
	//MARK: - Backward move
	std::vector<double> c(N + 1, 0);
	c[n] = (coeffF_i(n+1) + coeffC_i_Minus_1(n+1) * beta[n+1]) / coeffC_i(n+1) - coeffC_i_Minus_1(n+1) * alpha[n+1];
	for (int i = n - 1; i >= 0; --i) 
	{
		c[i] = alpha[i + 1] * c[i + 1] + beta[i + 1];
	}

	std::cout << c;
	//---------------------------
	// std::vector<double> A(n, 0);
	// std::vector<double> B(n + 1 , 0);
	// std::vector<double> C(n , 0);
	// std::vector<double> D(n + 1 , 0);

	// for(size_t i = 0; i < n ; ++i)
	// {
	// 	A[i] = coeffC_i_Minus_1(i + 1);
	// 	B[i] = -coeffC_i(i + 1);
	// 	C[i] = coeffC_i_Plus_1(i + 1);
	// 	D[i] = -coeffF_i(i + 1);
	// }
	// B[n] = coeffC_i(n);
	// D[n] = coeffF_i(n);

	// std::vector<double> c = Banish::solve(A , B , C , D);

	//---------------------------

	//Remaining coefficients
	std::vector<double> a(N, 0);
	std::vector<double> b(N, 0);
	std::vector<double> d(N, 0);

	a[0] = points_y[0];
	for (size_t i = 1; i <= N; ++i) 
	{
		const auto step = h(i);
		a[i] = points_y[i];
		d[i] = (c[i] - c[i - 1]) / step;
		b[i] = c[i] * step / 2 - d[i] * pow(step, 2) / 6 + (a[i] - a[i - 1]) / step;
	}

	double intery , x;
	points_inter_y.reserve(numberofpoints);
	for(size_t i = 0; i < numberofpoints ; ++i)
	{
		x = unifgrid(i, leftval_ , rightval_, numberofpoints);
		intery = interpolationSpline(x, a, b, c, d);
		points_inter_y.push_back(intery);
	}

}

Grid::Grid() {};

Grid::Grid(double leftval, double rightval, size_t numberofpoints)
{
	numberofpoints_ = numberofpoints;
	leftval_ = leftval;
	rightval_ = rightval;
	points_x.reserve(numberofpoints_);
	points_y.reserve(numberofpoints_);
};



#endif