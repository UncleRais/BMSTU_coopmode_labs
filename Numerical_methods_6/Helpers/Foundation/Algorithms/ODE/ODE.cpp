#ifndef ODE_CPP
#define ODE_CPP
#include "./ODE.h"

//MARK: Let's make a deal
// t – time iterator, current t is a timestamp
// i - node iterator, current t is a dimensional point

template < typename T >
Portrait ODE::NDsolve(const std::vector<funtwo>& rightpart, 
				  const std::vector<T>& cond, 
				  MethodType name, 
				  T h,
				  T epsilon)
{
	int systemsize = rightpart.size(); 
	int timestamps = (cond[1] - cond[0])/h + 1;
	std::vector<std::vector<T>> x(systemsize);
	for(int i = 0; i < systemsize; ++i)
	{
		x[i].reserve(timestamps);
		x[i].push_back(cond[i + 2]);
	} 
	Portrait end;
	switch (name)
	{
	case ExplicitEuler_:
		//std::cout << "ExplicitEuler finised.";
		return(ExplicitEuler(rightpart, timestamps, systemsize, h, x, epsilon));
		break;
	case ImplicitEuler_:
		//std::cout << "ImplicitEuler finised.";
		return(ImplicitEuler(rightpart, timestamps, systemsize, h, x, epsilon));
		break;
	case Symmetrical_:
		//std::cout << "Symmetrical finised.";
		return(Symmetrical(rightpart, timestamps, systemsize, h, x, epsilon));
		break;
	case Runge_Kutta_2_:
		//std::cout << "Runge_Kutta_2 finised.";
		return(Runge_Kutta_2(rightpart, timestamps, systemsize, h, x, epsilon));
		break;
	case Runge_Kutta_4_:
		//std::cout << "Runge_Kutta_4 finised.";
		return(Runge_Kutta_4(rightpart, timestamps, systemsize, h, x, epsilon));
		break;
	case Runge_Kutta_4_adaptive_:
		//std::cout << "Runge_Kutta_4_adaptive finised.";
		return(Runge_Kutta_4_adaptive(rightpart, cond, timestamps, systemsize, h, x, epsilon));
		break;
	case Adams_Bashforth_:
		//std::cout << "Adams_Bashforth finised.";
		return(Adams_Bashforth(rightpart, timestamps, systemsize, h, x, epsilon));
		break;
	case Forecast_correction_:
		//std::cout << "Forecast_correction finised.";
		return(Forecast_correction(rightpart, timestamps, systemsize, h, x, epsilon));
		break;
	default:
		//std::cout << "Unknown method! Please, check MethodType.";
		return(end);
		break;
	}
	return(end);
}



template < typename T >
Portrait ODE::ExplicitEuler(const std::vector<funtwo>& rightpart,  
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
Portrait ODE::Runge_Kutta_2(const std::vector<funtwo>& rightpart,  
						int timestamps,
						int systemsize,
						T h,
						std::vector<std::vector<T>>& x, 
						T epsilon)
{
	std::vector<T> xT(systemsize), K(systemsize), help(systemsize);
	for(int i = 0; i < timestamps - 2; ++i)
	{
		for(int k = 0; k < systemsize; ++k) {xT[k] = x[k][i]; };

		for(int k = 0; k < systemsize; ++k) {K[k] = rightpart[k](xT);};

		for(int j = 0; j < systemsize; ++j)
		{
			help = xT + h/2 * K;
			x[j].push_back(xT[j] + h * rightpart[j](help));
		}
	}

	return x;
}

template < typename T >
Portrait ODE::Runge_Kutta_4(const std::vector<funtwo>& rightpart,  
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
		}
		help = xT + h/2 * K[0];
		for(int k = 0; k < systemsize; ++k) 
		{
			K[1][k] = rightpart[k](help);
		}
		help = xT + h/2 * K[1];
		for(int k = 0; k < systemsize; ++k) 
		{
			K[2][k] = rightpart[k](help);
		}
		help = xT + h * K[2];
		for(int k = 0; k < systemsize; ++k) 
		{
			K[3][k] = rightpart[k](help);
		}
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
	const auto split = [&rightpart, systemsize](std::vector<T> x, T h) -> std::vector<T> 
	{
		std::vector<T> help(systemsize);
		std::vector<std::vector<T>> K(4);
		for (int i = 0; i < 4; ++i) {K[i] = help;};
		std::vector<T> res = x;
			for(int i = 0; i < systemsize; ++i) 
			{
				K[0][i] = rightpart[i](x);
			}
			help = x + h/2 * K[0];
			for(int i = 0; i < systemsize; ++i) 
			{
				K[1][i] = rightpart[i](help);
			}
			help = x + h/2 * K[1];
			for(int i = 0; i < systemsize; ++i) 
			{
				K[2][i] = rightpart[i](help);
			}
			help = x + h * K[2];
			for(int i = 0; i < systemsize; ++i) 
			{
				K[3][i] = rightpart[i](help);
			}
		res = res + h/6 * (K[0] +  K[1] + K[1] + K[2] + K[2] + K[3]);
		return res;
	};
	
	std::vector<T> norms;
	std::vector<T> steps;
	norms.reserve(timestamps);
	steps.reserve(timestamps);
	std::vector<T> sol(systemsize);
	std::vector<T> next, closer;
	int counter = 0;
	T tao = h, _norm;

	for(double t; t <= cond[1]; t += tao)
	{ 
		for(int i = 0; i < systemsize; ++i) { sol[i] = x[i][counter]; }
		next = split(sol, tao);

		while(true) 
		{
			next = split(sol, tao);
			closer = split(split(sol, tao/2), tao/2);
			_norm = norm(next - closer)/15;
			if(_norm <= epsilon) { break; } else { tao = tao/2; };
		}
		  while(true) 
		{
		   next = split(sol, tao);
		   closer = split(split(sol, tao/2), tao/2);
		   _norm = norm(next - closer)/15;
		   if(_norm < epsilon/10){ tao = tao * 2; } else { break; };
		}
		for(int i = 0; i < systemsize; ++i) { x[i].push_back(next[i]); }
		norms.push_back(_norm);
		steps.push_back(tao);
		++counter;
	}
	save(norms, "./output/Runge_Kutta_4_norms.dat");
	save(steps, "./output/Runge_Kutta_4_steps.dat");
	return x;
}

template < typename T >
Portrait ODE::Adams_Bashforth(const std::vector<funtwo>& rightpart,  
						  int timestamps,
						  int systemsize,
						  T h,
						  std::vector<std::vector<T>>& x, 
						  T epsilon)
{
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
		}
		help = xT[i] + h/2 * K[0];
		for(int k = 0; k < systemsize; ++k) 
		{
			K[1][k] = rightpart[k](help);
		}
		help = xT[i] + h/2 * K[1];
		for(int k = 0; k < systemsize; ++k) 
		{
			K[2][k] = rightpart[k](help);
		}
		help = xT[i] + h * K[2];
		for(int k = 0; k < systemsize; ++k) 
		{
			K[3][k] = rightpart[k](help);
		}
	 	for(int j = 0; j < systemsize; ++j)
	 	{
	 		x[j].push_back(xT[i][j] + h/6 * (K[0][j] + 2*K[1][j] + 2*K[2][j] + K[3][j]));
	 	}
	}

	int ind[4] = {0,1,2,3};
	auto shift = [](int (& ind)[4]) -> void
	{
		int a = ind[0];
		for (int i = 0; i < 3; ++i) ind[i] = ind[i + 1];
		ind[3] = a;
	};
	shift(ind);

	 for(int i = 4; i < timestamps - 2; ++i)
	{
		for(int k = 0; k < systemsize; ++k) {xT[ind[3]][k] = x[k][i]; };

	   	for(int j = 0; j < systemsize; ++j)
	   	{
	   		x[j].push_back(xT[ind[3]][j] + h/24 * (55*rightpart[j](xT[ind[3]]) - 59*rightpart[j](xT[ind[2]]) 
	   			+ 37*rightpart[j](xT[ind[1]]) - 9*rightpart[j](xT[ind[0]])));
	  	}
	   	shift(ind);
	}
	
	return x;
}

template < typename T >
Portrait ODE::Forecast_correction(const std::vector<funtwo>& rightpart,  
						      int timestamps,
						      int systemsize,
						      T h,
						      std::vector<std::vector<T>>& x, 
						      T epsilon)
{
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
		}
		help = xT[i] + h/2 * K[0];
		for(int k = 0; k < systemsize; ++k) 
		{
			K[1][k] = rightpart[k](help);
		}
		help = xT[i] + h/2 * K[1];
		for(int k = 0; k < systemsize; ++k) 
		{
			K[2][k] = rightpart[k](help);
		}
		help = xT[i] + h * K[2];
		for(int k = 0; k < systemsize; ++k) 
		{
			K[3][k] = rightpart[k](help);
		}

	 	for(int j = 0; j < systemsize; ++j)
	 	{
	 		x[j].push_back(xT[i][j] + h/6 * (K[0][j] + 2*K[1][j] + 2*K[2][j] + K[3][j]));
	 	}
	}

	int ind[4] = {0,1,2,3};
	auto shift = [](int (& ind)[4]) -> void
	{
		int a = ind[0];
		for (int i = 0; i < 3; ++i) ind[i] = ind[i + 1];
		ind[3] = a;
	};
	shift(ind);

	std::vector<T> forecast(systemsize);
	std::vector<vFunc> shifted(systemsize);
	for(int i = 4; i < timestamps - 2; ++i)
	{
	 	for(int k = 0; k < systemsize; ++k) {xT[ind[3]][k] = x[k][i]; };

	   	for(int j = 0; j < systemsize; ++j)
	   	{
	   		forecast[j] = xT[ind[3]][j] + h/24 * (55*rightpart[j](xT[ind[3]]) - 59*rightpart[j](xT[ind[2]]) 
	   			+ 37*rightpart[j](xT[ind[1]]) - 9*rightpart[j](xT[ind[0]]));
	  	}

		for (int i = 0; i < systemsize; ++i) 
		{ 
			x[i].push_back(xT[ind[3]][i] + h/24*( 9*rightpart[i](forecast) + 19*rightpart[i](xT[ind[3]])
			- 5*rightpart[i](xT[ind[2]]) + rightpart[i](xT[ind[1]])) ); 
		};
		shift(ind);
	}

	return x;
}

template < typename T >
void ODE::save(std::vector<std::vector<T>>& portrait, std::string path) {
	std::ofstream file;
	file.open(path);
	int portraitsize = portrait.size();
	const int timestamps = portrait[0].size();
	for(int t = 0; t < timestamps; ++t) {
		for(int i = 0; i < portraitsize; ++i) {
			file << portrait[i][t] << ' '; 
		}
		file << std::endl;
	}
	file.close();
}

template < typename T >
void ODE::save(std::vector<T>& portrait, std::string path) {
	std::ofstream file;
	file.open(path);
	int counter = 0;
	for(const auto &value: portrait) { file << ++counter << ' ' << value << std::endl;  }
	file.close();
}

#endif