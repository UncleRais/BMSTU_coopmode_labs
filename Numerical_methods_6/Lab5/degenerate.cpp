#ifndef degenerate_cpp
#define degenerate_cpp

#include <cmath>


double phi1(double x){return( 1. );}
double phi2(double x){return(  -x );}
double phi3(double x){return(  pow(x,3));}
double phi4(double x){return( -pow(x,5) );}
double phi5(double x){return(  pow(x,7) );}
double phi6(double x){return( -pow(x,9) );}
double phi7(double x){return(  pow(x,11) );}
double phi8(double x){return( -pow(x,13) );}
double phi9(double x){return(  pow(x,15) );}
double phi10(double x){return(-pow(x,17) );}
double phi11(double x){return( pow(x,19) );}

double psi1(double s){return( 1. );}
double psi2(double s){return( 1. );}
double psi3(double s){return( pow(s,2) * 1./2 );}
double psi4(double s){return( pow(s,4)* 1./24 );} 
double psi5(double s){return( pow(s,6)* 1./720 );}
double psi6(double s){return( pow(s,8)* 1./40320 );}
double psi7(double s){return( pow(s,10)* 1./3628800 );}
double psi8(double s){return( pow(s,12)* 1./479001600 );}
double psi9(double s){return( pow(s,14)* 1./87178291200 );}
double psi10(double s){return( pow(s,16)* 1./20922789888000 );}
double psi11(double s){return( pow(s,18)* 1./6402373705728000 );}

std::vector<std::function<double (double)>> phi = {phi1, phi2,phi3,
												   phi4,phi5,phi6,
												   phi7,phi8,phi9,
												   phi10,phi11};
std::vector<std::function<double (double)>> psi = {psi1, psi2,psi3,
												   psi4,psi5,psi6,
												   psi7,psi8,psi9,
												   psi10,psi11};

#endif