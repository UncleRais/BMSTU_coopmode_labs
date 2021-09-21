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

#endif