#ifndef Print_H
#define Print_H

#include <iostream>
#include "../Matrix/Matrix.cpp"
#include "../Algorithms/Algorithms.cpp"

struct AlgPrint {
	enum ContainerType {
		matr,
		vect,
	};

	static void drawline(size_t HowMuch = 10);

	template<typename T>
	static void container(const std::vector<T>& container, ContainerType type, bool boxed = false, int width = 7, int prec = 4);

	template<typename T>
	static void value(const T& message);
};

#endif