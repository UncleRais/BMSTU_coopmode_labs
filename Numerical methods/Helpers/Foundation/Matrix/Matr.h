#ifndef MATR
#define MATR

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "../Print/Print.cpp"

enum ErrorMatr {
	dimensionsIncongruity,
};


template<typename T> 
class Matr {

public:
	std::vector<size_t> rows_ = {};
	std::vector<size_t> cols_ = {};
	std::vector<T> matrix_ = {};
	size_t systemSize;

public:
	void setsize(size_t size);
	
	void reserve(size_t size);

	void push_back_rows(size_t i);

	void push_back_cols(size_t i);

	void push_back(T value);

	size_t fullSize() const;

	size_t size() const;

	//MARK: - Shared functions
 	T& at(const size_t row, const size_t col);

	T atvalue(const size_t row, const size_t col)  const;

	void swapCols(const size_t first, const size_t second);

	void swapRows(const size_t first, const size_t second);

	void inverse();

	Matr<T> inversed(); 

	void transpose();

	Matr<T> transposed();

	T normfirst() const;

	T norminf() const;

	T normmax() const;

	T normestimate(const std::vector<T>& vec);
public:
	std::vector<T> operator *(const std::vector<T>& rightvector);

	Matr<T> operator *(const Matr<T>& matrix);

	Matr<T>& operator =(const Matr<T>& rightv);

public:

	Matr();

	Matr(const std::vector<T>& matrix);

	Matr(const Matr<T>& copy);

};

#endif