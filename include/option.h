#ifndef OPTION_H
#define OPTION_H

#include "wrapper.h"
#include "payoff.h"

class Option
{
public:
    enum OptionType {european, american};
    Option(const Wrapper<PayOff>& payOff, double expiry, OptionType theOptionType);
    double getPayOff(double spot) const;
    double getExpiry() const{return expiry;}
    OptionType getOptionType() const {return theOptionType;}
    Option* clone() const;
private:
    double expiry;
    Wrapper<PayOff> payOff;
    OptionType theOptionType;
};
#endif