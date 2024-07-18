#include "../include/payoff.h"

#include <algorithm>

PayOff* PayOffCall::clone() const
{
    return new PayOffCall(*this);
}

std::vector<std::string> PayOffCall::getParamNames() const{
    return paramNames;
}

void PayOffCall::readParams(std::map<std::string, double> params_){
    params = params_;
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

std::vector<std::string> PayOffPut::getParamNames() const{
    return paramNames;
}

void PayOffPut::readParams(std::map<std::string, double> params_){
    params = params_;
}

double PayOffPut::operator()(double spot) const
{
    double strike = params.at("strike");
    return std::max(strike - spot, 0.0);
}

PayOff* PayOffDoubleDigital::clone() const
{
    return new PayOffDoubleDigital(*this);
}

std::vector<std::string> PayOffDoubleDigital::getParamNames() const{
    return paramNames;
}

void PayOffDoubleDigital::readParams(std::map<std::string, double> params_){
    params = params_;
}

double PayOffDoubleDigital::operator()(double spot) const
{
    double lowerStrike = params.at("lower_strike");
    double upperStrike = params.at("upper_strike");
    return (spot <= upperStrike & spot >= lowerStrike) ? 1: 0;
}