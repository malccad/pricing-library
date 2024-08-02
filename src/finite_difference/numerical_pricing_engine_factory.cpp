#include "../../include/finite_difference/numerical_pricing_engine_factory.h"

#include <iostream>
NumericalPricingEngineFactory& NumericalPricingEngineFactory::Instance(){
    static NumericalPricingEngineFactory theFactory;
    return theFactory;
}

void NumericalPricingEngineFactory::registerEngine(std::string engineName, CreateEngineFunction createEngineFunction){
    theCreatorFunctions.insert(std::pair<std::string, CreateEngineFunction> (engineName, createEngineFunction));
}

std::unique_ptr<NumericalPricingEngine> NumericalPricingEngineFactory::createEngine(
    std::string engineName,
    const Wrapper<Option>& theOption,
    double vol,
    double r,
    double div){
    std::map<std::string, CreateEngineFunction>::iterator it = theCreatorFunctions.find(engineName);
    if (it == theCreatorFunctions.end()){
        std::cout << "Engine name not found! "<< std::endl;
    }
    return (it->second)(theOption, vol, r, div);
}

std::vector<std::string> NumericalPricingEngineFactory::getEngineNames() const{
    std::vector<std::string> engineNames;
    for (const auto& pair : theCreatorFunctions){
        engineNames.push_back(pair.first);
    }
    return engineNames;
}