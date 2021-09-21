#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <iostream>
#include "../../Matrix/Matrix.cpp"
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
	static SwappingElement partialColumnSelection(const size_t startCol, Matrix<T>& matrix);

	template < typename T > 
	static void resetIndexation(std::vector<T>& vector, const std::vector<SwappingElement>& swapJournal);

public:
	template < typename T > 
	static std::vector<T> solve(Matrix<T> matrix) = delete;

	template < typename T > 
	static Matrix<T> dot(const Matrix<T>& A, const Matrix<T>& B);

	template < typename T > 
	static std::vector<T> dot(const Matrix<T>& A, const std::vector<T>& B);

	template < typename T > 
	static T misclosure(const Matrix<T>& matrix, const std::vector<T>& x, const std::vector<T>& b);
};

#endif
