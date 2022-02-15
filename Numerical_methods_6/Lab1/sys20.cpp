#ifndef SYS20
#define SYS20
#include <cmath>
/*Модель Лотки-Вольтерры динамики системы «хищник-жертва»*/

double r[2] = {0.4, 0.1}; /*{r1, r2}*/
double b[2][2] = {0.05, 0.1, 0.08, 0.003}; /*{b11, b12, b21, b22}*/
std::vector<double> cond = {0.0, 160.0, 1.0, 4.0}; /*{t0 , tn, x1(t0), x2(t0)}*/

double f1 (std::vector<double>& x)
{
	return(r[0] * x[0] - b[0][0] * pow(x[0],2) - b[0][1] * x[0] * x[1]);
}

double f2 (std::vector<double>& x)
{
	return(-r[1] * x[1] - b[1][1] * pow(x[1],2) + b[1][0] * x[0] * x[1]);
}

#endif