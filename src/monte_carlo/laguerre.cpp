#include <cmath>
#include "../../include/monte_carlo/laguerre.h"

Laguerre::Laguerre(unsigned long m)
    :m(m)
{
    assert (m>=2);
}

std::vector<double> Laguerre::operator()(double x) const{
    std::vector<double> out {1, 1-x};
    for (int i=2; i<m; ++i){
        double y = ((2*i-1-x)*out[i-1]-(i-1)*out[i-2])/i;
        out.push_back(y);
    }
    double weight = exp(-x/2);
    for (int i=0; i<out.size(); ++i){
        out[i] *= weight;
    }
    return out;
}