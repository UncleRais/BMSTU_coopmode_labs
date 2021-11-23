#ifndef Print_CPP
#define Print_CPP

#include<iostream>
#include<fstream>
#include<iterator>
#include<vector>
#include<iomanip>
#include<cmath>
#include<algorithm>
#include "./Print.h"

void AlgPrint::drawline(size_t HowMuch)
{
	for(size_t i = 0; i < HowMuch; ++i)
		std::cout << "-";
	std::cout << "-\n";
}

template<typename T>
void AlgPrint::container(const std::vector<T>& container, ContainerType type, bool boxed, int width, int prec) 
{
	size_t size = 0;
	switch (type) 
	{
	case matr: size = sqrt(container.size()); break;
	case vect: size = container.size(); break;
	}

	if (boxed) drawline(size * (width + 1));
	switch (type) 
	{
	case matr:
		for (size_t i = 0; i < size; ++i)
		{			
			std::cout <<"| "; 
			for (size_t j = 0; j < size; ++j)
				std::cout << std::setprecision(prec) << std::setw(width) << container[i * size + j] << " ";
			std::cout << "|\n"; 
		}
		break;
	case vect:	
			std::cout << "| "; 
			for (size_t i = 0; i < size; ++i)
				std::cout << container[i] << " ";
			std::cout << "|\n"; 
		break;
	}
	if (boxed) drawline(size * (width + 1));
}

template<typename T>
void AlgPrint::value(const T& message) {
	std::cout << message << "\n";
}

template<typename T>
void AlgPrint::printsystem(const Matr<T>& matrix, const std::vector<T>& vec, int width, int prec) 
{
	size_t size = matrix.size();
	drawline(size * (width + 1));
	for (size_t i = 0; i < size; ++i)
		{			
			std::cout << "| "; 
			for (size_t j = 0; j < size; ++j)
				std::cout << std::setw(width) << std::setprecision(prec)<< matrix.atvalue(i, j) << " ";
			std::cout << "| " << vec[i] << "\n";
		}
	drawline(size * (width + 1));
}

template<typename T>
std::ostream& operator <<(std::ostream& str, const Matr<T>& matrix)
{
	size_t size = matrix.size();
	for (size_t i = 0; i < size; ++i)
	{			
		str <<"| "; 
		for (size_t j = 0; j < size; ++j)
			str << std::setprecision(4) << std::setw(10) << matrix.atvalue(i , j) << " ";
		str << "|\n"; 
	}
	return str;
}

template<typename T>
std::ostream& operator <<(std::ostream& str, const std::vector<T>& vec)
{
	size_t size = vec.size();
	str << "| ";
	for (size_t i = 0; i < size; ++i)
		{			
			str << std::setprecision(4) << std::setw(10) << vec[i]<< " ";
		}
		str << "|\n"; 

	return str;
}

template<typename T>
std::ostream& operator <<(std::ostream& str, const EigenPair<T>& eigen)
{
	str << eigen.value << "\n" << eigen.vector;
	return str;
}

template<typename T>
std::ostream& operator <<(std::ostream& str, const std::vector<EigenPair<T>>& pairs)
{	
	for (auto& pair: pairs) { str << std::setprecision(4) << std::setw(6) << pair.value << " <--> " << pair.vector; }
	return str;
}
#endif