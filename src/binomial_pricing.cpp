#include "../include/binomial_pricing.h"
#include <cmath>
#include <algorithm>

// double getBinomialPrice(
//     double spot,
//     const Wrapper<Option>& theOption,
//     double vol,
//     double r,
//     double div,
//     unsigned long numBinomialTimeSteps
// ){
//     Option::OptionType optionType = theOption->getOptionType();
//     double expiry = theOption->getExpiry();
//     double upFactor = exp(vol/sqrt(numBinomialTimeSteps/expiry));
//     double downFactor = exp(-vol/sqrt(numBinomialTimeSteps/expiry));
//     double onePeriodInterest = r*expiry/numBinomialTimeSteps;
//     double onePeriodDividend = div*expiry/numBinomialTimeSteps;
//     // risk neutral probability
//     double p = (1+onePeriodInterest- downFactor)/(upFactor - downFactor);
//     double q = (upFactor - (1+onePeriodInterest))/(upFactor - downFactor);

//     std::vector<std::vector<double>> assetPrices = _getAssetPrices(upFactor, downFactor, spot, onePeriodDividend, numBinomialTimeSteps);
//     std::vector<double> curOptionPrices = _getFinalPayOff(assetPrices[numBinomialTimeSteps], theOption);
//     for (int i=numBinomialTimeSteps-1; i>=0; --i){
//         std::vector<double> tempOptionPrices;
//         for (int j=0; j<i+1; ++j){
//             double price = (q*curOptionPrices[j] +p*curOptionPrices[j+1]) /(1+onePeriodInterest);
//             if (optionType == Option::american){
//                 price = std::max(price, theOption->getPayOff(assetPrices[i][j]));
//             }
//             tempOptionPrices.push_back(price);
//         }
//         curOptionPrices = tempOptionPrices;
//     }
//     return curOptionPrices[0];
// }

// std::vector<std::vector<double>> _getAssetPrices(
//     double upFactor,
//     double downFactor,
//     double spot,
//     double onePeriodDividend,
//     unsigned long numBinomialTimeSteps
// ){
//     std::vector<std::vector<double>> assetPrices {{spot}};
//     for (int i=1; i<numBinomialTimeSteps+1; ++i){
//         std::vector<double> curAssetPrices;
//         for (int j=0; j<i; ++j){
//             curAssetPrices.push_back(assetPrices[i-1][j]*downFactor*(1-onePeriodDividend));
//         }
//         curAssetPrices.push_back(assetPrices[i-1][i-1]*upFactor*(1-onePeriodDividend));
//         assetPrices.push_back(curAssetPrices);
//     }
//     return assetPrices;
// }

// std::vector<double> _getFinalPayOff(
//     const std::vector<double> finalAssetPrices,
//     const Wrapper<Option>& theOption
// ){
//     std::vector<double> finalOptionPrices;
//     for (double assetPrice :finalAssetPrices){
//         double thisPayOff = theOption->getPayOff(assetPrice);
//         finalOptionPrices.push_back(thisPayOff);
//     }
//     return finalOptionPrices;
// }

BinomialPricingEngine::BinomialPricingEngine(
    double spot_,
    const Wrapper<Option>& theOption_,
    double vol_,
    double r_,
    double div_,
    unsigned long numBinomialTimeSteps_)
    :
    spot(spot_),
    theOption(theOption_),
    vol(vol_),
    r(r_),
    div(div_),
    numBinomialTimeSteps(numBinomialTimeSteps_),
    optionPriceTree(numBinomialTimeSteps+1),
    assetPriceTree(numBinomialTimeSteps+1)
{
    double expiry = theOption->getExpiry();
    dt = expiry/numBinomialTimeSteps;
    double upFactor = exp(vol*sqrt(dt));
    double downFactor = exp(-vol*sqrt(dt));
    double onePeriodInterest = r*dt;
    double onePeriodDividend = div*dt;
    // risk neutral probability
    double p = (1+onePeriodInterest- downFactor)/(upFactor - downFactor);
    double q = (upFactor - (1+onePeriodInterest))/(upFactor - downFactor);

    _computeAssetPriceTree(upFactor, downFactor, onePeriodDividend);
    _computeOptionPriceTree(p, q, onePeriodInterest);
}

void BinomialPricingEngine::_computeAssetPriceTree(
    double upFactor,
    double downFactor,
    double onePeriodDividend
){
    assetPriceTree[0].push_back(spot);
    for (int t=1; t<numBinomialTimeSteps+1; ++t){
        for (int j=0; j<t; ++j){
            assetPriceTree[t].push_back(assetPriceTree[t-1][j]*downFactor*(1-onePeriodDividend));
        }
        assetPriceTree[t].push_back(assetPriceTree[t-1][t-1]*upFactor*(1-onePeriodDividend));
    }
}

void BinomialPricingEngine::_computeFinalPayOff(){
    for (double assetPrice :assetPriceTree[numBinomialTimeSteps]){
        double thisPayOff = theOption->getPayOff(assetPrice);
        optionPriceTree[numBinomialTimeSteps].push_back(thisPayOff);
    }
}

void BinomialPricingEngine::_computeOptionPriceTree(
    double p,
    double q,
    double onePeriodInterest
){
    Option::OptionType optionType = theOption->getOptionType();
    // set final time step of option price tree
    _computeFinalPayOff();
    for (int t=numBinomialTimeSteps-1; t>=0; --t){
        for (int j=0; j<t+1; ++j){
            double price = (q*optionPriceTree[t+1][j] +p*optionPriceTree[t+1][j+1]) /(1+onePeriodInterest);
            if (optionType == Option::american){
                price = std::max(price, theOption->getPayOff(assetPriceTree[t][j]));
            }
            optionPriceTree[t].push_back(price);
        }
    }
}

double BinomialPricingEngine::getOptionPrice() const
{
    return optionPriceTree[0][0];
}