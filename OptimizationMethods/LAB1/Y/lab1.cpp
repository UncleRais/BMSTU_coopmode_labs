#include <iostream>
#include <fstream>


double f(double x)
{
	return x * x * x;
}

double FindMin(double delta, double epsilon, double a0, double b0)
{
	std::ofstream File;
	File.open("../Results/dichotomy.dat");
	size_t k = 0;
	size_t valuesCount = 0;
	double Lk = b0 - a0;
	double ak = a0, bk = b0, xk1, xk2;
	while(abs(Lk) >= epsilon)
	{
		File << Lk << std::endl;
		k++;
		// std::cout << "№" << k << ": [" << ak << ", " << bk << "]" << std::endl;
		xk1 = (bk + ak) / 2 - delta;
		xk2 = (bk + ak) / 2 + delta;
		valuesCount += 2;
		if (f(xk1) >= f(xk2))
			ak = xk1;
		else
			bk = xk2;
		Lk = bk - ak;
		// std::cout <<  "    [" << xk1 << ", " << xk2 << "]" << std::endl;
	}
	File << Lk << std::endl;
	std::cout << "Количество итераций: " << k << std::endl;
	std::cout << "Количество вычисленных значений: " << valuesCount << std::endl;
	File.close();
	return (bk + ak) / 2;
}

int main(int argc, char** argv)
{
	double e = 10e-5;
	double x = FindMin(e/10, e, -1, 1);
	double y = f(x);
	std::cout << "x⋆ = " << x << std::endl
			  << "y(x⋆) = " << y << std::endl;
}
