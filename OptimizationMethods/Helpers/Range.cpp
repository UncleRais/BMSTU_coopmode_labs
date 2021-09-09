#include <iostream>

template<
	typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
> 
struct Range {
private:
	T start, end;

public:
	const T getStart() const { return start; }
	const T getEnd() const { return end; }
	const T getLength() const { return end - start ; }
	const T getMiddleValue() const { return (start + end) / 2; }

	void setStart(T newValue) { 
		start = newValue;
	}
	void setEnd(T newValue) { 
		end = newValue; 
	}

	Range(T start = 0, T end = 0) {
		this->start = start; this->end = end;
	}
};