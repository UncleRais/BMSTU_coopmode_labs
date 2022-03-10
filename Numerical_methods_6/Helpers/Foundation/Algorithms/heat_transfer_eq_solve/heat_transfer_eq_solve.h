#ifndef HEAT_TRANSFER_EQ_SOLVE_H
#define HEAT_TRANSFER_EQ_SOLVE_H

#include "../../../../../Numerical_methods_5/Helpers/Foundation/Foundation.cpp"
#include "../../../../../Numerical_methods_6/Helpers/Foundation/Foundation.cpp"

typedef std::vector<std::vector<double>> Portrait;

class heat_transfer_eq_solve {
public:

template < typename T >
static Portrait NDsolve(const std::vector<funtwo>& rightpart, const std::vector<T>& cond,
 MethodType name, T h = 0.1, T epsilon = 1e-3);

template < typename T >
static void save(std::vector<std::vector<T>>& portrait, std::string path);

template < typename T >
static void save(std::vector<T>& portrait, std::string path);

};

#endif