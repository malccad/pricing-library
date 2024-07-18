#include "../include/european_option.h"

EuropeanOption::EuropeanOption(const Wrapper<PayOff>& payOff, double expiry)
    :payOff(payOff), expiry(expiry)
{}

double EuropeanOption::getPayOff(double spot) const
{
    return (*payOff)(spot);
}

EuropeanOption* EuropeanOption::clone() const{
    return new EuropeanOption(*this);
}