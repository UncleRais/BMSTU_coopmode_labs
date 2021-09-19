#ifndef Foundation
#define Foundation

#include <iostream>
#include <string>
#include "./Print.cpp"
#include "./Algorithms/Algorithms.cpp"
#include "./Matrix.cpp"

//FUNCTIONS--------------------------------------------------------------------------------
// template < typename T >
// T absolute(const T value) {
// 	return value < 0 ? -value : value;
// }

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
		print(message);
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
		print(message);
	}
	for (size_t i = 0; i < vector.size(); ++i) {
		file << vector[i] << " ";
	}
	file.close();
}

#endif