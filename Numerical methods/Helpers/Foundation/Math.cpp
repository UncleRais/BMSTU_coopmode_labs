#ifndef Math
#define Math

template<typename T>
T norm(const std::vector<T>& vector) {
	T result = 0;
	for (auto& x: vector) { 
		result += pow(x, 2);
	}
	return sqrt(result);
}

template<typename T>
void makeoutrage(std::vector<T>& vec, double sign)
{
	std::transform(std::begin(vec),std::end(vec),std::begin(vec),[sign](T x){return (x + sign * 0.01);});
}

template<typename T>
std::vector<T> operator -(const std::vector<T>& left, const std::vector<T>& right)
{
	std::vector<T> result;
	result.reserve(left.size());
	for (size_t i = 0; i < left.size(); ++i)
	{
		result.push_back(left[i] - right[i]);
	}
	return(result);
}

template<typename T>
std::vector<T> operator +(const std::vector<T>& left, const std::vector<T>& right)
{
	std::vector<T> result;
	result.reserve(left.size());
	for (size_t i = 0; i < left.size(); ++i)
	{
		result.push_back(left[i] + right[i]);
	}
	return(result);
}


#endif