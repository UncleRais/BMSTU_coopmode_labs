#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <iostream>
#include "../../Matrix/Matr.cpp"
#include "../../Foundation.cpp"

struct SwappingElement {
	size_t first_;
	size_t second_; 
	bool isEqual;

	SwappingElement(const size_t first = 0, const size_t second = 0) {
		first_ = first; second_ = second;
		isEqual = first == second;
	}
};

class MatrixAlgorithm {
protected:
	template < typename T >
	static SwappingElement partialColumnSelection(const size_t startCol, Matr<T>& matrix);

	template < typename T > 
	static void resetIndexation(std::vector<T>& vector, const std::vector<SwappingElement>& swapJournal);

public:
	template < typename T > 
	static std::vector<T> solve(Matr<T> matrix) = delete;

	template < typename T > 
	static T misclosure(Matr<T>& matrix, const std::vector<T>& vec, const std::vector<T>& x);
};

#endif
