#include <iostream>
#include "./GoldenSectionSearch.cpp"

double func (double x) {
	return x * x * x;
}

int main(int argc, char *argv[]) {
	GoldenSectionSearch(-1, 1, func).run(10e-6);
}