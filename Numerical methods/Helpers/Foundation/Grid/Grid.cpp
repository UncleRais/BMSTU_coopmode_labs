#ifndef GRID_CPP
#define GRID_CPP
#include "./Grid.h"
#include "../Foundation.cpp"

void Grid::printGrid(int width, int prec) const
{
	size_t numberofpoints = size();
	std::cout << "Table:\n";
	AlgPrint::drawline(5 + numberofpoints * (width + 1));
	std::cout << "i    |";
	for(size_t i = 0; i < numberofpoints; ++i)
	{
		std::cout << std::setprecision(prec) << std::setw(width) << i << "|";
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

Grid::Grid() {};

Grid::Grid(fun f, double leftval, double rightval, double numberofpoints)
{
	double y , x = leftval;
	double step = (rightval - leftval) / numberofpoints;
	points_x.reserve(numberofpoints);
	points_y.reserve(numberofpoints);

	while (x <= rightval)
	{
		y = f(x);
		points_x.push_back(x);
		points_y.push_back(y);
		x += step;
	}
};



#endif