#ifndef PAYOFF_FACTORY_H
#define PAYOFF_FACTORY_H

#include <map>
#include <string>

#include "payoff.h"

class PayOffFactory
{
public:
    typedef std::unique_ptr<PayOff> (*CreatePayOffFunction)(std::map<std::string, double>);
    static PayOffFactory& Instance();
    void registerPayOff(std::string payOffName, CreatePayOffFunction createPayOffFunction, std::vector<std::string> paramNames);
    std::unique_ptr<PayOff> createPayOff(std::string payOffName, std::map<std::string, double> params);
    std::vector<std::string> getPayOffNames() const;
    std::vector<std::string> getParamNames(std::string payOffName);
private:
    std::map<std::string, CreatePayOffFunction> theCreatorFunctions;
    std::map<std::string, std::vector<std::string>> payOffParamNames;
    PayOffFactory(){}
    PayOffFactory(const PayOffFactory&){}
    PayOffFactory& operator=(const PayOffFactory&){return *this;}
    ~PayOffFactory(){}
};
#endif