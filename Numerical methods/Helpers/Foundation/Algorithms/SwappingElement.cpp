#ifndef SWAPPING
#define SWAPPING

#include <iostream>

struct SwappingElements {
	size_t first_;
	size_t second_; 
	bool isEqual;

	SwappingElements(const size_t first = 0, const size_t second = 0) {
		first_ = first; second_ = second;
		isEqual = first == second;
	}
};

#endif