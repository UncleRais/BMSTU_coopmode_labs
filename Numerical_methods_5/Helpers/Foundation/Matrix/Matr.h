#ifndef MATR
#define MATR

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "../Print/Print.cpp"

enum ErrorMatr {
	dimensionsIncongruity,
	linearDependence
};

template< class T> 
class Matr {

private:
	size_t minor_ = 0;
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

	void minor();

	void infminor() { std::cout << minor_ << "\n"; };

	void resetMinor();

	Matr<T> inversed();

	Matr<T> lower();

	Matr<T> upper();

	Matr<T> diagonal(); 

	void transpose();

	Matr<T> transposed();

	T normfirst() const;

	T norminf() const;

	T normmax() const;

	T normestimate(const std::vector<T>& vec);

	bool symmetrical(T epsilon = 1e-3) const;

	Matr<T> uppertriangular() const;

	bool criteriaSylvester() const;

	Matr<T> toHessenberg() const;
public:
	std::vector<T> operator *(const std::vector<T>& rightvector);

	Matr<T> operator *(const Matr<T>& matrix);

	Matr<T> operator +(const Matr<T>& matrix);

	Matr<T> operator -(const Matr<T>& matrix);

	Matr<T> operator *(T value) const;

	Matr<T> operator /(T value) const;

	Matr<T>& operator =(const Matr<T>& rightv);

public:

	Matr(){ std::cout << "def\n";};

	Matr(const std::vector<T>& matrix);

	Matr(const Matr<T>& copy);

	Matr(size_t matrsize, T value);


};

#endif