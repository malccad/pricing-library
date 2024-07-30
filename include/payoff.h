#ifndef PAYOFF_H
#define PAYOFF_H

#include <map>
#include <vector>
#include <string>

class PayOff
{
public:
    PayOff(){};
    virtual ~PayOff(){};
    virtual PayOff* clone() const=0;
    virtual double operator()(double spot) const=0;
private:
};

class PayOffCall: public PayOff
{
public:
    PayOffCall(std::map<std::string, double> params);
    ~PayOffCall() override {};
    PayOff* clone() const override;
    double operator()(double spot) const override;
private:
    std::map<std::string, double> params;
};

class PayOffPut: public PayOff
{
public:
    PayOffPut(std::map<std::string, double> params);
    ~PayOffPut() override {};
    PayOff* clone() const override;
    double operator()(double spot) const override;
private:
    std::map<std::string, double> params;
};

class PayOffDoubleDigital: public PayOff
{
public:
    PayOffDoubleDigital(std::map<std::string, double> params);
    ~PayOffDoubleDigital() override {};
    PayOff* clone() const override;
    double operator()(double spot) const override;
private:
    std::map<std::string, double> params;
};
#endif