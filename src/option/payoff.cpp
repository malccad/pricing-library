#include "../../include/option/payoff.h"

#include <algorithm>
#include <cmath>

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

PayOffCashOrNthCall::PayOffCashOrNthCall(std::map<std::string, double> params):params(params){}

PayOff* PayOffCashOrNthCall::clone() const
{
    return new PayOffCashOrNthCall(*this);
}

double PayOffCashOrNthCall::operator()(double spot) const
{
    double strike = params.at("strike");
    return (spot >= strike) ? 1.0 : 0.0;
}

PayOffCashOrNthPut::PayOffCashOrNthPut(std::map<std::string, double> params):params(params){}

PayOff* PayOffCashOrNthPut::clone() const
{
    return new PayOffCashOrNthPut(*this);
}

double PayOffCashOrNthPut::operator()(double spot) const
{
    double strike = params.at("strike");
    return (spot <= strike) ? 1.0 : 0.0;
}

PayOffAssetOrNthCall::PayOffAssetOrNthCall(std::map<std::string, double> params):params(params){}

PayOff* PayOffAssetOrNthCall::clone() const
{
    return new PayOffAssetOrNthCall(*this);
}

double PayOffAssetOrNthCall::operator()(double spot) const
{
    double strike = params.at("strike");
    return (spot >= strike) ? spot : 0.0;
}

PayOffAssetOrNthPut::PayOffAssetOrNthPut(std::map<std::string, double> params):params(params){}

PayOff* PayOffAssetOrNthPut::clone() const
{
    return new PayOffAssetOrNthPut(*this);
}

double PayOffAssetOrNthPut::operator()(double spot) const
{
    double strike = params.at("strike");
    return (spot <= strike) ? spot : 0.0;
}

PayOffPowerCall::PayOffPowerCall(std::map<std::string, double> params):params(params){}

PayOff* PayOffPowerCall::clone() const
{
    return new PayOffPowerCall(*this);
}

double PayOffPowerCall::operator()(double spot) const
{
    double strike = params.at("strike");
    double power = params.at("power");
    return std::max(pow(spot, power) - pow(strike, power), 0.0);
}

PayOffPowerPut::PayOffPowerPut(std::map<std::string, double> params):params(params){}

PayOff* PayOffPowerPut::clone() const
{
    return new PayOffPowerPut(*this);
}

double PayOffPowerPut::operator()(double spot) const
{
    double strike = params.at("strike");
    double power = params.at("power");
    return std::max(pow(strike,power) - pow(spot, power), 0.0);
}
