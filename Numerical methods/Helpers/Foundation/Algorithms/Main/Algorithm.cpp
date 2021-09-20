#ifndef ALGORITHM_CPP
#define ALGORITHM_CPP

#include "./Algorithm.h"
#include "../../Foundation.cpp"

template <typename T>
SwappingElement MatrixAlgorithm::partialColumnSelection(const size_t startCol, Matrix<T>& matrix) {
	size_t maxCol = startCol;
	T maxValue = matrix.atvalue(startCol, startCol);
	for (size_t col = startCol + 1; col < matrix.size(); ++col) {
		const T nextValue = matrix.atvalue(startCol, col);
		if ( Math::absolute(nextValue) > maxValue ) {
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


#endif
