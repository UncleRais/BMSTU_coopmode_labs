#ifndef MATRIX
#define MATRIX

#include "../Helpers/Foundation.cpp"

enum Method {
	gauss,
	qr,
};

template<
	typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
> 
struct SwappingElements {
	T first_, second_; 

	SwappingElements(const T first, const T second) {
		first_ = first; second_ = second;
	}
};

template<
	typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
> 
class Matrix {
	typedef std::vector<T> Vector;
	typedef std::vector<size_t> Indices;
	typedef std::vector<SwappingElements<T>> Journal;

private:
	Journal swapJournal = {};
	Indices rows_ = {};
	Indices cols_ = {};
	Vector matrix_ = {};
	Vector rightvalues_ = {};
	size_t systemSize;

	void partialColumnSelection(const size_t startCol) {
		size_t maxCol = startCol;
		T maxValue = at(startCol, startCol);
		for (size_t col = startCol + 1; col < systemSize; ++col) {
			const T nextValue = atvalue(startCol, col);
			if ( absolute(nextValue) > maxValue ) {
				maxValue = nextValue;
				maxCol = col;
			}
		}
		if (startCol != maxCol) {
			swapJournal.push_back(SwappingElements<T>(startCol, maxCol));
			std::swap(cols_[startCol], cols_[maxCol]);
		}
	}

	void resetIndexation(Vector& vector) {
		for (auto it = swapJournal.rbegin(); it < swapJournal.rend(); ++it) {
			const size_t leftIndex = it->first_;
			const size_t rightIndex = it->second_;
			std::swap(vector[rightIndex], vector[leftIndex]);
		}
	}

	//MARK: - Convenient functions (internal use)
	Vector gaussMethod() {
		for(size_t k = 0; k < systemSize - 1; ++k)
		{
		    partialColumnSelection(k);
			for(size_t row = k + 1; row < systemSize; ++row)
			{
				T value = atvalue(row , k);
				for(size_t col = k; col < systemSize; ++col)
				{
					at(row,col) -= at(k, col) * value / at(k , k); 
				}
				rightvalues_[row] -= rightvalues_[k] * value / at(k , k); 
			}
		}
		Vector solution(systemSize, 0.0);
		for (int row = systemSize - 1; row >= 0; --row)
		{
			T x = 0.0;
			x += rightvalues_[row];			
			for(int col = systemSize - 1; col > row ; --col )
			{
				x -= at(row, col) * solution[col];
			} 
			x /= at(row,row);
			solution[row] = x;
		}	
		resetIndexation(solution); 
		return solution;
	}

public:
	//MARK: - Shared functions
 	T& at(const size_t row, const size_t col) 
	{
		return matrix_[rows_[row] * systemSize + cols_[col]];
	}

	T atvalue(const size_t row, const size_t col) 
	{
		return matrix_[rows_[row] * systemSize + cols_[col]];
	}

	void printsystem(int width = 7, int prec = 4) 
	{
		for(size_t i = 0; i < systemSize * (width + 1); ++i)
				std::cout << "-";
			std::cout << "-\n";
		for (size_t i = 0; i < systemSize; ++i)
			{			
				std::cout << "| "; 
				for (size_t j = 0; j < systemSize; ++j)
					std::cout << std::setw(width) << std::setprecision(prec)<< at(i, j) << " ";
				std::cout << "| " << rightvalues_[i] << "\n";
			}
			for(size_t i = 0; i < systemSize * (width + 1); ++i)
				std::cout << "-";
			std::cout << "-\n";
	}

	Vector linearSolve(Method method) {
		switch (method) {
		case gauss:
			return gaussMethod();
			break;
		case qr:
			return {};
		}
		return{};
	}

	Matrix() {}

	Matrix(const char * settings)
	{
		try { 
			std::ifstream iFile;
			iFile.open(settings);
			if (!iFile.is_open() ) { 
				throw settingsNotFound;
			}
			//Taking info from settings.dat
			iFile >> systemSize;
			std::string matrixName, vectorName, outputName;
			iFile >> matrixName;
			iFile >> vectorName;
			iFile >> outputName;
			iFile.close();

			//Collecting info about linear system
			iFile.open(matrixName);
			if (!iFile.is_open()) {
				throw matrixNotFound;
			}

			std::ifstream vectorFile;
			vectorFile.open(vectorName);
			if (!iFile.is_open()) {
				throw vectorNotFound;
			}

			matrix_.reserve(systemSize * systemSize);
			rows_.reserve(systemSize);
			cols_.reserve(systemSize);
			rightvalues_.reserve(systemSize);
			double value;
			for (size_t i = 0; i < systemSize; ++i)
			{
				rows_.push_back(i); cols_.push_back(i);
				for (size_t j = 0; j < systemSize; ++j)
				{
					iFile >> value;
					matrix_.push_back(value);
				}
			vectorFile >> value;
			rightvalues_.push_back(value);
			}
			iFile.close();
			vectorFile.close();
		} catch (FileError error) {
			std::string errorDescription;
			switch (error) {
				case settingsNotFound:
					errorDescription = "Settings not found\n";
					break;
				case matrixNotFound:
					errorDescription = "Matrix not found\n";
					break;
				case vectorNotFound:
					errorDescription = "Vector not found\n";
			}
			std::cerr << errorDescription << std::endl;
			exit(5);
		}
	};

	~Matrix(){};
};

#endif