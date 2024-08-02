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

class PayOffCashOrNthCall: public PayOff
{
public:
    PayOffCashOrNthCall(std::map<std::string, double> params);
    ~PayOffCashOrNthCall() override {};
    PayOff* clone() const override;
    double operator()(double spot) const override;
private:
    std::map<std::string, double> params;
};

class PayOffCashOrNthPut: public PayOff
{
public:
    PayOffCashOrNthPut(std::map<std::string, double> params);
    ~PayOffCashOrNthPut() override {};
    PayOff* clone() const override;
    double operator()(double spot) const override;
private:
    std::map<std::string, double> params;
};

class PayOffAssetOrNthCall: public PayOff
{
public:
    PayOffAssetOrNthCall(std::map<std::string, double> params);
    ~PayOffAssetOrNthCall() override {};
    PayOff* clone() const override;
    double operator()(double spot) const override;
private:
    std::map<std::string, double> params;
};

class PayOffAssetOrNthPut: public PayOff
{
public:
    PayOffAssetOrNthPut(std::map<std::string, double> params);
    ~PayOffAssetOrNthPut() override {};
    PayOff* clone() const override;
    double operator()(double spot) const override;
private:
    std::map<std::string, double> params;
};

class PayOffPowerCall: public PayOff
{
public:
    PayOffPowerCall(std::map<std::string, double> params);
    ~PayOffPowerCall() override {};
    PayOff* clone() const override;
    double operator()(double spot) const override;
private:
    std::map<std::string, double> params;
};

class PayOffPowerPut: public PayOff
{
public:
    PayOffPowerPut(std::map<std::string, double> params);
    ~PayOffPowerPut() override {};
    PayOff* clone() const override;
    double operator()(double spot) const override;
private:
    std::map<std::string, double> params;
};
#endif