#ifndef POISSON_EQ_SOLVE_H
#define POISSON_EQ_SOLVE_H

//#include "../../../../../Numerical_methods_5/Helpers/Foundation/Foundation.cpp"
#include "../../../../../Numerical_methods_6/Helpers/Foundation/Foundation.cpp"

//#include <algorithm>

template < typename T > 
class poisson_eq_solve 
{
public:
typedef std::function <T (T)> func1d;
typedef std::function <T (T , T)> func2d; 

std::vector<func1d> G; //Вектор граничных условий
std::vector<int> IndG;//Вектор индикаторов ГУ
func2d f; //Функция правой части
std::array<T,2> L; //Границы области

public:

poisson_eq_solve (func2d f_, std::vector<func1d> G_, std::vector<int> IndG_, T M[2])
{
    f = f_;
    G = G_;
    IndG = IndG_;
    L[0] = M[0];
    L[1] = M[1];

};

void solve(const std::string path, const std::array<size_t, 3>& N, T finish);

};

#endif