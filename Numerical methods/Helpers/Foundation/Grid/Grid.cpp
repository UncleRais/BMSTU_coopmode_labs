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

void  Grid::whyAreYouRunning() {
	typedef std::function<double(size_t)> func;

	//x_i - x_{i - 1}
	func h = [this](size_t index) { 
		if (index >= 1 && index < numberofpoints_) {
			return this->points_x[index] - this->points_x[index - 1];
		}
		return 0.;
	};

	//MARK: - Samarsky (page 143 –> formula for c_i coefficients). These are just for convenience!
	func coeffC_i_Minus_1 = h;
	func coeffC_i = [h](size_t index) { 
		return (-1) * (h(index) + h(index + 1));
	};
	func coeffC_i_Plus_1 = [h](size_t index) { 
		return h(index + 1);
	};
	func coeffF_i = [this, h](size_t index) { 
		return 6. * double( (this->points_y[index + 1] - this->points_y[index]) / h(index + 1) -  (this->points_y[index] - this->points_y[index - 1]) / h(index) );
	};

	//MARK: - Galanin (page 56, WhyAreYouRunning algorithm adaptation for our problem)
	func alpha = [this, coeffC_i_Minus_1, coeffC_i, coeffC_i_Plus_1, &alpha](size_t index) { 
		if (index <= 1) {
			return coeffC_i_Plus_1(0) / coeffC_i(0);
		}
		if (index >= this->points_x.size()) {
			return 0.0;
		}
		return coeffC_i_Plus_1(index - 1) / (coeffC_i(index - 1) - coeffC_i_Minus_1(index - 1) * alpha(index - 1)); 
	};
	func beta = [coeffC_i_Minus_1, coeffC_i, coeffF_i, &beta, alpha](size_t index) { 
		if (index <= 1) {
			return coeffF_i(0) / coeffC_i(0);
		}
		return (coeffF_i(index - 1) + coeffC_i_Minus_1(index - 1) * beta(index - 1)) / (coeffC_i(index - 1) - coeffC_i_Minus_1(index - 1) * alpha(index - 1));
	};

	std::vector<double> alphas = {};
	std::vector<double> betas = {};

	for (int i = 1; i <= points_x.size(); ++i) {
		alphas.push_back(alpha(i + 1));
		betas.push_back(beta(i + 1 ));

		std::cout << "h_{" << i << "} == " << h(i) << "\n";
		std::cout << "alpha_{" << i + 1 << "} == " << alphas[i] << "\n";
		std::cout << "beta_{" << i + 1 << "} == " << betas[i] << "\n";
		std::cout << "\n\n";
	}

	// func beta  = [this](size_t index) {  };
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