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
	std::vector<std::vector<T>> x;
	x.push_back({});
	for(int i = 0; i < systemsize; ++i)
	{
		x[0].push_back(cond[i + 2]);
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
		portrait = Runge_Kutta_2(rightpart, cond, timestamps, systemsize, h, x, epsilon);
		save(portrait, "./output/Runge_Kutta_2.dat");
		std::cout << "Runge_Kutta_2 finised.";
		break;
	case Runge_Kutta_4_:
		portrait = Runge_Kutta_4(rightpart, cond, timestamps, systemsize, h, x, epsilon);
		save(portrait, "./output/Runge_Kutta_4.dat");
		std::cout << "Runge_Kutta_4 finised.";
		break;
	case Runge_Kutta_4_adaptive_:
		portrait = Runge_Kutta_4_adaptive(rightpart, cond, timestamps, systemsize, h, x, epsilon);
		save(portrait, "./output/Runge_Kutta_4_adaptive.dat");
		std::cout << "Runge_Kutta_4_adaptive finised.";
		break;
	case Adams_Bashforth_:
		portrait = Adams_Bashforth(rightpart, cond, timestamps, systemsize, h, x, epsilon);
		save(portrait, "./output/Adams_Bashforth.dat");
		std::cout << "Adams_Bashforth finised.";
		break;
	case Forecast_correction_:
		portrait = Forecast_correction(rightpart, cond, timestamps, systemsize, h, x, epsilon);
		save(portrait, "./output/Forecast_correction.dat");
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
						std::vector<std::vector<T>> x, 
						T epsilon)
{
	for(int t = 0; t < timestamps; ++t)
	{
		x.push_back({});
		for(int j = 0; j < systemsize; ++j) { x[t+1].push_back(x[t][j] + h * rightpart[j](x[t]));}
	}
	return x;
}

template < typename T >
Portrait ODE::ImplicitEuler(const std::vector<funtwo>& rightpart, 
						const std::vector<T>& cond, 
						int timestamps,
						int systemsize,
						T h,
						std::vector<std::vector<T>> x, 
						T epsilon)
{
	std::vector<vFunc> shifted;
	std::vector<T> previous;
	for (int i = 0; i < systemsize; ++i)
	{
		auto f = [&rightpart, &previous, i, h](const Point& x) -> double 
		{
			auto icantgoalone = x;
			return double(x[i] - previous[i] - h*rightpart[i](icantgoalone));
		};
		shifted.push_back(f);
	}
	for(int t = 0; t < timestamps; ++t)
	{ 
	 	previous = x[t];
		x.push_back({});
		Point next = NonLinearSolve::system_newton(shifted, {}, 30, {0, 0});
		for (int i = 0; i < systemsize; ++i) 
		{ 
			x[t+1].push_back(next[i]);
		}
	}

	return x;
}

template < typename T >
Portrait ODE::Symmetrical(const std::vector<funtwo>& rightpart, 
					  	  const std::vector<T>& cond, 
					  	  int timestamps,
					  	  int systemsize,
				      	  T h,
					  	  std::vector<std::vector<T>> x, 
					  	  T epsilon)
{
	std::vector<vFunc> shifted;
	std::vector<T> previous;
	for (int i = 0; i < systemsize; ++i)
	{
		auto f = [&rightpart, &previous, i, h](const Point& x) -> double 
		{
			auto icantgoalone = x;
			return double(x[i] - previous[i] - h/2*(rightpart[i](icantgoalone) + rightpart[i](previous)));
		};
		shifted.push_back(f);
	}
	for(int t = 0; t < timestamps; ++t)
	{ 
		x.push_back({});
		previous = x[t];
		Point next = NonLinearSolve::system_newton(shifted, {}, 30, {-5, 5});
		for (int i = 0; i < systemsize; ++i) 
		{ 
			x[t+1].push_back(next[i]);
		}
	}
	return x;
}

template < typename T >
Portrait ODE::Runge_Kutta_2(const std::vector<funtwo>& rightpart, 
						const std::vector<T>& cond, 
						int timestamps,
						int systemsize,
						T h,
						std::vector<std::vector<T>> x, 
						T epsilon)
{

	std::vector<T> previous(systemsize), K(systemsize), help(systemsize);
	for(int t = 0; t < timestamps; ++t)
	{
		x.push_back({});
		previous = x[t];
		for(int k = 0; k < systemsize; ++k) {K[k] = rightpart[k](previous);};
		help = previous + h/2 * K;
		for(int j = 0; j < systemsize; ++j)
		{
			x[t+1].push_back(previous[j] + h * rightpart[j](help));
		}
	}

	return x;
}

template < typename T >
Portrait ODE::Runge_Kutta_4(const std::vector<funtwo>& rightpart, 
							const std::vector<T>& cond, 
							int timestamps,
							int systemsize,
							T h,
							std::vector<std::vector<T>> x, 
							T epsilon)
{
	std::vector<T> previous(systemsize), help(systemsize);
	std::vector<std::vector<T>> K(4);
	for (int i = 0; i < 4; ++i) {K[i] = help;};
	for(int t = 0; t < timestamps; ++t)
	{
		previous = x[t];
		x.push_back({});
		for(int k = 0; k < systemsize; ++k) 
			{
				K[0][k] = rightpart[k](previous);
				help = previous + h/2 * K[0];
				K[1][k] = rightpart[k](help);
				help = previous + h/2 * K[1];
				K[2][k] = rightpart[k](help);
				help = previous + h* K[2];
				K[3][k] = rightpart[k](help);
			};
	 	for(int j = 0; j < systemsize; ++j)
	 	{
	 		x[t+1].push_back(previous[j] + h/6 * (K[0][j] + 2*K[1][j] + 2*K[2][j] + K[3][j]));
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
									 std::vector<std::vector<T>> x, 
									 T epsilon)
{
	const auto lastPoint = [](std::vector<std::vector<T>> portrait) -> std::vector<T> {
		const auto last = portrait.size() - 1;
		return portrait[last];
	};

	std::vector<T> norms;
	std::vector<T> steps;
	T tao = h;
	int divider = 1;
	for(int t = 0; t < timestamps; ++t)
	{
		auto next = lastPoint(Runge_Kutta_4(rightpart, cond, divider, systemsize, tao, {x[t]}, epsilon));
		bool execute = true;
		while(execute)
		{
			tao /= 2;
			divider *= 2;
			auto closer = lastPoint(Runge_Kutta_4(rightpart, cond, divider, systemsize, tao, {x[t]}, epsilon));
			auto _norm = norm(next - closer)/(pow(2, 4) - 1);
			if(_norm <= epsilon)
			{
				if(_norm <= epsilon/1000)
				{
					divider /= 2;
					tao *= 2;
				}
				norms.push_back(_norm);
				steps.push_back(tao);
				execute = false;
			}
			next = closer;
		}
		x.push_back(next);
	}
	save(norms, "./output/Runge_Kutta_4_norms.dat");
	save(steps, "./output/Runge_Kutta_4_steps.dat");
	return x;
}

template < typename T >
Portrait ODE::Adams_Bashforth(const std::vector<funtwo>& rightpart, 
						  const std::vector<T>& cond, 
						  int timestamps,
						  int systemsize,
						  T h,
						  std::vector<std::vector<T>> x, 
						  T epsilon)
{
	std::vector<T> help(systemsize);
	std::vector<std::vector<T>> K(4);
	for (int i = 0; i < 4; ++i) {K[i] = help;};
	for(int t = 0; t < 4; ++t)
	{
		x.push_back({});
		for(int k = 0; k < systemsize; ++k) 
			{
				K[0][k] = rightpart[k](x[t]);
				help = x[t] + h/2 * K[0];
				K[1][k] = rightpart[k](help);
				help = x[t] + h/2 * K[1];
				K[2][k] = rightpart[k](help);
				help = x[t] + h* K[2];
				K[3][k] = rightpart[k](help);
			};
	 	for(int j = 0; j < systemsize; ++j)
	 	{
	 		x[t+1].push_back(x[t][j] + h/6 * (K[0][j] + 2*K[1][j] + 2*K[2][j] + K[3][j]));
	 	}
	}

	 for(int t = 4; t < timestamps; ++t)
	{
		x.push_back({});
	   	for(int j = 0; j < systemsize; ++j)
	   	{
	   		x[t+1].push_back(x[t][j] + h/24 * (55*rightpart[j](x[t]) - 59*rightpart[j](x[t-1]) 
	   			+ 37*rightpart[j](x[t-2]) - 9*rightpart[j](x[t-3])));
	  	}
	}

	return x;
}

template < typename T >
Portrait ODE::Forecast_correction(const std::vector<funtwo>& rightpart, 
						      const std::vector<T>& cond, 
						      int timestamps,
						      int systemsize,
						      T h,
						      std::vector<std::vector<T>> x, 
						      T epsilon)
{
	std::vector<T> help(systemsize);
	std::vector<std::vector<T>> K(4);
	for (int i = 0; i < 4; ++i) {K[i] = help;};
	for(int t = 0; t < 4; ++t)
	{
		x.push_back({});
		for(int k = 0; k < systemsize; ++k) 
			{
				K[0][k] = rightpart[k](x[t]);
				help = x[t] + h/2 * K[0];
				K[1][k] = rightpart[k](help);
				help = x[t] + h/2 * K[1];
				K[2][k] = rightpart[k](help);
				help = x[t] + h* K[2];
				K[3][k] = rightpart[k](help);
			};
	 	for(int j = 0; j < systemsize; ++j)
	 	{
	 		x[t+1].push_back(x[t][j] + h/6 * (K[0][j] + 2*K[1][j] + 2*K[2][j] + K[3][j]));
	 	}
	}
	std::vector<T> forecast(systemsize);
	for(int t = 4; t < timestamps; ++t)
	{
		x.push_back({});
	   	for(int j = 0; j < systemsize; ++j)
	   	{
	   		forecast[j] = x[t][j] + h/24 * (55*rightpart[j](x[t]) - 59*rightpart[j](x[t-1]) 
	   			+ 37*rightpart[j](x[t-2]) - 9*rightpart[j](x[t-3]));
	  	}

		for (int i = 0; i < systemsize; ++i) 
		{ 
			x[t+1].push_back(x[t][i] + h/24*( 9*rightpart[i](forecast) + 19*rightpart[i](x[t])
			- 5*rightpart[i](x[t-1]) + rightpart[i](x[t-2])) ); 
		};
	}

	return x;
}

template < typename T >
void ODE::save(std::vector<std::vector<T>>& portrait, std::string path) {
	std::ofstream file;
	file.open(path);
	for(const auto &point: portrait)
	{
		for(const auto &coordinate: point)
		{
			file << coordinate << ' ';
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