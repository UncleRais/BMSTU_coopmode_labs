#ifndef MATRIX_CPP
#define MATRIX_CPP

#include "./Matrix.h"
#include "../Algorithms/Gauss/Gauss.cpp"
#include "../Foundation.cpp"
#include <memory.h>

template<typename T> 
size_t Matrix<T>::fullSize() const {
	return systemSize * systemSize;
}

template<typename T>
size_t Matrix<T>::size() const {
	return systemSize;
}

template<typename T> 
T& Matrix<T>::rightValueRef(const size_t at) {
	return rightvalues_[at];
}

template<typename T> 
T Matrix<T>::rightValue(const size_t at) {
	return rightvalues_[at];
}

template<typename T> 
	T& Matrix<T>::at(const size_t row, const size_t col) 
{
	return matrix_[rows_[row] * systemSize + cols_[col]];
}

template<typename T> 
T Matrix<T>::atvalue(const size_t row, const size_t col)  const 
{
	return matrix_[rows_[row] * systemSize + cols_[col]];
}

template<typename T> 
void Matrix<T>::swapCols(const size_t first, const size_t second) {
	std::swap(cols_[first], cols_[second]);
}

template<typename T> 
void Matrix<T>::swapRows(const size_t first, const size_t second) {
	std::swap(rows_[first], rows_[second]);
}

template<typename T> 
void Matrix<T>::printsystem(int width, int prec) const 
{
	for(size_t i = 0; i < systemSize * (width + 1); ++i)
			std::cout << "-";
		std::cout << "-\n";
	for (size_t i = 0; i < systemSize; ++i)
		{			
			std::cout << "| "; 
			for (size_t j = 0; j < systemSize; ++j)
				std::cout << std::setw(width) << std::setprecision(prec)<< atvalue(i, j) << " ";
			std::cout << "| " << rightvalues_[i] << "\n";
		}
		for(size_t i = 0; i < systemSize * (width + 1); ++i)
			std::cout << "-";
		std::cout << "-\n";
}

template<typename T> 
void Matrix<T>::changerightvalues(const std::vector<T>& rightvalues)
{
	try
	{
		if (systemSize != rightvalues.size()) {
		throw dimensionsIncongruity;
		}
		rightvalues_ = rightvalues;
	} catch (FileError error) {
		std::string errorDescription;
		switch (error) {
			case dimensionsIncongruity:
				errorDescription = "The dimensions don't match!";
				break;
			default:
				errorDescription = "The dimensions don't match!"; 
		}
		std::cerr << errorDescription << std::endl;
		exit(5);
	}
}

template<typename T> 
void Matrix<T>::inverse()
{
	invmatrix_.reserve(systemSize * systemSize);
	if (!isinversed)
	{
		invmatrix_ = std::vector<T>(systemSize * systemSize, 0);
		// memset(invmatrix_.data(), 0, sizeof(T)*systemSize * systemSize);
		std::vector<T> partofright(systemSize, 0.0); // columns of an E matrix
		for (size_t i = 0; i < systemSize; ++i){
			partofright[i] = 1;
			if(i > 0) partofright[i - 1] = 0.0;
			Matrix<T> system(matrix_, partofright);
			const auto result = Gauss::solve(system);
			for (size_t j = 0; j < systemSize; ++j) 
			{
				invmatrix_[j * systemSize + i] = result[j];
			}
		}
		isinversed = true;
	}
}

template<typename T> 
Matrix<T> Matrix<T>::inversed()
{
	inverse();
	return Matrix<T>(invmatrix_,rightvalues_);
}

template<typename T>
void Matrix<T>::transpose() {
	for (size_t k = 0; k < systemSize - 1; ++k) 
	{
		for (size_t i = k; i < systemSize; ++i) 
		{
			std::swap(at(k, i), at(i, k));
		}
	}
}

template<typename T>
Matrix<T> Matrix<T>::transposed() {
	Matrix<T> result(*this);
	result.transpose();
	return result;
}

template<typename T>
void Matrix<T>::printInverse(int width, int prec) const
{
	 	for (size_t i = 0; i < systemSize; ++i)
			{			
				std::cout <<"| "; 
				for (size_t j = 0; j < systemSize; ++j)
					std::cout << std::setprecision(prec) << std::setw(width) << invmatrix_[i * systemSize + j] << " ";
				std::cout << "|\n"; 
			}
};

template<typename T> 
T Matrix<T>::norminf() const
{
	T sum, maxsum = 0;
	for(size_t i = 0; i < systemSize; ++i)
	{
		sum = 0;
		for(size_t j = 0; j < systemSize; ++j)
		{
			sum += atvalue(j , i);
		}
		if (maxsum < sum) maxsum = sum;
	}
			
	return maxsum;
}

template<typename T> 
T Matrix<T>::normfirst() const
{
	T sum, maxsum = 0;
	for(size_t i = 0; i < systemSize; ++i)
	{
		sum = 0;
		for(size_t j = 0; j < systemSize; ++j)
		{
			sum += atvalue(i , j);
		}
		if (maxsum < sum) maxsum = sum;
	}
			
	return maxsum;
}

template<typename T> 
T Matrix<T>::normmax() const
{
	const auto iter = std::max_element(matrix_.begin(), matrix_.end());
	return *iter * systemSize;
}

template<typename T> 
void Matrix<T>::makeoutrage(T sign)
{
	for(size_t i = 0; i < systemSize; ++i)
		rightvalues_[i] += sign * 0.01;
}

template<typename T>
std::vector<T> Matrix<T>::operator *(const std::vector<T>& rightvector)
{
	std::vector<T> result(systemSize, 0.0);
	for (size_t i = 0; i < systemSize; ++i)
	{
		for (size_t j = 0; j < systemSize; ++j)
		{
			result[i] += atvalue(i, j) * rightvector[j];
		}
	}
	return result; 
}

template<typename T> 
Matrix<T>::Matrix() {}

template<typename T> 
Matrix<T>::Matrix(const std::vector<T>& matrix, const std::vector<T>& rightvalues) 
{
	try
	{
		if (sqrt(matrix.size()) != rightvalues.size()) {
		throw dimensionsIncongruity;
		}
		matrix_ = matrix;
		rightvalues_ = rightvalues;
		systemSize = rightvalues.size();
		rows_.reserve(systemSize);
		cols_.reserve(systemSize);
		for (size_t i = 0; i < systemSize; ++i)
		{
			rows_.push_back(i); cols_.push_back(i);
		}
	} catch (FileError error) {
		std::string errorDescription;
		switch (error) {
			case dimensionsIncongruity:
				errorDescription = "The dimensions don't match!";
				break;
			default:
				errorDescription = "The dimensions don't match!"; 
		}
		std::cerr << errorDescription << std::endl;
		exit(5);
	}
}

template<typename T> 
Matrix<T>::Matrix(const char * settings)
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
			default:
			break;
		}
		std::cerr << errorDescription << std::endl;
		exit(5);
	}
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& copy) {
	matrix_ = copy.matrix_;
	rightvalues_ = copy.rightvalues_;
	rows_ = copy.rows_;
	cols_ = copy.cols_;
	systemSize = copy.systemSize;
	invmatrix_ = copy.invmatrix_;
}

#endif
