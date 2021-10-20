#ifndef GRID_CPP
#define GRID_CPP
#include "./Grid.h"
#include "../Foundation.cpp"

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