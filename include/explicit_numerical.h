#ifndef EXPLICIT_NUMERICAL_H
#define EXPLICIT_NUMERICAL_H

#include "numerical_pricing_engine.h"

class Explicit: public NumericalPricingEngine
{
public:
    Explicit(
        const Wrapper<EuropeanOption>& theOption,
        double vol,
        double r,
        double div
        );
    
    void buildModel(
        unsigned long numAssetStep,
        unsigned long numTimeStep,
        double upperLimit
        ) override;

    virtual ~Explicit(){}
private:
    void _stabilityCheck(double dt, unsigned long numAssetStep);
};
#endif