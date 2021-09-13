#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>

template<
	typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
> 
class Matrix {
private:
	std::vector< std::vector<T>> matrix_ = {};
	std::vector<T> rightvalues_ = {};
	size_t systemSize_;
public:
	Matrix(const char * fileName)
	{
		std::ifstream ifile;
		ifile.open(fileName);
		if (!ifile.is_open() ) { //need exception!!!
			std::cerr <<"Error: file with settings is not open!\n" ;
		}
		//Taking info from settings.dat
		ifile >> systemSize_;
		std::string matrixName, vectorName, outputName;
		ifile >> matrixName;
		ifile >> vectorName;
		ifile >> outputName;
		std::cout << "matrixName("<< matrixName.length() <<"):" << matrixName << std::endl;
		std::cout << "vectorName("<< vectorName.length() <<"):" << vectorName << std::endl;
		std::cout << "outputName("<< outputName.length() <<"):" << outputName << std::endl;
		ifile.close();

		//Collecting info about linear system
		ifile.open(matrixName);
		std::vector <T> carrier = {};
		carrier.reserve(systemSize_); //reserve needfull capacity
		matrix_.reserve(systemSize_);
		rightvalues_.reserve(systemSize_);
		double value;
		for (size_t i = 0; i < systemSize_; ++i)
		{
			for (size_t j = 0; j < systemSize_; ++j)
			{
				ifile >> value;
				carrier.push_back(value);
			}
		matrix_.push_back(carrier);
		ifile >> value;
		rightvalues_.push_back(value);
		carrier.clear();
		}
		ifile.close();
	};

	~Matrix(){};

	void print(int width = 7) const
	{
	for (size_t i = 0; i < systemSize_; ++i)
		{			
			std::cout << "| "; 
			for (size_t j = 0; j < systemSize_; ++j)
				std::cout << std::setw(width) << matrix_[i][j] << " ";
			std::cout << "| " << rightvalues_[i] << std::endl;
		}
	}
};