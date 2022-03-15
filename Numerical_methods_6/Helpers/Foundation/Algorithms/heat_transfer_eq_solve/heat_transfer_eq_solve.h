#ifndef HEAT_TRANSFER_EQ_SOLVE_H
#define HEAT_TRANSFER_EQ_SOLVE_H

//#include "../../../../../Numerical_methods_5/Helpers/Foundation/Foundation.cpp"
#include "../../../../../Numerical_methods_6/Helpers/Foundation/Foundation.cpp"

template < typename T > 
class heat_transfer_eq_solve {

typedef double(*func1d)(T);
typedef double(*func2d)(T, T);
typedef std::vector<std::vector<T>> Portrait; 

private:
/*Переменные уравнения теплопроводности и граничных условий*/ 
T c,   //Удельная теплоемкость   
  rho, //Плотность массы
  L,   //Длина стержня
  T0,  //Начальная температура стержня
  Q, t0,   //Параметры для потока на границе
  alpha, beta, gamma, k1, k2, x1, x2; //Параметры для теплопроводности

func1d P; // Поток на границе
func2d K; // Теплороводность

public:

heat_transfer_eq_solve(const std::vector<T> cond, int flow, int conductivity)
{
    c = cond[0]; rho = cond[1]; alpha = cond[2]; 
    beta = cond[3]; gamma = cond[4]; T0 = cond[5];
    k1 = cond[6]; k2 = cond[7]; x1 = cond[8]; x2 = cond[9];

    //Required
    L = static_cast<T>(1);  
    Q = static_cast<T>(10);  
    t0 = static_cast<T>(0.5); 

    switch(flow)
    {
        case 1:
        P = (double t) -> double 
        {if( 0 <= t && t < t0){ return (Q); } else { return(0); } };
        break;
        case 2:
        P = [](double t) -> double 
        {if( 0 <= t && t < t0){ return (2*Q*t); } else { return(0); } };
        break;
        case 3:
        P = [](double t) -> double 
        {if( 0 <= t && t < t0){ return (2*Q*(t0 - t)); } else { return(0); } };
        break;
        case 4:
        P = [](double t) -> double 
        {if( 0 <= t && t <= 0.5*t0){ return (2*Q*t); } else 
         if( 0.5*t0 < t && t < t0){ return (2*Q*(t0 - t)); } else { return(0); } };
        break;
    }

     switch(conductivity)
    {
        case 1:
        K = [](double temp, double x) -> double 
         {if( 0 <= x && x <= x1){ return (k1); } else 
          if( x1 < x && x < x2){ return (k1 * (x - x2)/(x1 - x2) + k2 * (x - x1)/(x2 - x1)); } else 
          { return(k2); } };
        break;
        case 2:
         K = [](double temp, double x) -> double 
         {if( 0 <= x && x <= x1){ return (k1); } else 
          if( x1 < x && x < x2){ return (k1 * (x - x2)/(x1 - x2) + k2 * (x - x1)/(x2 - x1)); } else 
          { return(k2); } };
        break;
    }
};

Portrait NDsolve(T epsilon = 1e-3);

void parameters_info();

void save(std::vector<std::vector<T>>& portrait, std::string path);

void save(std::vector<T>& portrait, std::string path);

};

#endif