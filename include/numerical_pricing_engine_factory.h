#ifndef NUMERICAL_PRICING_ENGINE_FACTORY_H
#define NUMERICAL_PRICING_ENGINE_FACTORY_H

#include <map>
#include <string>

#include "numerical_pricing_engine.h"

class NumericalPricingEngineFactory
{
public:
    typedef std::unique_ptr<NumericalPricingEngine> (*CreateEngineFunction)(const Wrapper<Option>& theOption, double vol, double r, double div);

    static NumericalPricingEngineFactory& Instance();
    void registerEngine(std::string, CreateEngineFunction);
    std::unique_ptr<NumericalPricingEngine> createEngine(std::string engineName, const Wrapper<Option>& theOption, double vol, double r, double div);
    std::vector<std::string> getEngineNames() const;
private:
    std::map<std::string, CreateEngineFunction> theCreatorFunctions;
    NumericalPricingEngineFactory(){}
    ~NumericalPricingEngineFactory(){}
    NumericalPricingEngineFactory(const NumericalPricingEngineFactory&){}
    NumericalPricingEngineFactory& operator=(const NumericalPricingEngineFactory&){return *this;}
};
#endif