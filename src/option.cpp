#include "../include/option.h"

Option::Option(const Wrapper<PayOff>& payOff, double expiry, OptionType theOptionType)
    :payOff(payOff), expiry(expiry), theOptionType(theOptionType)
{}

double Option::getPayOff(double spot) const
{
    return (*payOff)(spot);
}

Option* Option::clone() const{
    return new Option(*this);
}