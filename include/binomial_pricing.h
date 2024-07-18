#ifndef BINOMIAL_PRICING_H
#define BINOMIAL_PRICING_H

#include "wrapper.h"
#include "european_option.h"
#include <vector>

double getBinomialPrice(
    double spot,
    const Wrapper<EuropeanOption>& theOption,
    double vol,
    double r,
    unsigned long numBinomialTimeSteps
);

std::vector<double> _getFinalAssetPrices(
    double upFactor,
    double downFactor,
    double spot,
    unsigned long numBinomialTimeSteps
);

std::vector<double> _getFinalPayOff(
    std::vector<double> finalAssetPrices,
    const Wrapper<EuropeanOption>& theOption
);
#endif