#ifndef ODE_CPP
#define ODE_CPP
#include "./ODE.h"

template < typename T >
void ODE::NDsolve(std::vector<funtwo>& rightpart, std::vector<T>& cond, MethodType name, T epsilon)
{
	switch (name)
	{
	case ExplicitEuler_:
		ExplicitEuler(rightpart, cond, epsilon);
		std::cout << "ExplicitEuler finised.";
		break;
	case ImplicitEuler_:
		std::cout << "ImplicitEuler finised.";
		break;
	case Symmetrical_:
		std::cout << "Symmetrical finised.";
		break;
	case Runge_Kutta_4_:
		std::cout << "Runge_Kutta_4 finised.";
		break;
	case Runge_Kutta_2_:
		Runge_Kutta_2(rightpart, cond, epsilon);
		std::cout << "Runge_Kutta_2 finised.";
		break;
	case Adams_Bashforth_:
		std::cout << "Adams_Bashforth finised.";
		break;
	default:
		std::cout << "Unknown method! Please, check MethodType.";
		break;
	}
}

template < typename T >
void ODE::ExplicitEuler(std::vector<funtwo>& rightpart, std::vector<T>& cond, T epsilon)
{
	std::ofstream file;
	file.open("./output/ExplicitEuler.dat");

	int numberofpoints = 1000, systemsize = rightpart.size(); 
	T h = (cond[1] - cond[0])/(numberofpoints - 1);
	std::vector<std::vector<T>> x(systemsize);
	for(int i = 0; i < systemsize; ++i)
	{
		x[i].reserve(numberofpoints);
		x[i].push_back(cond[i + 2]);
	}

	std::vector<T> xT;
	xT.reserve(systemsize);
	for(int i = 0; i < numberofpoints - 2; ++i)
	{
		for(int k = 0; k < systemsize; ++k) {xT[k]=x[k][i];};
		for(int j = 0; j < systemsize; ++j)
		{
			x[j].push_back(xT[j] + h * rightpart[j](xT));
			file << xT[j] << ' ';
		}
		file << std::endl;
	}
	file << x[0][numberofpoints - 3] << ' ' << x[1][numberofpoints - 3] << std::endl;

	file.close();
}

template < typename T >
void ODE::ImplicitEuler(std::vector<funtwo>& rightpart, std::vector<T>& cond, T epsilon)
{
	std::ofstream file;
	file.open("./output/ImplicitEuler.dat");

	int numberofpoints = 1000, systemsize = rightpart.size(); 
	T h = (cond[1] - cond[0])/(numberofpoints - 1);
	std::vector<std::vector<T>> x(systemsize);
	for(int i = 0; i < systemsize; ++i)
	{
		x[i].reserve(numberofpoints);
		x[i].push_back(cond[i + 2]);
	}

	/*решение неявным методом Эйлера*/

	file.close();
}

template < typename T >
void ODE::Runge_Kutta_2(std::vector<funtwo>& rightpart, std::vector<T>& cond, T epsilon)
{
	std::ofstream file;
	file.open("./output/Runge_Kutta_2.dat");

	int numberofpoints = 1000, systemsize = rightpart.size(); 
	T h = (cond[1] - cond[0])/(numberofpoints - 1);
	std::vector<std::vector<T>> x(systemsize);
	for(int i = 0; i < systemsize; ++i)
	{
		x[i].reserve(numberofpoints);
		x[i].push_back(cond[i + 2]);
	}

	std::vector<T> xT(systemsize), K(systemsize), help(systemsize);
	for(int i = 0; i < numberofpoints - 2; ++i)
	{
		for(int k = 0; k < systemsize; ++k) {xT[k] = x[k][i]; };

		for(int k = 0; k < systemsize; ++k) {K[k] = rightpart[k](xT);};

		for(int j = 0; j < systemsize; ++j)
		{
			help = xT + h/2 * K;
			x[j].push_back(xT[j] + h / 2 * (K[j] + rightpart[j](help)));
			file << xT[j] << ' ';
		}
		file << std::endl;
	}
	file << x[0][numberofpoints - 3] << ' ' << x[1][numberofpoints - 3] << std::endl;


	file.close();
}

#endif