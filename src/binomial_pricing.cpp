#include "../include/binomial_pricing.h"
#include <cmath>

double getBinomialPrice(
    double spot,
    const Wrapper<EuropeanOption>& theOption,
    double vol,
    double r,
    double div,
    unsigned long numBinomialTimeSteps
){
    double expiry = theOption->getExpiry();
    double upFactor = exp(vol/sqrt(numBinomialTimeSteps/expiry));
    double downFactor = exp(-vol/sqrt(numBinomialTimeSteps/expiry));
    double onePeriodInterest = r*expiry/numBinomialTimeSteps;
    double onePeriodDividend = div*expiry/numBinomialTimeSteps;
    // risk neutral probability
    double p = (1+onePeriodInterest- downFactor)/(upFactor - downFactor);
    double q = (upFactor - (1+onePeriodInterest))/(upFactor - downFactor);

    std::vector<double> finalAssetPrices = _getFinalAssetPrices(upFactor, downFactor, spot, onePeriodDividend, numBinomialTimeSteps);
    std::vector<double> curOptionPrices = _getFinalPayOff(finalAssetPrices, theOption);
    for (int i=numBinomialTimeSteps-1; i>=0; --i){
        std::vector<double> tempOptionPrices;
        for (int j=0; j<i+1; ++j){
            double price = (q*curOptionPrices[j] +p*curOptionPrices[j+1]) /(1+onePeriodInterest);
            tempOptionPrices.push_back(price);
        }
        curOptionPrices = tempOptionPrices;
    }
    return curOptionPrices[0];
}

std::vector<double> _getFinalAssetPrices(
    double upFactor,
    double downFactor,
    double spot,
    double onePeriodDividend,
    unsigned long numBinomialTimeSteps
){
    std::vector<double> finalAssetPrices;
    double dividendFactor = pow(1-onePeriodDividend, numBinomialTimeSteps);
    for (int i=0; i<numBinomialTimeSteps+1; ++i){
        double finalAssetPrice = dividendFactor*spot*pow(downFactor, numBinomialTimeSteps - i)*pow(upFactor, i);
        finalAssetPrices.push_back(finalAssetPrice);
    }
    return finalAssetPrices;
}

std::vector<double> _getFinalPayOff(
    std::vector<double> finalAssetPrices,
    const Wrapper<EuropeanOption>& theOption
){
    std::vector<double> finalOptionPrices;
    for (double assetPrice :finalAssetPrices){
        double thisPayOff = theOption->getPayOff(assetPrice);
        finalOptionPrices.push_back(thisPayOff);
    }
    return finalOptionPrices;
}