#ifndef EUROPEAN_OPTION_H
#define EUROPEAN_OPTION_H

#include "wrapper.h"
#include "payoff.h"

class EuropeanOption
{
public:
    EuropeanOption(const Wrapper<PayOff>& payOff, double expiry);
    double getPayOff(double spot) const;
    double getExpiry() const{return expiry;}
    EuropeanOption* clone() const;
private:
    double expiry;
    Wrapper<PayOff> payOff;
};
#endif