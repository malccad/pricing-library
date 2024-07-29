#include "../include/binomial_pricing.h"
#include <cmath>
#include <algorithm>

double getBinomialPrice(
    double spot,
    const Wrapper<Option>& theOption,
    double vol,
    double r,
    double div,
    unsigned long numBinomialTimeSteps
){
    Option::OptionType optionType = theOption->getOptionType();
    double expiry = theOption->getExpiry();
    double upFactor = exp(vol/sqrt(numBinomialTimeSteps/expiry));
    double downFactor = exp(-vol/sqrt(numBinomialTimeSteps/expiry));
    double onePeriodInterest = r*expiry/numBinomialTimeSteps;
    double onePeriodDividend = div*expiry/numBinomialTimeSteps;
    // risk neutral probability
    double p = (1+onePeriodInterest- downFactor)/(upFactor - downFactor);
    double q = (upFactor - (1+onePeriodInterest))/(upFactor - downFactor);

    std::vector<std::vector<double>> assetPrices = _getAssetPrices(upFactor, downFactor, spot, onePeriodDividend, numBinomialTimeSteps);
    std::vector<double> curOptionPrices = _getFinalPayOff(assetPrices[numBinomialTimeSteps], theOption);
    for (int i=numBinomialTimeSteps-1; i>=0; --i){
        std::vector<double> tempOptionPrices;
        for (int j=0; j<i+1; ++j){
            double price = (q*curOptionPrices[j] +p*curOptionPrices[j+1]) /(1+onePeriodInterest);
            if (optionType == Option::american){
                price = std::max(price, theOption->getPayOff(assetPrices[i][j]));
            }
            tempOptionPrices.push_back(price);
        }
        curOptionPrices = tempOptionPrices;
    }
    return curOptionPrices[0];
}

std::vector<std::vector<double>> _getAssetPrices(
    double upFactor,
    double downFactor,
    double spot,
    double onePeriodDividend,
    unsigned long numBinomialTimeSteps
){
    std::vector<std::vector<double>> assetPrices {{spot}};
    for (int i=1; i<numBinomialTimeSteps+1; ++i){
        std::vector<double> curAssetPrices;
        for (int j=0; j<i; ++j){
            curAssetPrices.push_back(assetPrices[i-1][j]*downFactor*(1-onePeriodDividend));
        }
        curAssetPrices.push_back(assetPrices[i-1][i-1]*upFactor*(1-onePeriodDividend));
        assetPrices.push_back(curAssetPrices);
    }
    return assetPrices;
}

std::vector<double> _getFinalPayOff(
    const std::vector<double> finalAssetPrices,
    const Wrapper<Option>& theOption
){
    std::vector<double> finalOptionPrices;
    for (double assetPrice :finalAssetPrices){
        double thisPayOff = theOption->getPayOff(assetPrice);
        finalOptionPrices.push_back(thisPayOff);
    }
    return finalOptionPrices;
}