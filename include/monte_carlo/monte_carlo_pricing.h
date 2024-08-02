#ifndef MONTE_CARLO_PRICING_H
#define MONTE_CARLO_PRICING_H

#include "../utils/wrapper.h"
#include "../option/option.h"

// double getMonteCarloPrice(
//     double spot,
//     const Wrapper<Option>& theOption,
//     double vol,
//     double r,
//     double div,
//     unsigned long numPaths
// );

class MonteCarloPricingEngine
{
public:
    MonteCarloPricingEngine(
        double spot_,
        const Wrapper<Option>& theOption_,
        double vol_,
        double r_,
        double div_,
        unsigned long numPaths_
    );

    double getOptionPrice() const;
    double getStandardErrorOfMean() const;
private:
    double spot;
    Wrapper<Option> theOption;
    double vol;
    double r;
    double div;
    unsigned long numPaths;
    std::vector<double> discountedPayOffs;
};

#endif