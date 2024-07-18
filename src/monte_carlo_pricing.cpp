#include <cmath>
#include "../include/monte_carlo_pricing.h"
#include "../include/gaussian_generator.h"

double getMonteCarloPrice(
    double spot,
    const Wrapper<EuropeanOption>& theOption,
    double vol,
    double r,
    unsigned long numPaths
){
    double expiry = theOption->getExpiry();
    double movedSpot = spot*exp((r-0.5*vol*vol)*expiry);
    double sumPayOffs = 0;
    GaussianGenerator generator = GaussianGenerator();
    for (unsigned long i=0; i<numPaths; ++i){
        double rand = generator.getGaussian();
        double thisFinalSpot = movedSpot*exp(vol*sqrt(expiry)*rand);
        double thisPayOff = theOption->getPayOff(thisFinalSpot);
        sumPayOffs += thisPayOff;
    }
    double discountFactor = exp(-r*expiry);
    return discountFactor*sumPayOffs/numPaths;
}
