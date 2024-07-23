#ifndef NUMERICAL_PRICING_ENGINE_H
#define NUMERICAL_PRICING_ENGINE_H

#include "wrapper.h"
#include "option.h"

#include <tuple>
#include <vector>
#include <map>
#include <string>

class NumericalPricingEngine
{
public:
    NumericalPricingEngine(
        const Wrapper<Option>& theOption,
        double vol,
        double r,
        double div
        );
    
    virtual void buildModel(
        unsigned long numAssetStep,
        unsigned long numTimeStep,
        double upperLimit
        )=0;
    
    // linear interpolation to get option price at spot.
    double getOptionPrice(double spot);

    virtual ~NumericalPricingEngine(){};

protected:
    Wrapper<Option> theOption;
    double vol;
    double r;
    double div;
    std::vector<double> optionPrices;
    std::vector<double> assetPrices;

    void _computeAssetPrices(
        double lowerLimit,
        double dS,
        unsigned long numAssetStep
    );

};
#endif