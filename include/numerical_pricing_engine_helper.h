#ifndef NUMERICAL_PRICING_ENGINE_HELPER_H
#define NUMERICAL_PRICING_ENGINE_HELPER_H

#include "numerical_pricing_engine_factory.h"
#include <memory>
template <class T>
class NumericalPricingEngineHelper
{
public:
    NumericalPricingEngineHelper(std::string);
    static std::unique_ptr<NumericalPricingEngine> createEngine(const Wrapper<EuropeanOption>&, double, double);
};

template <class T>
NumericalPricingEngineHelper<T>::NumericalPricingEngineHelper(
    std::string engineName
){
    NumericalPricingEngineFactory& theFactory = NumericalPricingEngineFactory::Instance();
    theFactory.registerEngine(engineName, createEngine);
}

template <class T>
std::unique_ptr<NumericalPricingEngine> NumericalPricingEngineHelper<T>::createEngine(
    const Wrapper<EuropeanOption>& theOption, double vol, double r
){
    return std::make_unique<T>(theOption, vol, r);
}
#endif

