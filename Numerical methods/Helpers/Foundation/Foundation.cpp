#ifndef Foundation
#define Foundation

#include <iostream>
#include "./Print/Print.cpp"
#include "./Algorithms/Algorithms.cpp"

enum FileError {
	settingsNotFound,
	matrixNotFound,
	vectorNotFound,
};

template<typename T>
void init(Matr<T>& matrix, std::vector<T>& vec, const char * settings)
{
try { 
	size_t systemSize;
		std::ifstream iFile;
		iFile.open(settings);
		if (!iFile.is_open() ) { 
			throw settingsNotFound;
		}

		iFile >> systemSize;
		std::string matrixName, vectorName, outputName;
		iFile >> matrixName;
		iFile >> vectorName;
		iFile >> outputName;
		iFile.close();

		iFile.open(matrixName);
		if (!iFile.is_open()) {
			throw matrixNotFound;
		}

		std::ifstream vectorFile;
		vectorFile.open(vectorName);
		if (!iFile.is_open()) {
			throw vectorNotFound;
		}

		matrix.setsize(systemSize);
		matrix.reserve(systemSize);
		vec.reserve(systemSize);
		double value;
		for (size_t i = 0; i < systemSize; ++i)
		{
			matrix.push_back_rows(i); matrix.push_back_cols(i);
			for (size_t j = 0; j < systemSize; ++j)
			{
				iFile >> value;
				matrix.push_back(value);
			}
		vectorFile >> value;
		vec.push_back(value);
		}
		iFile.close();
		vectorFile.close();
	} catch (FileError error) {
		std::string errorDescription;
		switch (error) {
			case settingsNotFound:
				errorDescription = "Settings not found\n";
				break;
			case matrixNotFound:
				errorDescription = "Matrix not found\n";
				break;
			case vectorNotFound:
				errorDescription = "Vector not found\n";
			default:
			break;
		}
		std::cerr << errorDescription << std::endl;
		exit(5);
	}
}


template<typename T>
void save(
	const Matr<T>& matrix, 
	const std::string& directory, 
	const std::string& name,
	const std::string& extension = "dat"
	) {
	const std::string path = "../" + directory + "/" + name + "." + extension;
	std::ofstream file;
	file.open(path);
	if (!file.is_open()) {
		const std::string oopsMessage = "Oops. Could not save file at: ";
		const std::string error = ". Directory location not found";
		const std::string message = oopsMessage + path + error;
		AlgPrint::value(message);
	}
	for (size_t i = 0; i < matrix.size(); ++i) {
		for (size_t j = 0; j < matrix.size(); ++j) {
			file << matrix.atvalue(i, j) << " ";
		}
		file << "\n";
	}
	file.close();
}

template<typename T>
void save(
	const std::vector<T>& vector, 
	const std::string& directory, 
	const std::string& name,
	const std::string& extension = "dat"
	) {
	const std::string path = "../" + directory + "/" + name + "." + extension;
	std::ofstream file;
	file.open(path);
	if (!file.is_open()) {
		const std::string oopsMessage = "Oops. Could not save file at: ";
		const std::string error = ". Directory location not found";
		const std::string message = oopsMessage + path + error;
		AlgPrint::value(message);
	}
	for (size_t i = 0; i < vector.size(); ++i) {
		file << vector[i] << " ";
	}
	file.close();
}

#endif