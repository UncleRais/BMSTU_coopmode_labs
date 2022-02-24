#ifndef ODE_CPP
#define ODE_CPP
#include "./ODE.h"

//MARK: Let's make a deal
// t – time iterator, current t is a timestamp
// i - node iterator, current t is a dimensional point

template < typename T >
void ODE::NDsolve(const std::vector<funtwo>& rightpart, const std::vector<T>& cond, MethodType name, T epsilon)
{
	int timestamps = 1000, systemsize = rightpart.size(); 
	T h = (cond[1] - cond[0])/(timestamps - 1);
	std::vector<std::vector<T>> x(systemsize);
	for(int i = 0; i < systemsize; ++i)
	{
		x[i].reserve(timestamps);
		x[i].push_back(cond[i + 2]);
	}
	Portrait portrait;
	switch (name)
	{
	case ExplicitEuler_:
		portrait = ExplicitEuler(rightpart, cond, timestamps, systemsize, h, x, epsilon);
		save(portrait, "./output/ExplicitEuler.dat");
		std::cout << "ExplicitEuler finised.";
		break;
	case ImplicitEuler_:
		portrait = ImplicitEuler(rightpart, cond, timestamps, systemsize, h, x, epsilon);
		save(portrait, "./output/ImplicitEuler.dat");
		std::cout << "ImplicitEuler finised.";
		break;
	case Symmetrical_:
		portrait = Symmetrical(rightpart, cond, timestamps, systemsize, h, x, epsilon);
		save(portrait, "./output/Symmetrical.dat");
		std::cout << "Symmetrical finised.";
		break;
	case Runge_Kutta_2_:
		Runge_Kutta_2(rightpart, cond, timestamps, systemsize, h, x, epsilon);
		std::cout << "Runge_Kutta_2 finised.";
		break;
	case Runge_Kutta_4_:
		portrait = Runge_Kutta_4(rightpart, cond, timestamps, systemsize, h, x, epsilon);
		save(portrait, "./output/Runge_Kutta_4.dat");
		std::cout << "Runge_Kutta_4 finised.";
		break;
	case Runge_Kutta_4_adaptive_:
		portrait = Runge_Kutta_4_adaptive(rightpart, cond, timestamps, systemsize, h, x, epsilon);
		save(portrait, "./output/Runge_Kutta_4_____.dat");
		std::cout << "Runge_Kutta_4 finised.";
		break;
	case Adams_Bashforth_:
		Adams_Bashforth(rightpart, cond, timestamps, systemsize, h, x, epsilon);
		std::cout << "Adams_Bashforth finised.";
		break;
	case Forecast_correction_:
		Forecast_correction(rightpart, cond, timestamps, systemsize, h, x, epsilon);
		std::cout << "Forecast_correction finised.";
		break;
	default:
		std::cout << "Unknown method! Please, check MethodType.";
		break;
	}
}

template < typename T >
Portrait ODE::ExplicitEuler(const std::vector<funtwo>& rightpart, 
						const std::vector<T>& cond, 
						int timestamps,
						int systemsize,
						T h,
						std::vector<std::vector<T>>& x, 
						T epsilon)
{
	std::vector<T> xT;
	xT.reserve(systemsize);
	for(int t = 0; t < timestamps - 2; ++t)
	{
		for(int i = 0; i < systemsize; ++i) {xT[i]=x[i][t];};
		for(int j = 0; j < systemsize; ++j)
		{
			x[j].push_back(xT[j] + h * rightpart[j](xT));
		}
	}

	return x;
	// for (int i = 0; i < systemsize; ++i ) file << x[i][timestamps - 3] << ' ';
}

template < typename T >
Portrait ODE::ImplicitEuler(const std::vector<funtwo>& rightpart, 
						const std::vector<T>& cond, 
						int timestamps,
						int systemsize,
						T h,
						std::vector<std::vector<T>>& x, 
						T epsilon)
{
	std::vector<T> xT;
	xT.reserve(systemsize);
	std::vector<vFunc> shifted;
	for (int i = 0; i < systemsize; ++i)
	{
		auto f = [&rightpart, &xT, i, h](const Point& x) -> double 
		{
			auto icantgoalone = x;
			return double(x[i] - xT[i] - h*rightpart[i](icantgoalone));
		};
		shifted.push_back(f);
	}
	for(int t = 0; t < timestamps - 2; ++t)
	{ 
		for (int i = 0; i < systemsize; ++i) { xT[i] = x[i][t]; }
		Point next = NonLinearSolve::system_newton(shifted, {}, 30, {0, 0});
		for (int i = 0; i < systemsize; ++i) 
		{ 
			x[i].push_back(next[i]);
		}
	}

	return x;
	// for (int i = 0; i < systemsize; ++i ) file << x[i][timestamps - 3] << ' ';
}

template < typename T >
Portrait ODE::Symmetrical(const std::vector<funtwo>& rightpart, 
					  const std::vector<T>& cond, 
					  int timestamps,
					  int systemsize,
				      T h,
					  std::vector<std::vector<T>>& x, 
					  T epsilon)
{
	std::vector<T> xT;
	xT.reserve(systemsize);
	std::vector<vFunc> shifted;
	for (int i = 0; i < systemsize; ++i)
	{
		auto f = [&rightpart, &xT, i, h](const Point& x) -> double 
		{
			auto icantgoalone = x;
			return double(x[i] - xT[i] - h/2*(rightpart[i](icantgoalone) + rightpart[i](xT)));
		};
		shifted.push_back(f);
	}
	for(int t = 0; t < timestamps - 2; ++t)
	{ 
		for (int i = 0; i < systemsize; ++i) { xT[i] = x[i][t]; }
		Point next = NonLinearSolve::system_newton(shifted, {}, 30, {-5, 5});
		for (int i = 0; i < systemsize; ++i) 
		{ 
			x[i].push_back(next[i]);
		}
	}

	return x;
	// for (int i = 0; i < systemsize; ++i ) file << x[i][timestamps - 3] << ' ';
}

template < typename T >
void ODE::Runge_Kutta_2(const std::vector<funtwo>& rightpart, 
						const std::vector<T>& cond, 
						int timestamps,
						int systemsize,
						T h,
						std::vector<std::vector<T>>& x, 
						T epsilon)
{
	std::ofstream file;
	file.open("./output/Runge_Kutta_2.dat");

	std::vector<T> xT(systemsize), K(systemsize), help(systemsize);
	for(int i = 0; i < timestamps - 2; ++i)
	{
		for(int k = 0; k < systemsize; ++k) {xT[k] = x[k][i]; };

		for(int k = 0; k < systemsize; ++k) {K[k] = rightpart[k](xT);};

		for(int j = 0; j < systemsize; ++j)
		{
			help = xT + h/2 * K;
			x[j].push_back(xT[j] + h * rightpart[j](help));
			file << xT[j] << ' ';
		}
		file << std::endl;
	}
	for (int i = 0; i < systemsize; ++i ) file << x[i][timestamps - 3] << ' ';
	file << std::endl;


	file.close();
}

template < typename T >
Portrait ODE::Runge_Kutta_4(const std::vector<funtwo>& rightpart, 
							const std::vector<T>& cond, 
							int timestamps,
							int systemsize,
							T h,
							std::vector<std::vector<T>>& x, 
							T epsilon)
{
	std::vector<T> xT(systemsize), help(systemsize);
	std::vector<std::vector<T>> K(4);
	for (int i = 0; i < 4; ++i) {K[i] = help;};
	for(int i = 0; i < timestamps - 2; ++i)
	{
		for(int k = 0; k < systemsize; ++k) {xT[k] = x[k][i]; };
		for(int k = 0; k < systemsize; ++k) 
			{
				K[0][k] = rightpart[k](xT);
				help = xT + h/2 * K[0];
				K[1][k] = rightpart[k](help);
				help = xT + h/2 * K[1];
				K[2][k] = rightpart[k](help);
				help = xT + h* K[2];
				K[3][k] = rightpart[k](help);
			};
	 	for(int j = 0; j < systemsize; ++j)
	 	{
	 		x[j].push_back(xT[j] + h/6 * (K[0][j] + 2*K[1][j] + 2*K[2][j] + K[3][j]));
	 	}
	}

	return x;
}

template < typename T >
Portrait ODE::Runge_Kutta_4_adaptive(const std::vector<funtwo>& rightpart, 
									 const std::vector<T>& cond, 
									 int timestamps,
									 int systemsize,
									 T h,
									 std::vector<std::vector<T>>& x, 
									 T epsilon)
{
	const auto split = [&rightpart, systemsize](std::vector<T> cond, T h, int timestamps) -> std::vector<T> {
		std::vector<T> help(systemsize);
		std::vector<std::vector<T>> K(4);
		for (int i = 0; i < 4; ++i) {K[i] = help;};
		for(int t = 0; t < timestamps; ++t) {
			for(int i = 0; i < systemsize; ++i) {
				K[0][i] = rightpart[i](cond);
				help = cond + h/2 * K[0];
				K[1][i] = rightpart[i](help);
				help = cond + h/2 * K[1];
				K[2][i] = rightpart[i](help);
				help = cond + h* K[2];
				K[3][i] = rightpart[i](help);

				cond[i] = cond[i] + h/6 * (K[0][i] + 2*K[1][i] + 2*K[2][i] + K[3][i]);
			}
		}
		return cond;
	};

	for(int t = 0; t < timestamps-2; ++t) {
		std::vector<T> cond; for(int i = 0; i < systemsize; ++i) { cond.push_back(x[i][t]); }
		T tao = h;
		int divider = 1;
		auto next = split(cond, tao, divider);
		while(true) {
			divider += 1;
			tao = h/divider;
			auto closer = split(cond, tao, divider);
			auto _norm = norm(next - next)/(pow(2, divider) - 1);
			if(_norm <= epsilon) {
				break;
			}
			next = closer;
		}
		for(int i = 0; i < systemsize; ++i) { x[i].push_back(next[i]); }
	}
	return x;

	// return Runge_Kutta_4(rightpart, cond, timestamps, systemsize, h, x, epsilon);
}

template < typename T >
void ODE::Adams_Bashforth(const std::vector<funtwo>& rightpart, 
						  const std::vector<T>& cond, 
						  int timestamps,
						  int systemsize,
						  T h,
						  std::vector<std::vector<T>>& x, 
						  T epsilon)
{
	std::ofstream file;
	file.open("./output/Adams_Bashforth.dat");

	std::vector<T> help(systemsize);
	std::vector<std::vector<T>> xT(4);
	std::vector<std::vector<T>> K(4);
	for (int i = 0; i < 4; ++i) {K[i] = help; xT[i] = help;};

	for(int i = 0; i < 4; ++i)
	{
		for(int k = 0; k < systemsize; ++k) {xT[i][k] = x[k][i]; };

		for(int k = 0; k < systemsize; ++k) 
			{
				K[0][k] = rightpart[k](xT[i]);
				help = xT[i] + h/2 * K[0];
				K[1][k] = rightpart[k](help);
				help = xT[i] + h/2 * K[1];
				K[2][k] = rightpart[k](help);
				help = xT[i] + h* K[2];
				K[3][k] = rightpart[k](help);
			};

	 	for(int j = 0; j < systemsize; ++j)
	 	{
	 		x[j].push_back(xT[i][j] + h/6 * (K[0][j] + 2*K[1][j] + 2*K[2][j] + K[3][j]));
	 		file << xT[i][j] << ' ';
	 	}
	 	file << std::endl;
	}

	int ind[4] = {0,1,2,3};
	auto shift = [](int (& ind)[4]) -> void
	{
		int a = ind[0];
		for (int i = 0; i < 3; ++i) ind[i] = ind[i + 1];
		ind[3] = a;
	};

	 for(int i = 4; i < timestamps - 2; ++i)
	{
	 	for(int k = 0; k < systemsize; ++k) {xT[ind[3]][k] = x[k][i]; };

	   	for(int j = 0; j < systemsize; ++j)
	   	{
	   		x[j].push_back(xT[ind[3]][j] + h/24 * (55*rightpart[j](xT[ind[3]]) - 59*rightpart[j](xT[ind[2]]) 
	   			+ 37*rightpart[j](xT[ind[1]]) - 9*rightpart[j](xT[ind[0]])));
	   		file << xT[ind[3]][j] << ' ';
	  	}
	   	shift(ind);
   	file << std::endl;

	}
	for (int i = 0; i < systemsize; ++i ) file << x[i][timestamps - 3] << ' ';
	file << std::endl;
	file.close();
}

template < typename T >
void ODE::Forecast_correction(const std::vector<funtwo>& rightpart, 
						      const std::vector<T>& cond, 
						      int timestamps,
						      int systemsize,
						      T h,
						      std::vector<std::vector<T>>& x, 
						      T epsilon)
{
	std::ofstream file;
	file.open("./output/Forecast_correction.dat");

	std::vector<T> help(systemsize);
	std::vector<std::vector<T>> xT(4);
	std::vector<std::vector<T>> K(4);
	for (int i = 0; i < 4; ++i) {K[i] = help; xT[i] = help;};

	for(int i = 0; i < 4; ++i)
	{
		for(int k = 0; k < systemsize; ++k) {xT[i][k] = x[k][i]; };

		for(int k = 0; k < systemsize; ++k) 
			{
				K[0][k] = rightpart[k](xT[i]);
				help = xT[i] + h/2 * K[0];
				K[1][k] = rightpart[k](help);
				help = xT[i] + h/2 * K[1];
				K[2][k] = rightpart[k](help);
				help = xT[i] + h* K[2];
				K[3][k] = rightpart[k](help);
			};

	 	for(int j = 0; j < systemsize; ++j)
	 	{
	 		x[j].push_back(xT[i][j] + h/6 * (K[0][j] + 2*K[1][j] + 2*K[2][j] + K[3][j]));
	 		file << xT[i][j] << ' ';
	 	}
	 	file << std::endl;
	}

	int ind[4] = {0,1,2,3};
	auto shift = [](int (& ind)[4]) -> void
	{
		int a = ind[0];
		for (int i = 0; i < 3; ++i) ind[i] = ind[i + 1];
		ind[3] = a;
	};

	std::vector<T> forecast(systemsize);
	std::vector<vFunc> shifted(systemsize);
	for(int i = 4; i < timestamps - 2; ++i)
	{
	 	for(int k = 0; k < systemsize; ++k) {xT[ind[3]][k] = x[k][i]; };

	   	for(int j = 0; j < systemsize; ++j)
	   	{
	   		forecast[j] = xT[ind[3]][j] + h/24 * (55*rightpart[j](xT[ind[3]]) - 59*rightpart[j](xT[ind[2]]) 
	   			+ 37*rightpart[j](xT[ind[1]]) - 9*rightpart[j](xT[ind[0]]));
	   		file << xT[ind[3]][j] << ' ';
	  	}

		for (int i = 0; i < systemsize; ++i) 
		{ 
			x[i].push_back(xT[ind[3]][i] + h/24*( 9*rightpart[i](forecast) + 19*rightpart[i](xT[ind[3]])
			- 5*rightpart[i](xT[ind[2]]) + rightpart[i](xT[ind[1]])) ); 
		};
		shift(ind);

   		file << std::endl;
	}
	for (int i = 0; i < systemsize; ++i ) file << x[i][timestamps - 3] << ' ';
	file << std::endl;
	file.close();
}

template < typename T >
void ODE::save(std::vector<std::vector<T>>& portrait, std::string path) {
	std::ofstream file;
	file.open(path);
	const int timestamps = portrait[0].size();
	for(int t = 0; t < timestamps; ++t) {
		for(int i = 0; i < portrait.size(); ++i) {
			file << portrait[i][t] << ' '; 
		}
		file << std::endl;
	}
	file.close();
}

#endif