#include "../include/option.h"

Option::Option(const Wrapper<PayOff>& payOff, double expiry)
    :payOff(payOff), expiry(expiry)
{}

double Option::getPayOff(double spot) const
{
    return (*payOff)(spot);
}

Option* Option::clone() const{
    return new Option(*this);
}