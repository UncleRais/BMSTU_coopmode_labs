#ifndef QR_CPP
#define QR_CPP

#include "./QR.h"

template < typename T >
Matrix<T> QR::factor(Matrix<T> rMatrix) {
	for (size_t k = 1; k < rMatrix.size(); ++k) {
		for (size_t i = 1; i < rMatrix.size(); ++i) {
			for (size_t j = 1; j < rMatrix.size(); ++j) {
				
			}
		}
	}

	return {};
}

#endif