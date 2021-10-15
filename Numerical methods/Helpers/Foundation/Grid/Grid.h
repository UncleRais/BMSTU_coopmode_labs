#ifndef GRID
#define GRID

#include <iostream>
#include <fstream>
#include <vector>
#include "../Print/Print.cpp"


typedef double(*fun)(double);

class Grid {

private:
	std::vector<double> points_x = {};
	std::vector<double> points_y = {};

public:

	double& atx(const size_t i) {return points_x[i];};

	double atvalx(const size_t i)  const {return points_x[i];};

	double& aty(const size_t i) {return points_y[i];};

	double atvaly(const size_t i)  const {return points_y[i];};

	void printGrid(int width = 10, int prec = 4) const;

	size_t size() const {
		return points_x.size();
	};
public:

	Grid();
	Grid(fun , double leftval, double rightval, double numberofpoints);
};
#endif