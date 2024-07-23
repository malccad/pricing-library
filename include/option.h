#ifndef OPTION_H
#define OPTION_H

#include "wrapper.h"
#include "payoff.h"

class Option
{
public:
    Option(const Wrapper<PayOff>& payOff, double expiry);
    double getPayOff(double spot) const;
    double getExpiry() const{return expiry;}
    Option* clone() const;
private:
    double expiry;
    Wrapper<PayOff> payOff;
};
#endif