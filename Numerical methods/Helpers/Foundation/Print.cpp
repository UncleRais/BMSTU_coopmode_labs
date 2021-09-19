#ifndef Print
#define Print

#include<iostream>
#include<fstream>
#include<iterator>
#include<vector>
#include<iomanip>
#include<cmath>
#include<algorithm>
#include "./Matrix.cpp"

enum ContainerType {
	matr,
	vect,
};

void drawline(size_t HowMuch = 10)
{
	for(size_t i = 0; i < HowMuch; ++i)
				std::cout << "-";
			std::cout << "-\n";
}

template < typename T >
void print(const std::vector<T>& container, ContainerType type, bool boxed = false, int width = 7, int prec = 4) 
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
//FUNCTIONS--------------------------------------------------------------------------------
template<typename T>
void print(const T& message) {
	std::cout << message << "\n";
}

#endif