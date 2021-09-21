#ifndef Foundation
#define Foundation

#include <iostream>
#include "./Print/Print.cpp"
#include "./Algorithms/Algorithms.cpp"

template<typename T>
void save(
	const Matrix<T>& matrix, 
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