#ifndef SYS20
#define SYS20
#include <cmath>
/*Модель Лотки-Вольтерры динамики системы «хищник-жертва»*/

double r[2] = {0.4, 0.1};
double b[2][2] = {0.05, 0.1, 0.08, 0.003}; 
double cond[2][2] = {0.0, 1.0, 0.0, 4.0};

double f1 (double x1, double x2)
{
	return(r[0] * x1 - b[0][0] * pow(x1,2) - b[0][1] * x1 * x2);
}

double f2 (double x1, double x2)
{
	return(-r[1] * x2 - b[1][1] * pow(x2,2) + b[1][0] * x1 * x2);
}

#endif