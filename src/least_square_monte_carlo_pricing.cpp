#include <cmath>
#include <utility>
#include <numeric>
#include <iostream>
#include "../include/least_square_monte_carlo_pricing.h"
#include "../include/monte_carlo_pricing.h"
#include "../include/gaussian_generator.h"
#include "../include/laguerre.h"
#include "../include/linear_regression.h"
#include "../include/minmax_scaler.h"

double getLeastSquareMonteCarloPrice(
    double spot,
    const Wrapper<Option>& theOption,
    double vol,
    double r,
    double div,
    unsigned long numPaths,
    unsigned long numBasisFunctions,
    unsigned long numTimeSteps
){
    double expiry = theOption->getExpiry();
    MultiDimGaussianGenerator generator(numTimeSteps-1);
    std::vector<std::vector<double>> assetPricePaths;
    double dt = expiry/(numTimeSteps-1);
    double drift = exp((r-div-0.5*vol*vol)*dt);
    for (int i=0; i<numPaths; ++i){
        std::vector<double> curPricePath {spot};
        std::vector<double> gaussians = generator.getGaussian();
        for (int t=1; t<numTimeSteps; t++){
            curPricePath.push_back(curPricePath[t - 1]*drift*exp(vol*sqrt(dt)*gaussians[t-1]));
            }
        assetPricePaths.push_back(curPricePath);
    }

    std::pair<std::vector<double>, std::vector<unsigned long>> cashFlowAtTime;
    for (int i=0; i<numPaths; ++i){
        cashFlowAtTime.first.push_back(theOption->getPayOff(assetPricePaths[i][numTimeSteps-1]));
        cashFlowAtTime.second.push_back(numTimeSteps - 1);

    }

    Laguerre laguerre(numBasisFunctions);
    for (int t=numTimeSteps-2; t>=0;--t){
        std::tuple<std::vector<double>, std::vector<double>, std::vector<unsigned long>> inTheMoneyTuple = _getInTheMoneyTuple(theOption, assetPricePaths, t);
        std::vector<double>& inTheMoneyAssetPrices = std::get<0>(inTheMoneyTuple);
        std::vector<double>& inTheMoneyPayOffs = std::get<1>(inTheMoneyTuple);
        std::vector<unsigned long>& inTheMoneyIndices = std::get<2>(inTheMoneyTuple);

        if (inTheMoneyIndices.size() == 0){
            continue;
        }
        std::vector<double> discountedContValues = _getDiscountedContValues(inTheMoneyIndices, cashFlowAtTime, r, dt, t);
        
        MinMaxScaler minMaxScaler;
        minMaxScaler.fit(inTheMoneyAssetPrices);
        std::vector<double> scaledInTheMoneyAssetPrices = minMaxScaler.transform(inTheMoneyAssetPrices);
        
        std::vector<std::vector<double>> features;
        for (double price: scaledInTheMoneyAssetPrices){
            std::vector<double> featuresForOneExample = laguerre(price);
            features.push_back(featuresForOneExample);
            
        }
        LinearRegression regressor;
        regressor.fit(features, discountedContValues);
        std::vector<double> predDiscountedContValues = regressor.predict(features);
        _updateCashFlowAtTime(cashFlowAtTime, inTheMoneyIndices, inTheMoneyPayOffs, predDiscountedContValues, t);
    }
    std::vector<double> discountedCashFlow = _getDiscountedCashFlow(cashFlowAtTime, r, dt);
    return _getMean(discountedCashFlow);
}


std::tuple<std::vector<double>, std::vector<double>, std::vector<unsigned long>> _getInTheMoneyTuple(
    const Wrapper<Option>& theOption, const std::vector<std::vector<double>>& assetPricePaths, unsigned long t
){
    std::vector<double> outAssetPrices;
    std::vector<double> outPayOffs;
    std::vector<unsigned long> outIndices;
    
    for (int i=0; i<assetPricePaths.size(); ++i){
        double assetPrice = assetPricePaths[i][t];
        double curPayOff = theOption->getPayOff(assetPrice);
        if (curPayOff > 0.0){
            outAssetPrices.push_back(assetPrice);
            outPayOffs.push_back(curPayOff);
            outIndices.push_back(i);
        }
    }
    return std::make_tuple(outAssetPrices, outPayOffs, outIndices);
}


std::vector<double> _getDiscountedContValues(
    const std::vector<unsigned long>& inTheMoneyIndices,
    const std::pair<std::vector<double>, std::vector<unsigned long>>& cashFlowAtTime,
    double r,
    double dt,
    unsigned long t)
{
    std::vector<double> discountedContValues;
    for (int ind: inTheMoneyIndices){
        unsigned long timeStep = cashFlowAtTime.second[ind];
        double discountFactor = exp(-r*dt*(timeStep - t));
        discountedContValues.push_back(discountFactor*cashFlowAtTime.first[ind]);
    }
    return discountedContValues;
}

void _updateCashFlowAtTime(
    std::pair<std::vector<double>, std::vector<unsigned long>>& cashFlowAtTime,
    const std::vector<unsigned long>& inTheMoneyIndices,
    const std::vector<double>& inTheMoneyPayOffs,
    const std::vector<double>& predDiscountedContValues,
    unsigned long t
){
    for (int i=0; i<inTheMoneyIndices.size(); ++i){
        if (inTheMoneyPayOffs[i] > predDiscountedContValues[i]){
            unsigned long curInd = inTheMoneyIndices[i];
            cashFlowAtTime.first[curInd] = inTheMoneyPayOffs[i];
            cashFlowAtTime.second[curInd] = t;
        }
    }
}

std::vector<double> _getDiscountedCashFlow(const std::pair<std::vector<double>, std::vector<unsigned long>>& cashFlowAtTime, double r, double dt){
    std::vector<double> discountedCashFlow;
    for (int i=0; i<cashFlowAtTime.first.size(); ++i){
        discountedCashFlow.push_back(cashFlowAtTime.first[i]*exp(-r*dt*cashFlowAtTime.second[i]));
    }
    return discountedCashFlow;
}

double _getMean(const std::vector<double>& v){
    double s = 0.0;
    for (double x: v){
        s += x;
    }
    return s/v.size();
}