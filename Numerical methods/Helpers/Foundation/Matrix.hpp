#ifndef MATRIX
#define MATRIX

#include "./Foundation.cpp"

enum FileError {
	settingsNotFound,
	matrixNotFound,
	vectorNotFound,
};

template<
	typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
> 
class Matrix {
	typedef std::vector<T> Vector;
	typedef std::vector<size_t> Indices;

private:
	Indices rows_ = {};
	Indices cols_ = {};
	Vector matrix_ = {};
	Vector rightvalues_ = {};
	size_t systemSize;

public:
	size_t fullSize() const {
		return systemSize * systemSize;
	}

	size_t size() const {
		return systemSize;
	}

	T& rightValue(const size_t at) {
		return rightvalues_[at];
	}

	//MARK: - Shared functions
 	T& at(const size_t row, const size_t col) 
	{
		return matrix_[rows_[row] * systemSize + cols_[col]];
	}

	T atvalue(const size_t row, const size_t col)  const 
	{
		return matrix_[rows_[row] * systemSize + cols_[col]];
	}

	void swapCols(const size_t first, const size_t second) {
		std::swap(cols_[first], cols_[second]);
	}

	void swapRows(const size_t first, const size_t second) {
		std::swap(rows_[first], rows_[second]);
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