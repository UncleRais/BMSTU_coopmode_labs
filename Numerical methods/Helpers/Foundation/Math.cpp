#ifndef Math
#define Math

template < typename T >
T absolute(const T value) {
	return value < 0 ? -value : value;
}

template<typename T>
T norm(const std::vector<T>& vector) {
	T result = 0;
	for (auto& x: vector) { 
		result += pow(x, 2);
	}
	return sqrt(result);
}

#endif