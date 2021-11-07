#ifndef BANISH_CPP
#define BANISH_CPP

#include "./Banish.h"
#include <cmath>
#include "../../Foundation.cpp"
#include "../../Math.cpp"

template < typename T >
std::vector<T> Banish::solve(std::vector<T> vecA, std::vector<T> vecB, std::vector<T> vecC, std::vector<T> vecD)
{
	std::vector<T> result(vecD.size());
	std::vector<T> alpha(vecD.size() - 1);
	std::vector<T> beta(vecD.size() - 1);

	alpha[0] = -(vecC[0]/vecB[0]);
	beta[0] = (vecD[0]/vecB[0]);

	T value;

	for( size_t i = 1; i < vecD.size() - 1; ++i)
	{
		value = vecB[i] + vecA[i - 1] * alpha[i - 1];
		alpha[i] = -vecC[i] / value;
		beta[i] = (vecD[i] - vecA[i - 1] * beta[i - 1]) / value;
	}

	size_t n = vecD.size() - 1;
	result[n] = (vecD[n] - vecA[n - 1] * beta[n - 1])/(vecB[n] + alpha[n - 1] * vecA[n - 1]);

	for( size_t i = n - 1; i >= 1; --i)
	{
		result[i] = alpha[i] * result[i + 1] + beta[i];
	}
	result[0] = alpha[0] * result[1] + beta[0];
	return result;
}

#endif