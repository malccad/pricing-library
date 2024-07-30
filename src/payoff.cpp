#include "../include/payoff.h"

#include <algorithm>

PayOffCall::PayOffCall(std::map<std::string, double> params):params(params){}

PayOff* PayOffCall::clone() const
{
    return new PayOffCall(*this);
}

double PayOffCall::operator()(double spot) const
{
    double strike = params.at("strike");
    return std::max(spot - strike, 0.0);
}

PayOff* PayOffPut::clone() const
{
    return new PayOffPut(*this);
}

PayOffPut::PayOffPut(std::map<std::string, double> params):params(params){}


double PayOffPut::operator()(double spot) const
{
    double strike = params.at("strike");
    return std::max(strike - spot, 0.0);
}
PayOffDoubleDigital::PayOffDoubleDigital(std::map<std::string, double> params):params(params){}

PayOff* PayOffDoubleDigital::clone() const
{
    return new PayOffDoubleDigital(*this);
}

double PayOffDoubleDigital::operator()(double spot) const
{
    double lowerStrike = params.at("lowerStrike");
    double upperStrike = params.at("upperStrike");
    return (spot <= upperStrike & spot >= lowerStrike) ? 1: 0;
}