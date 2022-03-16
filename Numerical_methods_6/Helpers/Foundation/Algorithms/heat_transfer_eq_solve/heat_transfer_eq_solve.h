#ifndef HEAT_TRANSFER_EQ_SOLVE_H
#define HEAT_TRANSFER_EQ_SOLVE_H

//#include "../../../../../Numerical_methods_5/Helpers/Foundation/Foundation.cpp"
#include "../../../../../Numerical_methods_6/Helpers/Foundation/Foundation.cpp"

template<class T>
using Portrait = std::vector<std::vector<T>>;


template < typename T > 
class heat_transfer_eq_solve 
{
public:
typedef std::function <T (T)> func1d;
typedef std::function <T (T , T)> func2d; 

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

heat_transfer_eq_solve(const std::vector<T>& cond, int flow, int conductivity)
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
        P = [this](T t) -> T 
        {if( 0 <= t && t < t0){ return (Q); } else { return(0); } };
        break;
        case 2:
        P = [this](T t) -> T 
        {if( 0 <= t && t < t0){ return (2*Q*t); } else { return(0); } };
        break;
        case 3:
        P = [this](T t) -> T 
        {if( 0 <= t && t < t0){ return (2*Q*(t0 - t)); } else { return(0); } };
        break;
        case 4:
        P = [this](T t) -> T 
        {if( 0 <= t && t <= 0.5*t0){ return (2*Q*t); } else 
         if( 0.5*t0 < t && t < t0){ return (2*Q*(t0 - t)); } else { return(0); } };
        break;
    }

     switch(conductivity)
    {
        case 1: //K зависит только от координаты
        K = [this](T temp, T x) -> T 
         {if( 0 <= x && x <= x1){ return (k1); } else 
          if( x1 < x && x < x2){ return (k1 * (x - x2)/(x1 - x2) + k2 * (x - x1)/(x2 - x1)); } else 
          { return(k2); } };
        break;
        case 2: //K зависит только от температуры
         K = [this](T temp, T x) -> T 
         { return (alpha + beta * pow(temp, gamma)); };
        break;
    }
};

Portrait<T> NDsolve(int left, int right, int NumTime, int NumX, T LatterTime, T sigma = 0);

void parameters_info() const;

static void save(const std::vector<std::vector<T>>& portrait, const std::string path);

static void save(const std::vector<T>& portrait, const std::string path);

};

#endif