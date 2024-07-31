#ifndef LAGUERRE_H
#define LAGUERRE_H
#include <vector>
// first m weighted laguerre polynomial, with weight exp(-x/2)
class Laguerre
{
public:
    Laguerre(unsigned long m);
    std::vector<double> operator()(double x) const;
private:
    unsigned long m;
};
#endif