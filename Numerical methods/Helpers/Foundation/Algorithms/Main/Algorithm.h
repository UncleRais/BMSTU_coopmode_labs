#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <iostream>
#include "../../Matrix.cpp"

struct SwappingElements {
	size_t first_;
	size_t second_; 
	bool isEqual;

	SwappingElements(const size_t first = 0, const size_t second = 0) {
		first_ = first; second_ = second;
		isEqual = first == second;
	}
};

class MatrixAlgorithm {
private:
	template < typename T >
	static SwappingElements partialColumnSelection(const size_t startCol, Matrix<T>& matrix);

	template < typename T > 
	static void resetIndexation(std::vector<T>& vector, const std::vector<SwappingElements>& swapJournal);

public:
	template < typename T > 
	static std::vector<T> solve(Matrix<T> matrix) = delete;
};

#endif
