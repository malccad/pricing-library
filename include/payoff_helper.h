#ifndef PAYOFF_HELPER_H
#define PAYOFF_HELPER_H

#include "payoff_factory.h"
#include "payoff.h"
#include <memory>

template<class T>
class PayOffHelper
{
public:
    PayOffHelper(std::string payOffName);
    static std::unique_ptr<PayOff> create();
private:

};

template<class T>
PayOffHelper<T>::PayOffHelper(std::string payOffName){
    PayOffFactory& thePayOffFactory = PayOffFactory::Instance();
    thePayOffFactory.registerPayOff(payOffName, PayOffHelper<T>::create);
}

template<class T>
std::unique_ptr<PayOff> PayOffHelper<T>::create(){
    return std::make_unique<T>();
}
#endif