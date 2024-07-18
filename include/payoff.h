#ifndef PAYOFF_H
#define PAYOFF_H

#include <map>
#include <vector>
#include <string>

class PayOff
{
public:
    PayOff(){};
    virtual std::vector<std::string> getParamNames() const=0;
    virtual void readParams(std::map<std::string, double>)=0;
    virtual ~PayOff(){};
    virtual PayOff* clone() const=0;
    virtual double operator()(double spot) const=0;
private:
};

class PayOffCall: public PayOff
{
public:
    PayOffCall(){};
    std::vector<std::string> getParamNames() const override;
    void readParams(std::map<std::string, double>) override;
    ~PayOffCall() override {};
    PayOff* clone() const override;
    double operator()(double spot) const override;
private:
    std::vector<std::string> paramNames{"strike"};
    std::map<std::string, double> params;
};

class PayOffPut: public PayOff
{
public:
    PayOffPut(){};
    std::vector<std::string> getParamNames() const override;
    void readParams(std::map<std::string, double>) override;
    ~PayOffPut() override {};
    PayOff* clone() const override;
    double operator()(double spot) const override;
private:
    std::vector<std::string> paramNames{"strike"};
    std::map<std::string, double> params;
};

class PayOffDoubleDigital: public PayOff
{
public:
    PayOffDoubleDigital(){};
    std::vector<std::string> getParamNames() const override;
    void readParams(std::map<std::string, double>) override;
    ~PayOffDoubleDigital() override {};
    PayOff* clone() const override;
    double operator()(double spot) const override;
private:
    std::vector<std::string> paramNames{"lower_strike", "upper_strike"};
    std::map<std::string, double> params;
};
#endif