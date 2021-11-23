#ifndef MATR_CPP
#define MATR_CPP

#include "./Matr.h"
#include "../Algorithms/Gauss/Gauss.cpp"
#include "../Foundation.cpp"
#include <memory.h>

template<typename T>
void Matr<T>::setsize(size_t size)
{
	systemSize = size;
}


template<typename T>
void Matr<T>::reserve(size_t size)
{
	matrix_.reserve(size * size);
	rows_.reserve(size);
	cols_.reserve(size);
}

template<typename T>
void Matr<T>::push_back_rows(size_t i)
{
	cols_.push_back(i);
}

template<typename T>
void Matr<T>::push_back_cols(size_t i)
{
	rows_.push_back(i);
}

template<typename T>
void Matr<T>::push_back(T value)
{
	matrix_.push_back(value);
}

template<typename T> 
size_t Matr<T>::fullSize() const {
	return systemSize * systemSize;
}

template<typename T>
size_t Matr<T>::size() const {
	return systemSize;
}

template<typename T> 
T& Matr<T>::at(const size_t row, const size_t col) 
{
	return matrix_[rows_[row] * systemSize + cols_[col]];
}

template<typename T> 
T Matr<T>::atvalue(const size_t row, const size_t col)  const 
{
	return matrix_[rows_[row] * systemSize + cols_[col]];
}

template<typename T> 
void Matr<T>::swapCols(const size_t first, const size_t second) {
	std::swap(cols_[first], cols_[second]);
}

template<typename T> 
void Matr<T>::swapRows(const size_t first, const size_t second) {
	std::swap(rows_[first], rows_[second]);
}

template<typename T> 
void Matr<T>::inverse()
{
	*this = inversed();
}

template<typename T> 
void Matr<T>::minor()
{
	const size_t shrinked = systemSize - 1;
	std::vector<T> buffer;
	buffer.reserve(pow(shrinked, 2));
	for (int i = 0; i < fullSize() - systemSize; ++i) 
	{
		if ((i + 1) % systemSize == 0) { continue; }
		buffer.push_back(matrix_[i]);
	}
	systemSize = shrinked;
	matrix_ = buffer;
}

template<typename T> 
Matr<T> Matr<T>::inversed()
{
	std::vector<T> invmatrix_(systemSize * systemSize, 0);
	std::vector<T> partofright(systemSize, 0.0); // columns of an E matrix
	for (size_t i = 0; i < systemSize; ++i)
	{
		partofright[i] = 1;
		if(i > 0) partofright[i - 1] = 0.0;
		const auto result = Gauss::solve(*this, partofright);
		for (size_t j = 0; j < systemSize; ++j) 
		{
			invmatrix_[j * systemSize + i] = result[j];
		}
	}
	return Matr<T>(invmatrix_);
}

template<typename T> 
Matr<T> Matr<T>::lower()
{
	std::vector<T> result(systemSize * systemSize, 0);
		for (size_t i = 0; i < systemSize; ++i)
			for (size_t j = 0; j < i; ++j)
				result[i + systemSize * j] = atvalue(i, j);
		
	return Matr<T>(result);
}

template<typename T> 
Matr<T> Matr<T>::upper()
{
	std::vector<T> result(systemSize * systemSize, 0);
	for (size_t i = 0; i < systemSize; ++i)
		for (size_t j = i + 1; j < systemSize; ++j)
			result[i + systemSize * j] = atvalue(i, j);
	
	return Matr<T>(result);
}

template<typename T> 
Matr<T> Matr<T>::diagonal()
{
	std::vector<T> result(systemSize * systemSize, 0);
	for (size_t i = 0; i < systemSize; ++i)
		result[i * systemSize + i] = atvalue(i,i);

	return Matr<T>(result);
}

template<typename T>
void Matr<T>::transpose() {
	for (size_t k = 0; k < systemSize - 1; ++k) 
	{
		for (size_t i = k; i < systemSize; ++i) 
		{
			std::swap(at(k, i), at(i, k));
		}
	}


}

template<typename T>
Matr<T> Matr<T>::transposed() {
	Matr<T> result(*this);
	result.transpose();
	return result;
}

template<typename T> 
T Matr<T>::normfirst() const
{
	T sum, maxsum = 0;
	for(size_t i = 0; i < systemSize; ++i)
	{
		sum = 0;
		for(size_t j = 0; j < systemSize; ++j)
		{
			sum += fabs(atvalue(j , i));
		}
		if (maxsum < sum) maxsum = sum;
	}
			
	return maxsum;
}

template<typename T> 
T Matr<T>::norminf() const
{
	T sum, maxsum = 0;
	for(size_t i = 0; i < systemSize; ++i)
	{
		sum = 0;
		for(size_t j = 0; j < systemSize; ++j)
		{
			sum += fabs(atvalue(i , j));
		}
		if (maxsum < sum) maxsum = sum;
	}
			
	return maxsum;
}

template<typename T> 
T Matr<T>::normmax() const
{
	T max = 0;
	for(size_t i = 0; i < systemSize; ++i)
		for(size_t j = 0; j < systemSize; ++j)
			if (max < fabs(atvalue(i, j))) max = fabs(atvalue(i, j));
	return max * systemSize;
}

template<typename T>
T Matr<T>::normestimate(const std::vector<T>& vec)
{
	std::vector<T> f(vec);
	std::vector<T> x(size(), 0.0);
	std::vector<T> dx(size(), 0.0);
	std::vector<T> df(size(), 0.01);
	T normf , normx , normdf, normdx;
	x = Gauss::solve(*this, f);
	dx = Gauss::solve(*this, f + df);
	normf = Math::norm(f);
	normdx = Math::norm(dx - x);
	normx = Math::norm(x);
	normdf = Math::norm(df);
	return ((normdx * normf) / (normdf * normx));
}

template<typename T>
bool Matr<T>::symmetrical(T epsilon) const
{
	for(size_t i = 1; i < size(); ++i)
		for (size_t j = 0; j < i; ++j)
			if(fabs(atvalue(i , j) - atvalue(j , i)) >= epsilon)
				return false;
	return true;
}

template<typename T>
Matr<T> Matr<T>::uppertriangular() const
{
	try
	{
	Matr<T> result(*this);
	for(size_t k = 0; k < result.size() - 1; ++k)
	{
		for(size_t row = k + 1; row < result.size(); ++row)
			{
				if (fabs(result.at(k , k)) < __DBL_EPSILON__)
				{
					throw linearDependence;
				}
				T value = result.atvalue(row , k);
				for(size_t col = k; col < result.size(); ++col)
				{
					result.at(row,col) -= result.at(k, col) * value / result.at(k , k); 
				}
			}
	}		
	return result;
	} catch (ErrorMatr error) {
		std::string errorDescription;
		switch (error) {
			case linearDependence:
				errorDescription = "Matrix is degenerate!";
				break;
			default:
				errorDescription = "Matrix is degenerate!"; 
		}
		std::cerr << errorDescription << std::endl;
		exit(5);
	}  
}

template<typename T>
bool Matr<T>::criteriaSylvester() const
{
		if(symmetrical())
		{
			Matr<T> upper(uppertriangular());
			T value = 1.0;
			for(size_t i = 0; i < size(); ++i)
			{
				value *= upper.atvalue(i,i);
				if(value < __DBL_EPSILON__) return false;
			}
			return true;
		} else
		{
			return false;
		}
}

template<typename T>
Matr<T> Matr<T>::operator +(const Matr<T>& matrix)
{
	std::vector<T> result(systemSize * systemSize, 0.0);

	for (size_t i = 0; i < systemSize; ++i)
		for (size_t j = 0; j < systemSize; ++j)
			result[i * systemSize + j] = atvalue(i, j) + matrix.atvalue(i, j);

	return Matr<T>(result);
}

template<typename T>
Matr<T> Matr<T>::operator -(const Matr<T>& matrix)
{
	return *this + T((-1)) * matrix; 
}

template<typename T>
std::vector<T> Matr<T>::operator *(const std::vector<T>& rightvector)
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
Matr<T> Matr<T>::operator *(const Matr<T>& matrix)
{
	std::vector<T> result(systemSize * systemSize, 0.0);
	for (size_t i = 0; i < systemSize; ++i)
	{
		for (size_t j = 0; j < systemSize; ++j)
		{
			for (size_t k = 0; k < systemSize; ++k)
			{
				result[i * systemSize + j] += atvalue(i, k) * matrix.atvalue(k, j);  
			}
		}
	}
	return Matr<T>(result);
}

template<typename T>
Matr<T> Matr<T>::operator *(T value) const
{
	Matr<T> result(*this);
	for(size_t i = 0; i < size(); ++i)
	{
		for (size_t j = 0; j < size(); ++j)
		{
			result.at(i , j) *= value;
		}
	}
	return result;
}

template<typename T>
Matr<T> Matr<T>::operator /(T value) const
{
	return T(1 / value) * *this;
}

template<typename T> //Is not class member 
Matr<T> operator *(T value, const Matr<T>& matrix) 
{
	return matrix * value;
}

template<typename T> 
Matr<T>& Matr<T>::operator =(const Matr<T>& rightv)
{
	matrix_ = rightv.matrix_;
	rows_ = rightv.rows_;
	cols_ = rightv.cols_;
	systemSize = rightv.systemSize;
	return *this;
}

template<typename T> 
Matr<T>::Matr() {}

template<typename T> 
Matr<T>::Matr(const std::vector<T>& matrix) 
{
	try
	{
		// if ((modf(sqrt(matrix.size()), nullptr) > 0))
		// {
		// 	throw dimensionsIncongruity;
		// } // PROBLEMS OCCURE HERE

		matrix_ = matrix;
		systemSize = sqrt(matrix.size());
		rows_.reserve(systemSize);
		cols_.reserve(systemSize);
		for (size_t i = 0; i < systemSize; ++i)
		{
			rows_.push_back(i); cols_.push_back(i);
		}
	} catch (ErrorMatr error) {
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
Matr<T>::Matr(const Matr<T>& copy) {
	matrix_ = copy.matrix_;
	rows_ = copy.rows_;
	cols_ = copy.cols_;
	systemSize = copy.systemSize;
}

template<typename T>
Matr<T>::Matr(size_t matrsize, T value) {
	systemSize = matrsize;
	rows_.reserve(systemSize);
	cols_.reserve(systemSize);
	matrix_.reserve(systemSize * systemSize);
	for (size_t i = 0; i < systemSize; ++i)
	{
		for (size_t j = 0; j < systemSize; ++j)
		{
			matrix_[i*systemSize + j] = value;
		}
		rows_.push_back(i); cols_.push_back(i);
	}

}


#endif