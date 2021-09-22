#ifndef GAUSS
#define GAUSS

#include "./Gauss.h"
#include <cmath>
#include "../../Foundation.cpp"
#include "../../Math.cpp"

template < typename T >
std::vector<SwappingElement> Gauss::forwardMove(Matrix<T>& matrix) {
	std::vector<SwappingElement> journal = {};
	for(size_t k = 0; k < matrix.size() - 1; ++k)
	{
	    const SwappingElement newSwappingElement = partialColumnSelection(k, matrix);
	    if (!newSwappingElement.isEqual) {
	    	journal.push_back(newSwappingElement);
	    }
		for(size_t row = k + 1; row < matrix.size(); ++row)
		{
			T value = matrix.atvalue(row , k);
			for(size_t col = k; col < matrix.size(); ++col)
			{
				matrix.at(row,col) -= matrix.at(k, col) * value / matrix.at(k , k); 
			}
			matrix.rightValueRef(row) -= matrix.rightValue(k) * value / matrix.at(k , k); 
		}
	}
	return journal;
}

template < typename T >
std::vector<T> Gauss::backwardMove(Matrix<T>& matrix, const std::vector<SwappingElement>& journal) {
	std::vector<T> solution(matrix.size(), 0.0);
	for (int row = matrix.size() - 1; row >= 0; --row)
		{
			T x = 0.0;
			x += matrix.rightValueRef(row);			
			for(int col = matrix.size() - 1; col > row ; --col )
			{
				x -= matrix.at(row, col) * solution[col];
			} 
			x /= matrix.at(row,row);
			solution[row] = x;
		}	
	resetIndexation(solution, journal); 
	return solution;
}

template < typename T >
std::vector<T> Gauss::solve(Matrix<T> matrix, bool uppertriangular) {
	std::vector<SwappingElement> journal;
	if (!uppertriangular)
	{
		journal = forwardMove(matrix);
	} else
	{
		journal = {};
	}

	//MARK: - check if the matrix is not invertible
	for (size_t k = 0; k < matrix.size(); ++k) {
		if(absolute(matrix.at(k, k)) < __DBL_EPSILON__ ) {
			std::cerr << "Matrix is not invertible.\n";
			exit(-4);
		}
	}

	return backwardMove(matrix, journal);
}

#endif