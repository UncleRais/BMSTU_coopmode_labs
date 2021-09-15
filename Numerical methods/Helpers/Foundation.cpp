template<
	typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
> 
T positive(const T value) {
	return value < 0 ? -value : value;
}