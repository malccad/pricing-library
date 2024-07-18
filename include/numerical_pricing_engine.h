#ifndef NUMERICAL_PRICING_ENGINE_H
#define NUMERICAL_PRICING_ENGINE_H

#include "wrapper.h"
#include "european_option.h"

#include <tuple>
#include <vector>
#include <map>
#include <string>

class NumericalPricingEngine
{
public:
    NumericalPricingEngine(
        const Wrapper<EuropeanOption>& theOption,
        double vol,
        double r
        );
    
    virtual void buildModel(
        unsigned long numAssetStep,
        unsigned long numTimeStep,
        double upperLimit
        )=0;
    
    double getOptionPrice(double spot);

    virtual ~NumericalPricingEngine(){};

protected:
    Wrapper<EuropeanOption> theOption;
    double vol;
    double r;
    std::vector<double> optionPrices;
    std::vector<double> assetPrices;

    void _computeAssetPrices(
        double lowerLimit,
        double dS,
        unsigned long numAssetStep
    );

};
#endif