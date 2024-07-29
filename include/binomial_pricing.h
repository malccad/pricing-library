#ifndef BINOMIAL_PRICING_H
#define BINOMIAL_PRICING_H

#include "wrapper.h"
#include "option.h"
#include <vector>

double getBinomialPrice(
    double spot,
    const Wrapper<Option>& theOption,
    double vol,
    double r,
    double div,
    unsigned long numBinomialTimeSteps
);

std::vector<std::vector<double>> _getAssetPrices(
    double upFactor,
    double downFactor,
    double spot,
    double onePeriodDividend,
    unsigned long numBinomialTimeSteps
);

std::vector<double> _getFinalPayOff(
    std::vector<double> finalAssetPrices,
    const Wrapper<Option>& theOption
);
#endif