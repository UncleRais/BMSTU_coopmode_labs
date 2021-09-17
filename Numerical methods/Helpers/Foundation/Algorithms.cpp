#ifndef Algorithms
#define Algorithms

#include<iostream>
#include<fstream>
#include<iterator>
#include<vector>
#include<iomanip>
#include<cmath>
#include<algorithm>
#include "./Matrix.cpp"
#include "./Foundation.cpp"

template < typename T >
T absolute(const T value) {
	return value < 0 ? -value : value;
}


enum Method {
	gauss,
	qr,
};

struct SwappingElements {
	size_t first_;
	size_t second_; 
	bool isEqual;

	SwappingElements(const size_t first = 0, const size_t second = 0) {
		first_ = first; second_ = second;
		isEqual = first == second;
	}
};

template<
	typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
> 
struct MatrixAlgorithms {
private:
	typedef std::vector<T> Vector;
	typedef std::vector<size_t> Indices;
	typedef std::vector<SwappingElements> Journal;

	static SwappingElements partialColumnSelection(const size_t startCol, Matrix<T>& matrix) {
		size_t maxCol = startCol;
		T maxValue = matrix.atvalue(startCol, startCol);
		for (size_t col = startCol + 1; col < matrix.systemSize; ++col) {
			const T nextValue = matrix.atvalue(startCol, col);
			if ( absolute(nextValue) > maxValue ) {
				maxValue = nextValue;
				maxCol = col;
			}
		}
		if (startCol != maxCol) {
			matrix.swapCols(startCol, maxCol);
			return SwappingElements(startCol, maxCol);
		}
		return {}; 
	}

	static void resetIndexation(Vector& vector, const Journal& swapJournal) {
		for (auto it = swapJournal.rbegin(); it < swapJournal.rend(); ++it) {
			const size_t leftIndex = it->first_;
			const size_t rightIndex = it->second_;
			std::swap(vector[rightIndex], vector[leftIndex]);
		}
	}

	//MARK: - Convenient functions (internal use)
	static Vector gaussMethod(Matrix<T>& matrix) {
		Journal journal = {};
		for(size_t k = 0; k < matrix.systemSize - 1; ++k)
		{
		    const SwappingElements newSwappingElement = partialColumnSelection(k, matrix);
		    if (!newSwappingElement.isEqual) {
		    	journal.push_back(newSwappingElement);
		    }
			for(size_t row = k + 1; row < matrix.systemSize; ++row)
			{
				T value = matrix.atvalue(row , k);
				for(size_t col = k; col < matrix.systemSize; ++col)
				{
					matrix.at(row,col) -= matrix.at(k, col) * value / matrix.at(k , k); 
				}
				matrix.rightvalues_[row] -= matrix.rightvalues_[k] * value / matrix.at(k , k); 
			}
		}
		Vector solution(matrix.systemSize, 0.0);
		for (int row = matrix.systemSize - 1; row >= 0; --row)
		{
			T x = 0.0;
			x += matrix.rightvalues_[row];			
			for(int col = matrix.systemSize - 1; col > row ; --col )
			{
				x -= matrix.at(row, col) * solution[col];
			} 
			x /= matrix.at(row,row);
			solution[row] = x;
		}	
		resetIndexation(solution, journal); 
		return solution;
	}

public:
	static std::vector<T> linearSolve(Matrix<T> matrix,const Method method = gauss) {
		return gaussMethod(matrix);
	}
};

#endif
