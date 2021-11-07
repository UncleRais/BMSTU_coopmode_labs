#ifndef BANISH
#define BANISH

#include "../Main/Algorithm.h"

class Banish: public MatrixAlgorithm {

private:

public:
	template < typename T >
	static std::vector<T> solve(std::vector<T> vecA, std::vector<T> vecB, std::vector<T> vecC, std::vector<T> vecD);

}

#endif