#ifndef MONTE_CARLO_PRICING_H
#define MONTE_CARLO_PRICING_H

#include "wrapper.h"
#include "european_option.h"

double getMonteCarloPrice(
    double spot,
    const Wrapper<EuropeanOption>& theOption,
    double vol,
    double r,
    double div,
    unsigned long numPaths
);

#endif