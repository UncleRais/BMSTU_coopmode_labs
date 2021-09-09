#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>
#include "../../Helpers/Range.cpp"

typedef std::function<double(double)> UnimodalFunction;
typedef std::vector<double> DoubleArray;
typedef Range<double> RealRange;

struct GoldenSectionSearch {
//MARK: Private properties 
private:
	UnimodalFunction func;
	RealRange range;
	DoubleArray lengths = {};

//MARK: Algorithm
public:
	void run(double eps = 10e-4) {
		double leftX = getLeftX();
		double leftY = func(leftX);
		double rightX = getRightX();
		double rightY = func(rightX);
		double length = range.getLength();
		size_t numberOfIterations = 0;
		size_t valuesCount = 2;

		std::ofstream file;
		file.open("../Results/golden.dat");

		while ( abs(length) >= eps ) {
			file << length << std::endl;
			++numberOfIterations;
			++valuesCount;
			if (leftY >= rightY) {
				range.setStart(leftX);
				leftX = rightX;
				leftY = rightY;
				rightX = getRightX();
				rightY = func(rightX);
			} else {
				range.setEnd(rightX);
				rightX = leftX;
				rightY = leftY;
				leftX = getLeftX();
				leftY = func(leftX);
			}
			length = range.getLength();
		}
		file << length << std::endl;
		file.close();
		double x = range.getMiddleValue();
		double y = func(x);
		std::cout << "Iterations: " << numberOfIterations << std::endl
				  << "Values: " << valuesCount << std::endl  
				  << "x⋆ = " << x << std::endl
				  << "y(x⋆) = " << y << std::endl;
	}

private:

	double getLeftX() {
		return range.getStart() + (1 - 1 / 1.618) * range.getLength();
	}

	double getRightX() {
		return range.getStart() + range.getLength() / 1.618;
	}

//MARK: Init
public:
	GoldenSectionSearch(
		const double start = 0, 
		const double end = 0, 
		const UnimodalFunction& _func = [](double x) { return x * x; }
	) : GoldenSectionSearch(RealRange(start, end), _func) {}

	GoldenSectionSearch(
		const RealRange& _range, 
		const UnimodalFunction& _func = [](double x) { return x * x; }
	){
		func = _func;
		range = _range;
	}
};