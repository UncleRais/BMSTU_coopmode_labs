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
void ODE::Phase(const std::vector<funtwo>& rightpart, const std::vector<T>& cond, MethodType name, T epsilon)
{
	int timestamps = 1000, systemsize = rightpart.size(); 
	T h = (cond[1] - cond[0])/(timestamps - 1);
	std::vector<std::vector<T>> x;
    std::vector<std::vector<T>> C;
	for(T i = 0; i < 30; i += 0.5 ) { C.push_back({-30, i}); }
	for(T i = 0; i < 30; i += 0.5 ) { C.push_back({i, -30}); }
	for(T i = 0; i < 30; i += 0.5 ) { C.push_back({30, i}); }
	for(T i = 0; i < 30; i += 0.5 ) { C.push_back({i, 30}); }
	for(int r = 0; r < C.size(); ++r)
	{
		std::vector<std::vector<T>> x;
		x.push_back(C[r]);
		Portrait portrait; 
		switch (name)
		{
		case ExplicitEuler_:
			portrait = ExplicitEuler(rightpart, timestamps, systemsize, h, x, epsilon);
			save(portrait, "./output/phaseExplicitEuler/r=" + std::to_string(r) + ".dat");
			break;
		case ImplicitEuler_:
			portrait = ImplicitEuler(rightpart, timestamps, systemsize, h, x, epsilon);
			save(portrait, "./output/phaseImplicitEuler/r=" + std::to_string(r) + ".dat");
			break;
		case Symmetrical_:
			portrait = Symmetrical(rightpart, timestamps, systemsize, h, x, epsilon);
			save(portrait, "./output/phaseSymmetrical/r=" + std::to_string(r) + ".dat");
			break;
		case Runge_Kutta_2_:
			portrait = Runge_Kutta_2(rightpart, timestamps, systemsize, h, x, epsilon);
			save(portrait, "./output/phaseRK2/r=" + std::to_string(r) + ".dat");
			break;
		case Runge_Kutta_4_:
			portrait = Runge_Kutta_4(rightpart, timestamps, systemsize, h, x, epsilon);
			save(portrait, "./output/phaseRK4/r=" + std::to_string(r) + ".dat");
			break;
		case Runge_Kutta_4_adaptive_:
			portrait = Runge_Kutta_4_adaptive(rightpart, cond, timestamps, systemsize, h, x, epsilon);
			save(portrait, "./output/phaseRK4_adaptive/r=" + std::to_string(r) + ".dat");
			break;
		case Adams_Bashforth_:
			portrait = Adams_Bashforth(rightpart, timestamps, systemsize, h, x, epsilon);
			save(portrait, "./output/phaseAB/r=" + std::to_string(r) + ".dat");
			break;
		case Forecast_correction_:
			portrait = Forecast_correction(rightpart, timestamps, systemsize, h, x, epsilon);
			save(portrait, "./output/phaseFC/r=" + std::to_string(r) + ".dat");
			break;
		default:
			std::cout << "Unknown method! Please, check MethodType.";
			break;
		}
		std:: cout << "Finished r = " << r << std::endl;
	}
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

	// std::vector<T> xT(systemsize), K(systemsize), help(systemsize);
	// for(int i = 0; i < timestamps - 2; ++i)

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
	// const auto lastPoint = [](std::vector<std::vector<T>> portrait) -> std::vector<T> {
	// 	const auto last = portrait.size() - 1;
	// 	return portrait[last];
	// };

	// T tao = h;
	// int divider = 1;
	// std::vector<T> norms;
	// std::vector<T> steps;
	// for(int t = 0; t < timestamps; ++t)
	// {
	// 	auto next = lastPoint(Runge_Kutta_4(rightpart, cond, divider, systemsize, tao, {x[t]}, epsilon));
	// 	bool execute = true;
	// 	while(execute)
	// 	{
	// 		tao /= 2;
	// 		divider *= 2;
	// 		auto closer = lastPoint(Runge_Kutta_4(rightpart, cond, divider, systemsize, tao, {x[t]}, epsilon));
	// 		auto _norm = norm(next - closer)/(pow(2, 4) - 1);
	// 		if(_norm <= epsilon)
	// 		{
	// 			if(_norm <= epsilon/4)
	// 			{
	// 				divider /= 2;
	// 				tao *= 2;
	// 				closer = next;
	// 			}
	// 			norms.push_back(_norm);
	// 			steps.push_back(tao);
	// 			execute = false;
	// 		}
	// 		next = closer;
	// 	}
	// 	x.push_back(next);
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
	// 	int a = ind[0];
	// 	for (int i = 0; i < 3; ++i) ind[i] = ind[i + 1];
	// 	ind[3] = a;
	// };
	// shift(ind);

	//  for(int i = 4; i < timestamps - 2; ++i)
	// {
	// 	for(int k = 0; k < systemsize; ++k) {xT[ind[3]][k] = x[k][i]; };

	//    	for(int j = 0; j < systemsize; ++j)
	//    	{
	//    		x[j].push_back(xT[ind[3]][j] + h/24 * (55*rightpart[j](xT[ind[3]]) - 59*rightpart[j](xT[ind[2]]) 
	//    			+ 37*rightpart[j](xT[ind[1]]) - 9*rightpart[j](xT[ind[0]])));
	//   	}
	//    	shift(ind);
	// }
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

	// int ind[4] = {0,1,2,3};
	// auto shift = [](int (& ind)[4]) -> void
	// {
	// 	int a = ind[0];
	// 	for (int i = 0; i < 3; ++i) ind[i] = ind[i + 1];
	// 	ind[3] = a;
	// };
	// shift(ind);
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