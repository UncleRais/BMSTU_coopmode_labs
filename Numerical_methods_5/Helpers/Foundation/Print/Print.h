#ifndef Print_H
#define Print_H

#include <iostream>
#include "../Matrix/Matr.cpp"
#include "../Algorithms/Algorithms.cpp"

struct AlgPrint {
	enum ContainerType {
		matr,
		vect,
	};

	static void drawline(size_t HowMuch = 10);

	template<typename T>
	static void container(const std::vector<T>& container, ContainerType type, bool boxed = false, int width = 7, int prec = 8);

	template<typename T>
	static void value(const T& message);

	template<typename T>
	static void printsystem(const Matr<T>& matrix, const std::vector<T>& vec, int width = 10, int prec = 4);

};

#endif