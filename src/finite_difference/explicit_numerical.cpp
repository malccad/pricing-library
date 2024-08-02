#include "../../include/finite_difference/explicit_numerical.h"
#include <iostream>
#include <algorithm>

Explicit::Explicit(
    const Wrapper<Option>& theOption,
    double vol,
    double r,
    double div
): NumericalPricingEngine(
    theOption,
    vol,
    r,
    div
)
{}

void Explicit::buildModel(
    unsigned long numAssetStep,
    unsigned long numTimeStep,
    double upperLimit
){
    Option::OptionType optionType = theOption->getOptionType();
    double lowerLimit = 0.0;
    
    double dS = (upperLimit - lowerLimit)/(numAssetStep-1);
    double dt = theOption->getExpiry()/numTimeStep;

    _stabilityCheck(dt, numAssetStep);
    _computeAssetPrices(lowerLimit, dS, numAssetStep);
    std::vector<double> curOptionPrices(numAssetStep);

    for (int i=0; i<assetPrices.size(); ++i){
        curOptionPrices[i] = theOption->getPayOff(assetPrices[i]);
    }

    std::vector<double> tempOptionPrices(numAssetStep-2);

    for (int k=1; k<numTimeStep+1; ++k){
        for (int i=1; i<numAssetStep -1; ++i){
            double delta = (curOptionPrices[i+1] - curOptionPrices[i-1])/(2*dS);
            double gamma = (curOptionPrices[i+1] -2*curOptionPrices[i] + curOptionPrices[i-1])/(dS*dS);
            double theta = -0.5*vol*vol*assetPrices[i]*assetPrices[i]*gamma - (r-div)*assetPrices[i]*delta + r*curOptionPrices[i];
            tempOptionPrices[i-1] = curOptionPrices[i] - dt*theta;
        }

        for (int i=1; i<numAssetStep -1; ++i){
            curOptionPrices[i] = tempOptionPrices[i-1];
        }
        curOptionPrices[0] = curOptionPrices[0]*(1- r*dt);
        curOptionPrices[numAssetStep - 1] = 2*curOptionPrices[numAssetStep-2] - curOptionPrices[numAssetStep -3];
        if (optionType == Option::american){
            for (int i=0; i<numAssetStep; ++i){
                curOptionPrices[i] = std::max(curOptionPrices[i], theOption->getPayOff(assetPrices[i]));
            }
        }
    }
    optionPrices = curOptionPrices;
}

void Explicit::_stabilityCheck(double dt, unsigned long numAssetStep){
    double stability_coef = dt*vol*vol*(numAssetStep-1)*(numAssetStep-1);
    std::cout << "Stability coefficient (should be <= 1): " << stability_coef << std::endl;
    if (stability_coef <= 1){
        std::cout << "The scheme is stable" << std::endl;
    }
    else {
        std::cout << "The scheme is not stable! Increase the number of time steps or decrease the number of asset steps." << std::endl;
    }
}