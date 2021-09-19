#ifndef GAUSS
#define GAUSS

#include "./Gauss.h"
#include <cmath>

// template < typename T >
// FactorizationResult Gauss::factor(Matrix<T>& matrix) {
// 	for(size_t k = 0; k < matrix.size() - 1; ++k)
// 	{
// 	    partialColumnSelection(k, matrix);
// 		for(size_t row = k + 1; row < matrix.size(); ++row)
// 		{
// 			T value = matrix.atvalue(row , k);
// 			for(size_t col = k; col < matrix.size(); ++col)
// 			{
// 				matrix.at(row,col) -= matrix.at(k, col) * value / matrix.at(k , k); 
// 			}
// 			matrix.rightValue(row) -= matrix.rightValue(k) * value / matrix.at(k , k); 
// 		}
// 	}
// }

template < typename T >
std::vector<T> Gauss::solve(Matrix<T> matrix) {
	std::vector<SwappingElements> journal = {};
	for(size_t k = 0; k < matrix.size() - 1; ++k)
	{
	    const SwappingElements newSwappingElement = partialColumnSelection(k, matrix);
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
			matrix.rightValue(row) -= matrix.rightValue(k) * value / matrix.at(k , k); 
		}
	}

	//MARK: - check if the matrix is not invertible
	for (size_t k = 0; k < matrix.size(); ++k) {
		if( absolute(matrix.at(k, k)) < __DBL_EPSILON__ ) {
			std::cerr << "Matrix is not invertible.\n";
			exit(-4);
		}
	}

	std::vector<T> solution(matrix.size(), 0.0);
	for (int row = matrix.size() - 1; row >= 0; --row)
	{
		T x = 0.0;
		x += matrix.rightValue(row);			
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

#endif