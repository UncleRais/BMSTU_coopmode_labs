#ifndef MATRIX
#define MATRIX

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "../Print.cpp"

enum FileError {
	dimensionsIncongruity,
	settingsNotFound,
	matrixNotFound,
	vectorNotFound,
};

template<typename T> 
class Matrix {

private:
	std::vector<size_t> rows_ = {};
	std::vector<size_t> cols_ = {};
	std::vector<T> matrix_ = {};
	std::vector<T> invmatrix_ = {};
	std::vector<T> rightvalues_ = {};
	size_t systemSize;

public:
	size_t fullSize() const;

	size_t size() const;

	T& rightValue(const size_t at);

	//MARK: - Shared functions
 	T& at(const size_t row, const size_t col);

	T atvalue(const size_t row, const size_t col)  const;

	void swapCols(const size_t first, const size_t second);

	void swapRows(const size_t first, const size_t second);

	void printsystem(int width = 7, int prec = 4);

	void changerightvalues(const std::vector<T>& rightvalues);

	void inverse();

	void printInverse(int width = 7, int prec = 4);

	Matrix();

	Matrix(const std::vector<T>& matrix, const std::vector<T>& rightvalues);

	Matrix(const char * settings);
};

#endif