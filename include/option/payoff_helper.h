#ifndef PAYOFF_HELPER_H
#define PAYOFF_HELPER_H

#include "payoff_factory.h"
#include "payoff.h"
#include <memory>

template<class T>
class PayOffHelper
{
public:
    PayOffHelper(std::string payOffName, std::vector<std::string> paramNames);
    static std::unique_ptr<PayOff> create(std::map<std::string, double> params);
private:

};

template<class T>
PayOffHelper<T>::PayOffHelper(std::string payOffName, std::vector<std::string> paramNames){
    PayOffFactory& thePayOffFactory = PayOffFactory::Instance();
    thePayOffFactory.registerPayOff(payOffName, PayOffHelper<T>::create, paramNames);
}

template<class T>
std::unique_ptr<PayOff> PayOffHelper<T>::create(std::map<std::string, double> params){
    return std::make_unique<T>(params);
}
#endif