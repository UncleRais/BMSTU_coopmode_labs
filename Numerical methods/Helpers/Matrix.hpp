#ifndef MATRIX
#define MATRIX

#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<cmath>

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
private:
	std::vector<T> matrix_ = {};
	std::vector<T> rightvalues_ = {};
	size_t systemSize;

public:
 	T& at(const size_t row, const size_t col) 
	{
		return matrix_[row * systemSize + col];
	}

	T atvalue(const size_t row, const size_t col) 
	{
		return matrix_[row * systemSize + col];
	}

	void print(int width = 7, int prec = 4) 
	{
		std::cout << "---------------------"<< std::endl;;
		for (size_t i = 0; i < systemSize; ++i)
			{			
				std::cout << "| "; 
				for (size_t j = 0; j < systemSize; ++j)
					std::cout << std::setw(width) << std::setprecision(prec)<< at(i, j) << " ";
				std::cout << "| " << rightvalues_[i] << std::endl;
			}
		std::cout << "---------------------"<< std::endl;;
	}

	void GaussMethod()
	{
		//Forward method progress START
		for(size_t k = 0; k < systemSize - 1; ++k)
		{
		    //THERE WILL BE: checking elem a[k][k] != 0 OR finding main elem 
			for(size_t row = k + 1; row < systemSize; ++row)
			{
				T value = atvalue(row , k);
				for(size_t col = k; col < systemSize; ++col)
				{
					at(row,col) -= at(k, col) * value / at(k , k); 
				}
				rightvalues_[row] -= rightvalues_[k] * value / at(k , k); 
			}
		}
		//Forward method progress FINISH
		print(10,4);
		//Backward method progress START
		std::vector<T> solution = {};
		solution.reserve(systemSize);
		for (size_t row = systemSize - 1; row >= 0; --row)
		{
			T x = 0.0;
			x += rightvalues_[row];			
			for(size_t col = 0; col < solution.size() ; ++col )
			{
				x -= at(row,col) * solution[systemSize - col];
			} 
			x /= at(row,row);
			solution.push_back(x);
		}			
		//Backward method progress FINISH
		print(10,4);
	}

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
			rightvalues_.reserve(systemSize);
			double value;
			for (size_t i = 0; i < systemSize; ++i)
			{
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
					errorDescription = "Settings not found";
					break;
				case matrixNotFound:
					errorDescription = "Matrix not found";
					break;
				case vectorNotFound:
					errorDescription = "Vector not found";
			}
			std::cerr << errorDescription << std::endl;
			exit(-1488);
		}
	};

	~Matrix(){};
};

#endif