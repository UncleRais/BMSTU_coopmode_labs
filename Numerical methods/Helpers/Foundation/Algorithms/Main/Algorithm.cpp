#ifndef ALGORITHM_CPP
#define ALGORITHM_CPP

#include "./Algorithm.h"
#include "../../Foundation.cpp"

template <typename T>
SwappingElement MatrixAlgorithm::partialColumnSelection(const size_t startCol, Matr<T>& matrix) {
	size_t maxCol = startCol;
	T maxValue = matrix.atvalue(startCol, startCol);
	for (size_t col = startCol + 1; col < matrix.size(); ++col) {
		const T nextValue = matrix.atvalue(startCol, col);
		if ( fabs(nextValue) > maxValue ) {
			maxValue = nextValue;
			maxCol = col;
		}
	}
	if (startCol != maxCol) {
		matrix.swapCols(startCol, maxCol);
		return SwappingElement(startCol, maxCol);
	}
	return {}; 
}

template < typename T >
void MatrixAlgorithm::resetIndexation(std::vector<T>& vector, const std::vector<SwappingElement>& swapJournal) {
	for (auto it = swapJournal.rbegin(); it < swapJournal.rend(); ++it) {
		const size_t leftIndex = it->first_;
		const size_t rightIndex = it->second_;
		std::swap(vector[rightIndex], vector[leftIndex]);
	}
}

template < typename T >
Matr<T> MatrixAlgorithm::dot(const Matr<T>& A, const Matr<T>& B) {
	const size_t size = A.size();
	std::vector<T> result(size * size, 0);
	for (size_t i = 0; i < size; ++i)
	{
		for (size_t j = 0; j < size; ++j)
		{
			for (size_t k = 0; k < size; ++k)
			{
				result[i * size + j] += A.atvalue(i, k) * B.atvalue(k, j);  
			}
		}
	}
	return Matr<T>(result);  
}

template < typename T >
std::vector<T> MatrixAlgorithm::dot(const Matr<T>& A, const std::vector<T>& B) {
	const size_t size = A.size();
	std::vector<T> result(size, 0.0);
	for (size_t i = 0; i < size; ++i)
	{
		for (size_t j = 0; j < size; ++j)
		{
			result[i] += A.atvalue(i, j) * B[j];
		}
	}
	return result; 
}

template < typename T > 
T MatrixAlgorithm::misclosure( Matr<T>& matrix, const std::vector<T>& vec, const std::vector<T>& x) {
	const std::vector<T> Ax(matrix * x);
	std::vector<T> result(x.size(), 0.0);
	for (size_t i = 0; i < x.size(); ++i)
	{  
		result[i] = Ax[i] - vec[i];
	}

	return Math::norm(result);
}

#endif
