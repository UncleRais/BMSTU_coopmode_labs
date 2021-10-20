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
	std::vector<double> points_inter_y = {};

public:

	double& atx(const size_t i) {return points_x[i];};

	double atvalx(const size_t i)  const {return points_x[i];};

	double& aty(const size_t i) {return points_y[i];};

	double atvaly(const size_t i)  const {return points_y[i];};

	double& atintery(const size_t i) {return points_inter_y[i];};

	double atvalintery(const size_t i)  const {return points_inter_y[i];};

	void printGrid(int width = 10, int prec = 4) const;

	double unifgrid(size_t i, double leftval, double rightval, size_t numberofpoints) const;

	double chebishevgrid(size_t i, double leftval, double rightval, size_t numberofpoints) const;

	double coefLagrange(size_t numcoef, double point) const;

	double interpolationLagrange(double point) const;

	size_t size() const {return numberofpoints_; };

	size_t intersize() const {return points_inter_y.size();};

	void setunifgrid(fun f);

	void setchebishevgrid(fun f);

	void calculateLagrange(double leftval, double rightval, size_t numberofpoints);

	double funcnorm(fun f); 
public:

	Grid();
	Grid(double leftval, double rightval, size_t numberofpoints);
};
#endif