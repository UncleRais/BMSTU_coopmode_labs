#ifndef WAVE_EQ_SOLVE_H
#define WAVE_EQ_SOLVE_H

//#include "../../../../../Numerical_methods_5/Helpers/Foundation/Foundation.cpp"
#include "../../../../../Numerical_methods_6/Helpers/Foundation/Foundation.cpp"

#include <algorithm>

template < typename T > 
class wave_eq_solve
{
public:
typedef std::function <T (T)> func1d;
typedef std::function <T (T , T)> func2d; 

func1d InitVelocity;  //Начальная скорость всех точек струны
func1d InitShape;     //Начальная форма струны
func1d InitShapeXX;   //Вторая производная начальной формы струны
func1d LeftBoundary;  //Закон движения левого конца струны
func1d RightBoundary; //Закон движения правого конца струны
T a, 			//Фазовая скорость
  L, 			//Длина струны
  finish_time;  //Время колебаний

public:

wave_eq_solve(func1d f, func1d fxx, func1d g, func1d phi, func1d xi, T L_, T time, T a_)
{
    InitShape = f; 
    InitShapeXX = fxx;
    InitVelocity = g;
    LeftBoundary = phi;
    RightBoundary = xi; 
    L = L_;
    finish_time = time;
    a = a_;
};

void solve(const std::string path, size_t timestamps, size_t sections, size_t NumberOfResults);

};

#endif