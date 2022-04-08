#ifndef WAVE_EQ_SOLVE_CPP
#define WAVE_EQ_SOLVE_CPP

#include "wave_eq_solve.h"

template <typename T>
void wave_eq_solve<T>::solve(const std::string path, size_t timestamps, size_t sections, size_t NumberOfResults)
{
	std::ofstream file_x_time_y;
	file_x_time_y.open(path);

	const size_t nodes = sections + 1;
	const T h = L / sections, tau = finish_time / timestamps;
	const T lol =  tau * tau * a * a, sigma = lol / h / h; //Эти константы нужны для упрощения вычислений

	std::vector<T> prev1(nodes), prev2(nodes), actual(nodes), x;
	x.reserve(nodes);

	T node;
	for(size_t i = 0; i < nodes; ++i)
	{
	node = i * h;
	x.push_back(node);
	prev1[i] = InitShape(node);
	prev2[i] = prev1[i] + tau * InitVelocity(node) + lol / 2 * InitShapeXX(node);
	file_x_time_y << node << ' ' << 0 << ' ' << prev1[i];
	file_x_time_y << std::endl;
	}

	for(size_t i = 0; i < nodes; ++i)
	{
	file_x_time_y << x[i] << ' ' << tau << ' ' << prev2[i];
	file_x_time_y << std::endl;	
	}

	for(size_t j = 2; j < timestamps; ++j)
	{
		actual[0] = LeftBoundary(x[0]); 
		for(size_t i = 1; i < nodes - 1; ++i)
		{
			actual[i] = 2 * prev2[i] - prev1[i] + sigma * (prev2[i+1] - 2 * prev2[i] + prev2[i-1]);
		}
		actual[nodes-1] = RightBoundary(x[nodes-1]); 

		swap(prev1 , prev2);
		swap(prev2 , actual);

		if(!(j % NumberOfResults)) 
 		{
 			for(size_t i = 0; i < nodes; i++)
 			{
				file_x_time_y << x[i] << ' ' << j * tau << ' ' << prev2[i];
				file_x_time_y << std::endl;
			}
 		}
	}
file_x_time_y << nodes << std::endl;
file_x_time_y.close();
	
}


#endif