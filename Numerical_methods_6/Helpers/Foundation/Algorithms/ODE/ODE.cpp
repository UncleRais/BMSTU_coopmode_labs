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
	std::vector<std::vector<T>> x;
	x.push_back({});
	for(int i = 0; i < systemsize; ++i)
	{
		x[0].push_back(cond[i + 2]);
	} 
	Portrait end;
	switch (name)
	{
	case ExplicitEuler_:
		return(ExplicitEuler(rightpart, timestamps, systemsize, h, x, epsilon));
		break;
	case ImplicitEuler_:
		return(ImplicitEuler(rightpart, timestamps, systemsize, h, x, epsilon));
		break;
	case Symmetrical_:
		return(Symmetrical(rightpart, timestamps, systemsize, h, x, epsilon));
		break;
	case Runge_Kutta_2_:
		return(Runge_Kutta_2(rightpart, timestamps, systemsize, h, x, epsilon));
		break;
	case Runge_Kutta_4_:
		return(Runge_Kutta_4(rightpart, timestamps, systemsize, h, x, epsilon));
		break;
	case Runge_Kutta_4_adaptive_:
		return(Runge_Kutta_4_adaptive(rightpart, cond, timestamps, systemsize, h, x, epsilon));
		break;
	case Adams_Bashforth_:
		return(Adams_Bashforth(rightpart, timestamps, systemsize, h, x, epsilon));
		break;
	case Forecast_correction_:
		return(Forecast_correction(rightpart, timestamps, systemsize, h, x, epsilon));
		break;
	default:
		return(end);
		break;
	}
return(end);
}

template < typename T >
Portrait ODE::Phase(const std::vector<funtwo>& rightpart, const std::vector<T>& cond, MethodType name, T h, T epsilon)
{
	auto _cond = cond;
	Portrait result = {};
	int counter = 0;
	const T start1 = -1;
	const T end1 = 1;
	const T start2 = -1;
	const T end2 = 1;
	const T stepper1 = 0.1;
	const T stepper2 = 0.1;
	result.push_back({ T(int( ((end1-start1)/stepper1 * (end2-start2))/stepper2 )), (cond[1] - cond[0])/h + 1 });
	for(T r = start1; r <= end1; r += stepper1){
		_cond[2] = r;
		for(T m = start2; m <= end2; m += stepper2)
		{
			_cond[3] = m;
			const auto part = NDsolve(rightpart, {cond[0], cond[1], r, m}, name, h, epsilon);
			result.insert(std::end(result), std::begin(part), std::end(part));
			std::cout << "Finished with t = " << ++counter << std::endl;
		}
	}
	return result;
}


template < typename T >
Portrait ODE::ExplicitEuler(const std::vector<funtwo>& rightpart,  
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
			// help = xT + h/2 * K;
			// x[j].push_back(xT[j] + h * rightpart[j](help));
			x[t+1].push_back(previous[j] + h * rightpart[j](help));
		}
	}

	return x;
}

template < typename T >
Portrait ODE::Runge_Kutta_4(const std::vector<funtwo>& rightpart,  
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
		}
		help = previous + h/2 * K[0];
		for(int k = 0; k < systemsize; ++k) 
		{
			K[1][k] = rightpart[k](help);
		}
		help = previous + h/2 * K[1];
		for(int k = 0; k < systemsize; ++k) 
		{
			K[2][k] = rightpart[k](help);
		}
		help = previous + h * K[2];
		for(int k = 0; k < systemsize; ++k) 
		{
			K[3][k] = rightpart[k](help);
		}
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
		sol = x[counter];
		// for(int i = 0; i < systemsize; ++i) { sol[i] = x[i][counter]; }
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
		//for(int i = 0; i < systemsize; ++i) { x[i].push_back(next[i]); }
		x.push_back(next);
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
						  std::vector<std::vector<T>> x, 
						  T epsilon)
{
	std::vector<T> help(systemsize);
	std::vector<std::vector<T>> K(4);
	std::vector<T> previous;
 	for (int i = 0; i < 4; ++i) {K[i] = help;};
	for(int t = 0; t < 4; ++t)
	{
		x.push_back({});
		previous = x[t];
		for(int k = 0; k < systemsize; ++k) 
		{
			K[0][k] = rightpart[k](previous);
		}
		help = previous + h/2 * K[0];
		for(int k = 0; k < systemsize; ++k) 
		{
			K[1][k] = rightpart[k](help);
		}
		help = previous + h/2 * K[1];
		for(int k = 0; k < systemsize; ++k) 
		{
			K[2][k] = rightpart[k](help);
		}
		help = previous + h * K[2];
		for(int k = 0; k < systemsize; ++k) 
		{
			K[3][k] = rightpart[k](help);
		}
	 	for(int j = 0; j < systemsize; ++j)
	 	{
	 		//x[j].push_back(xT[i][j] + h/6 * (K[0][j] + 2*K[1][j] + 2*K[2][j] + K[3][j]));
	 		x[t+1].push_back(previous[j] + h/6 * (K[0][j] + 2*K[1][j] + 2*K[2][j] + K[3][j]));
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
						      int timestamps,
						      int systemsize,
						      T h,
						      std::vector<std::vector<T>> x, 
						      T epsilon)
{
	std::vector<T> help(systemsize);
	std::vector<std::vector<T>> K(4);
	std::vector<T> previous;
	for (int i = 0; i < 4; ++i) {K[i] = help;};
	for(int t = 0; t < 4; ++t)
	{
		x.push_back({});
		previous = x[t];
		for(int k = 0; k < systemsize; ++k) 
		{
			K[0][k] = rightpart[k](previous);
		}
		help = previous + h/2 * K[0];
		for(int k = 0; k < systemsize; ++k) 
		{
			K[1][k] = rightpart[k](help);
		}
		help = previous + h/2 * K[1];
		for(int k = 0; k < systemsize; ++k) 
		{
			K[2][k] = rightpart[k](help);
		}
		help = previous + h * K[2];
		for(int k = 0; k < systemsize; ++k) 
		{
			K[3][k] = rightpart[k](help);
		}

	 	for(int j = 0; j < systemsize; ++j)
	 	{
	 		//x[j].push_back(xT[i][j] + h/6 * (K[0][j] + 2*K[1][j] + 2*K[2][j] + K[3][j]));
	 		x[t+1].push_back(previous[j] + h/6 * (K[0][j] + 2*K[1][j] + 2*K[2][j] + K[3][j]));
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