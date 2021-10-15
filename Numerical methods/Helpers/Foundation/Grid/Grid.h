#ifndef GRID
#define GRID

#include <iostream>
#include <fstream>
#include <vector>
#include "../Print/Print.cpp"


typedef double(*fun)(double);

class Grid {

private:
	double leftval_;
	double rightval_;
	size_t numberofpoints_;
	std::vector<double> points_x = {};
	std::vector<double> points_y = {};

public:

	double& atx(const size_t i) {return points_x[i];};

	double atvalx(const size_t i)  const {return points_x[i];};

	double& aty(const size_t i) {return points_y[i];};

	double atvaly(const size_t i)  const {return points_y[i];};

	void printGrid(int width = 10, int prec = 4) const;

	double unifgrid(size_t i, double leftval, double rightval, double numberofpoints) const;

	double chebishevgrid(size_t i, double leftval, double rightval, double numberofpoints) const;

	size_t size() const {return points_x.size(); };

	void setunifgrid(fun f);

	void setchebishevgrid(fun f);
public:

	Grid();
	Grid(double leftval, double rightval, double numberofpoints);
};
#endif