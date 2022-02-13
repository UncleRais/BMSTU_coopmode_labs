#ifndef ODE_H
#define ODE_H

typedef double(*funtwo)(double, double);

class ODE {

public:
template < typename T >
static void NDsolve(std::vector<funtwo> rightpart, T (&cond)[2][2], T epsilon = 1e-3);

};

#endif