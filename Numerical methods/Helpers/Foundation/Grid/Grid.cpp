#ifndef GRID_CPP
#define GRID_CPP
#include "./Grid.h"
#include "../Foundation.cpp"

double Grid::unifgrid(size_t i, double leftval, double rightval, double numberofpoints) const
{
	return (leftval + i * (rightval - leftval) / numberofpoints); 
};

double Grid::chebishevgrid(size_t i, double leftval, double rightval, double numberofpoints) const
{
return ((leftval + rightval)/2 + (rightval - leftval)/2 * cos(pi * (2 * i + 1)/(2 * (numberofpoints + 2)))) ; 
}

void Grid::printGrid(int width, int prec) const
{
	size_t numberofpoints = size();
	std::cout << "Table:\n";
	AlgPrint::drawline(5 + numberofpoints * (width + 1));
	std::cout << "i    |";
	for(size_t i = 0; i < numberofpoints; ++i)
	{
		std::cout << std::setprecision(prec) << std::setw(width) << i + 1 << "|";
	}
	std::cout<<"\n";
	AlgPrint::drawline(5 + numberofpoints * (width + 1));
	std::cout << "x    |";
	for(size_t i = 0; i < numberofpoints; ++i)
	{
		std::cout << std::setprecision(prec) << std::setw(width) << points_x[i] << "|";
	}
	std::cout<<"\n";
	AlgPrint::drawline(5 + numberofpoints * (width + 1));
	std::cout << "f(x) |";
	for(size_t i = 0; i < numberofpoints; ++i)
	{
		std::cout << std::setprecision(prec) << std::setw(width) << points_y[i] << "|";
	}
	std::cout<<"\n";
	AlgPrint::drawline(5 + numberofpoints * (width + 1));
};

void Grid::setunifgrid(fun f)
{
	double y , x;
	for(size_t i = 0; i <= numberofpoints_ + 1; ++i)
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
	for(size_t i = 0; i <= numberofpoints_ + 1; ++i)
	{
		x = chebishevgrid(i, leftval_ , rightval_, numberofpoints_);
		y = f(x);
		points_x.push_back(x);
		points_y.push_back(y);
	}
};

Grid::Grid() {};

Grid::Grid(double leftval, double rightval, double numberofpoints)
{
	numberofpoints_ = numberofpoints;
	leftval_ = leftval;
	rightval_ = rightval;
	points_x.reserve(numberofpoints_);
	points_y.reserve(numberofpoints_);
};



#endif