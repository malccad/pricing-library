#ifndef PAYOFF_FACTORY_H
#define PAYOFF_FACTORY_H

#include <map>
#include <string>

#include "payoff.h"

class PayOffFactory
{
public:
    typedef std::unique_ptr<PayOff> (*CreatePayOffFunction)();
    static PayOffFactory& Instance();
    void registerPayOff(std::string payOffName, CreatePayOffFunction createPayOffFunction);
    std::unique_ptr<PayOff> createPayOff(std::string payOffName);
    std::vector<std::string> getPayOffNames() const;
private:
    std::map<std::string, CreatePayOffFunction> theCreatorFunctions;
    PayOffFactory(){}
    PayOffFactory(const PayOffFactory&){}
    PayOffFactory& operator=(const PayOffFactory&){return *this;}
    ~PayOffFactory(){}
};
#endif