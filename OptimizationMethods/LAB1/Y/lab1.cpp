#include <iostream>
#include <fstream>
#include <cmath>
#include "../A/GoldenSectionSearch.cpp"


double f(double x)
{
	double R1 = sin((sqrt(13)*pow(x,3) - 9*x - 5 - sqrt(17))/10);
	double R2 = tan((pow(x,2)+x+pow(2, 1/3))/(3*x-5));
	return -R1 - R2 - 0.6;
}

double g(double x)
{
	double R1 = sin((-2*pow(x,2) - x*sqrt(10) + 1)/4);
	double sqrt7_ = sqrt(7);
	double sqrt5_ = sqrt(5);
	double R2 = pow((pow(x,2)+(sqrt7_ + sqrt(2))*x + 1 - sqrt5_)/(sqrt7_*x - sqrt5_), log(2));
	return -R1 - R2 +1.2;
}

double dichotomy(double delta, double epsilon, double a0, double b0, const UnimodalFunction& func)
{
	std::ofstream File;
	File.open("../Results/dichotomy.dat");
	size_t k = 0;
	size_t valuesCount = 0;
	double Lk = b0 - a0;
	double ak = a0, bk = b0, xk1, xk2;
	while(Lk >= epsilon)
	{
		File << Lk << std::endl;
		k++;
		//std::cout << "№" << k << ": [" << ak << ", " << bk << "]" << std::endl;
		xk1 = (bk + ak) / 2 - delta;
		xk2 = (bk + ak) / 2 + delta;
		valuesCount += 2;
		if (func(xk1) >= func(xk2))
		{
			ak = xk1;
		}
		else
		{
			bk = xk2;
		}
		Lk = bk - ak;
		//std::cout << "Lk = "<< Lk << std::endl;
	    //std::cout <<  "    [" << xk1 << ", " << xk2 << "]" << std::endl;
	    //std::cout<< Lk << "    " << epsilon << std::endl;
	}
	File << Lk << std::endl;
	std::cout << "Количество итераций: " << k << std::endl;
	std::cout << "Количество вычисленных значений: " << valuesCount << std::endl;
	File.close();
	return (bk + ak) / 2;
}

int main(int argc, char** argv)
{
	const auto h = f;

	double e = 1e-15;
	double x = dichotomy(e/10, e, -1, 0, h);
	double y = h(x);
	std::cout << "x⋆ = " << x << std::endl
			  << "y(x⋆) = " << y << std::endl;
	std::cout << "------------------------" << std::endl;
    GoldenSectionSearch(-1, 0, h).run(e);
    //std::cout << abs(0.5) << " " << 0.5 << std::endl; abs работает не так , как надо
}
