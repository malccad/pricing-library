#ifndef BINOMIAL_PRICING_H
#define BINOMIAL_PRICING_H

#include "wrapper.h"
#include "option.h"
#include <vector>

// double getBinomialPrice(
//     double spot,
//     const Wrapper<Option>& theOption,
//     double vol,
//     double r,
//     double div,
//     unsigned long numBinomialTimeSteps
// );

// std::vector<std::vector<double>> _getAssetPrices(
//     double upFactor,
//     double downFactor,
//     double onePeriodDividend
// );

// std::vector<double> _getFinalPayOff(
//     std::vector<double> finalAssetPrices,
//     const Wrapper<Option>& theOption
// );

class BinomialPricingEngine
{
public:
    BinomialPricingEngine(
        double spot,
        const Wrapper<Option>& theOption,
        double vol,
        double r,
        double div,
        unsigned long numBinomialTimeSteps
        );
    double getOptionPrice() const;
private:
    double spot;
    Wrapper<Option> theOption;
    double vol;
    double r;
    double div;
    unsigned long numBinomialTimeSteps;
    double dt;
    std::vector<std::vector<double>> optionPriceTree;
    std::vector<std::vector<double>> assetPriceTree;
    void _computeOptionPriceTree(
        double p,
        double q,
        double onePeriodInterest
        );
    void _computeAssetPriceTree(
        double upFactor,
        double downFactor,
        double onePeriodDividend
    );
    void _computeFinalPayOff();
};
#endif