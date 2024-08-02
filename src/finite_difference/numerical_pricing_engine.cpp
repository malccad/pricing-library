#include "../../include/finite_difference/numerical_pricing_engine.h"

NumericalPricingEngine::NumericalPricingEngine(
    const Wrapper<Option>& theOption,
        double vol,
        double r,
        double div
)
    :theOption(theOption),
    vol(vol),
    r(r),
    div(div)
{}

double NumericalPricingEngine::getOptionPrice(double spot){
    std::vector<double>::iterator it = std::upper_bound(assetPrices.begin(), assetPrices.end(), spot);
    if (it - 1 >= assetPrices.begin() && it < assetPrices.end()){
        int index = std::distance(assetPrices.begin(), it);
        return (optionPrices[index] -optionPrices[index-1])*(spot - *(it-1))/(*it - *(it-1)) + optionPrices[index-1];
    } else {
        throw std::runtime_error("The value of spot is out of range!");
    }
}

void NumericalPricingEngine::_computeAssetPrices(
    double lowerLimit,
    double dS,
    unsigned long numAssetStep
){
    assetPrices.resize(numAssetStep);
    for (int i=0; i<numAssetStep; ++i){
        assetPrices[i] = lowerLimit + dS*i;
    }
}