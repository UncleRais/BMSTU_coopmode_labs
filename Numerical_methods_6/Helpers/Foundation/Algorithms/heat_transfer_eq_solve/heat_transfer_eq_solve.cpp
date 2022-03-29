#ifndef HEAT_TRANSFER_EQ_SOLVE_CPP
#define HEAT_TRANSFER_EQ_SOLVE_CPP

#include <climits>
#include <limits> 


#include "../../../../../Numerical_methods_5/Helpers/Foundation/Algorithms/Banish/Banish.cpp"
#include "./heat_transfer_eq_solve.h"

template < typename T >
void heat_transfer_eq_solve<T>::NDsolve(const std::string path, int left, int right, 
										size_t NumTime,  size_t NumX, size_t NumberOfResults,
										T LatterTime, T sigma)
{ 
	std::ofstream file_x_time_temp;
	//std::ofstream file_conservative_energy;
	file_x_time_temp.open(path);
	//file_conservative_energy.open("./output/conserv_energy.dat");

	T h = L/(NumX - 1);
	T tau = LatterTime/(NumTime - 1);
	T coef_cp = (h * c * rho)/tau;
	T mu_left, mu_right, sigm_a_i, sigm_a_i_1, help0, helpN;

	if(tau <= pow(h,2) * pow(L , 2) * c * rho / 2 / k2 / pow(NumX, 2)) {std::cout << "Явный метод устойчив!" << std::endl;}
		else {std::cout << "Явный метод не устойчив!" << std::endl;};

	std::vector<T> prev(NumX), actual(NumX), coef_a(NumX - 1), omega(NumX - 1), 
	A(NumX - 1), C(NumX), B(NumX - 1), F(NumX), x;
	x.reserve(NumX);

	for(size_t i = 0; i < NumX; i++)
	{
		x.push_back(i * h);
		prev[i] = InitTemp(i * h);
	}

	for(size_t i = 0; i < NumX; i++)
	{
		file_x_time_temp << x[i] << ' ' << 0 << ' ' << prev[i];
		file_x_time_temp << std::endl;
	}

	for(size_t j = 1; j < NumTime; j++)
	{
		for(size_t i = 0; i < NumX - 1; i++)
		{
			coef_a[i] = K(0, h*(i + 1/2));
			omega[i] = coef_a[i] * (prev[i+1] - prev[i]) / h;
		}

		help0 = coef_cp / 2 + sigma * coef_a[0] / h;
		helpN = coef_cp / 2 + sigma * coef_a[NumX - 2] / h;
		B[0] = right*sigma * coef_a[0] / h / help0;
		C[0] = -1;
		mu_left = (prev[0] * coef_cp / 2 - sigma * P((j + 1) * tau) + (1 - sigma) * (omega[0] - P(j * tau)) ) / help0;
		F[0] = -(left * mu_left + (1 - left) * T0);
		for(size_t i = 1; i < NumX - 1; i++)
		{	
			sigm_a_i_1 = sigma * coef_a[i - 1] / h;
			sigm_a_i = sigma * coef_a[i] / h;
			A[i - 1] = sigm_a_i_1;
			C[i] = -(sigm_a_i_1 + sigm_a_i + coef_cp);
			B[i] = sigm_a_i;
			F[i] = -(prev[i] * coef_cp + (1 - sigma) * (omega[i] - omega[i - 1]));
		} 
		A[NumX - 2] = right*(sigma * coef_a[NumX - 2] / h) / helpN;
		C[NumX - 1] = -1;
		mu_right = (prev[NumX - 1] * coef_cp / 2 + sigma * P(j * tau) + (1 - sigma) * (P((j - 1)*tau) - omega[NumX - 2])) / helpN;
		F[NumX - 1] =  -(right * mu_right  + (1 - right) * (T0));

		actual = Banish::solve(A , C , B , F);

		// T sum_energy = 0;

		// for(size_t i = 0 ; i < actual.size() - 1; ++i)
		// {
		// 	sum_energy += (actual[i] + actual[i+1]) * h /2;
		// }

		// file_conservative_energy << 1 - sum_energy << std::endl;

		if(!(j % NumberOfResults)) 
 		{
 			for(size_t i = 0; i < NumX; i++)
 			{
				file_x_time_temp << x[i] << ' ' << j * tau << ' ' << actual[i];
				file_x_time_temp << std::endl;
			}
 		}
		prev = actual;
	}
	file_x_time_temp.close();
	//file_conservative_energy.close();

}

template < typename T >
void heat_transfer_eq_solve<T>::TEST(const std::string path, bool left_flow, bool right_flow, size_t timestamps, size_t nodes, size_t results, T finish, T sigma) {
	std::ofstream file;
	file.open(path);

	T h = L/(nodes - 1);
	T tau = finish/(timestamps - 1);
	T r = (h*c*rho)/tau;

	std::vector<T> temperature(nodes), x(nodes);
	for(size_t i = 0; i < nodes; i++)
	{
		const auto node = i*h;
		const auto resting_heat = InitTemp(node);
		x[i] = node;
		temperature[i] = resting_heat;
		file << node << ' ' << 0 << ' ' << resting_heat;
		file << std::endl;
	}

	std::vector<T> A(nodes-1), B(nodes), C(nodes-1), F(nodes);
	for(size_t j = 1; j < timestamps; ++j)
	{
		if(left_flow) {
			const T a1 = (K(temperature[1], 0)+K(temperature[0], 0))/2;
			B[0] = -(r/2 + a1*sigma/h);
			C[0] = a1*sigma/h;
			F[0] = -(temperature[0]*r/2 + sigma*P(tau*(j))+(1-sigma)*(a1*(temperature[1]-temperature[0])/h-P(tau*(j-1))));
		} else {
			B[0] = 1.0;
			C[0] = 0.0;
			F[0] = InitTemp(x[0]);
		}

		for(size_t i = 1; i < nodes-1; ++i) {
			const T a  = (K(temperature[i], 0)+K(temperature[i-1], 0))/2;
			const T ap = (K(temperature[i+1], 0)+K(temperature[i], 0))/2;
			A[i-1] = ap*sigma/h;
			B[i]   = -(ap*sigma/h-a*sigma/h+r);
			C[i-1] = a*sigma/h;
			F[i]   = -(temperature[i]*r+(1-sigma)*( ap*(temperature[i+1]-temperature[i])/h-a*(temperature[i]-temperature[i-1])/h)); 
		}

		if(right_flow) {
			const T aN = (K(temperature[nodes-1], 0)+K(temperature[nodes-2], 0))/2;
			A[nodes-2] = -aN*sigma/h;
			B[nodes-1] = r/2 + aN*sigma/h;
			F[nodes-1] = temperature[nodes-1]*r/2 + sigma*P(tau*(j))+(1-sigma)*(P(tau*(j-1))-aN*(temperature[nodes-1] - temperature[nodes-2])/h);
		} else {
			A[nodes-2] = 0.0;
			B[nodes-1] = 1.0;
			F[nodes-1] = InitTemp(x[nodes-1]);
		}

		temperature = Banish::solve(A, B, C, F);
		if(!(j%results)) 
 		{
 			for(size_t i = 0; i < nodes; ++i)
 			{
				file << x[i] << ' ' << j*tau << ' ' << temperature[i];
				file << std::endl;
			}
 		}
	}

	file.close();
}

template < typename T >
void heat_transfer_eq_solve<T>::parameters_info() const
{
	std::cout << "Beam characteristics:\n";
	std::cout << "c = " << c << ", rho = " << rho << ", L = " << L <<";\n"; 
	std::cout << "Boundary conditions:\n";
	std::cout << "alpha = " << alpha << ", beta = " << beta << ", gamma = " << gamma << ",\n";
	std::cout << "x1 = " << x1 << ", x2 = " << x2 << ", k1 = " << k1 << ", k2 = " << k2 << ",\n";
	std::cout << "Q = " << Q << ", t0 = " << t0 << ", T0 = " << T0 << ";\n";
}

#endif