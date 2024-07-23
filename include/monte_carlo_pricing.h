#ifndef MONTE_CARLO_PRICING_H
#define MONTE_CARLO_PRICING_H

#include "wrapper.h"
#include "option.h"

double getMonteCarloPrice(
    double spot,
    const Wrapper<Option>& theOption,
    double vol,
    double r,
    double div,
    unsigned long numPaths
);

#endif