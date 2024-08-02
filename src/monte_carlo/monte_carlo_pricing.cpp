#include <cmath>
#include "../../include/monte_carlo/monte_carlo_pricing.h"
#include "../../include/gaussian/gaussian_generator.h"

// double getMonteCarloPrice(
//     double spot,
//     const Wrapper<Option>& theOption,
//     double vol,
//     double r,
//     double div,
//     unsigned long numPaths
// ){
//     double expiry = theOption->getExpiry();
//     double movedSpot = spot*exp((r-div-0.5*vol*vol)*expiry);
//     double sumPayOffs = 0;
//     GaussianGenerator generator = GaussianGenerator();
//     for (unsigned long i=0; i<numPaths; ++i){
//         double rand = generator.getGaussian();
//         double thisFinalSpot = movedSpot*exp(vol*sqrt(expiry)*rand);
//         double thisPayOff = theOption->getPayOff(thisFinalSpot);
//         sumPayOffs += thisPayOff;
//     }
//     double discountFactor = exp(-r*expiry);
//     return discountFactor*sumPayOffs/numPaths;
// }

MonteCarloPricingEngine::MonteCarloPricingEngine(
    double spot_,
    const Wrapper<Option>& theOption_,
    double vol_,
    double r_,
    double div_,
    unsigned long numPaths_
)
    :spot(spot_),
    theOption(theOption_),
    vol(vol_),
    r(r_),
    div(div_),
    numPaths(numPaths_)
{
    double expiry = theOption->getExpiry();
    double movedSpot = spot*exp((r-div-0.5*vol*vol)*expiry);
    double discountFactor = exp(-r*expiry);
    GaussianGenerator generator = GaussianGenerator();
    for (unsigned long i=0; i<numPaths; ++i){
        double rand = generator.getGaussian();
        double thisFinalSpot = movedSpot*exp(vol*sqrt(expiry)*rand);
        double thisPayOff = theOption->getPayOff(thisFinalSpot);
        discountedPayOffs.push_back(discountFactor*thisPayOff);
    }
}

double MonteCarloPricingEngine::getOptionPrice() const
{
    double sumPayOffs = 0.0;
    for (double p: discountedPayOffs){
        sumPayOffs += p;
    }
    return sumPayOffs/numPaths;
}

double MonteCarloPricingEngine::getStandardErrorOfMean() const
{
    double mean = getOptionPrice();
    double var = 0.0;
    for (double p: discountedPayOffs){
        var += (p-mean)*(p-mean);
    }
    var /= numPaths;
    return sqrt(var/numPaths);
}