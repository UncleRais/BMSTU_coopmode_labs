#include <iostream>
#include <vector>

template<
	typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
> 
class Matrix {
private:
	std::vector<T> values = {};
};