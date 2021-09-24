#ifndef MATRIX
#define MATRIX

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "../Print/Print.cpp"

enum FileError {
	dimensionsIncongruity,
	settingsNotFound,
	matrixNotFound,
	vectorNotFound,
};

template<typename T> 
class Matrix {

public:
	std::vector<size_t> rows_ = {};
	std::vector<size_t> cols_ = {};
	std::vector<T> matrix_ = {};
	std::vector<T> invmatrix_ = {};
	bool isinversed = false;
	std::vector<T> rightvalues_ = {};
	size_t systemSize;

public:
	size_t fullSize() const;

	size_t size() const;

	T& rightValueRef(const size_t at);

	T rightValue(const size_t at);

	//MARK: - Shared functions
 	T& at(const size_t row, const size_t col);

	T atvalue(const size_t row, const size_t col)  const;

	void swapCols(const size_t first, const size_t second);

	void swapRows(const size_t first, const size_t second);

	void printsystem(int width = 7, int prec = 4) const;

	void changerightvalues(const std::vector<T>& rightvalues);

	void inverse();

	Matrix<T> inversed(); 

	void transpose();

	Matrix<T> transposed();

	void printInverse(int width = 7, int prec = 4) const;

	T norminf() const;

	T normfirst() const;

	T normmax() const;

	void makeoutrage(T sign);
public:
	std::vector<T> operator *(const std::vector<T>& rightvector);

public:

	Matrix();

	Matrix(const std::vector<T>& matrix, const std::vector<T>& rightvalues);

	Matrix(const char * settings);

	Matrix(const Matrix<T>& copy);
};

#endif