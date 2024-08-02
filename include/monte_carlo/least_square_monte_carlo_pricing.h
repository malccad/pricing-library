#ifndef LEAST_SQUARE_MONTE_CARLO_PRICING_H
#define LEAST_SQUARE_MONTE_CARLO_PRICING_H

#include "../option/option.h"
#include "../utils/wrapper.h"
#include "laguerre.h"

// double getLeastSquareMonteCarloPrice(
//     double spot,
//     const Wrapper<Option>& theOption,
//     double vol,
//     double r,
//     double div,
//     unsigned long numPaths,
//     unsigned long numBasisFunctions,
//     unsigned long numTimeSteps
// );

// std::tuple<std::vector<double>, std::vector<double>, std::vector<unsigned long>> _getInTheMoneyTuple(
//     const Wrapper<Option>& theOption, const std::vector<std::vector<double>>& assetPricePaths, unsigned long t
// );
// // Discounted continuation values for in the money paths at time step t
// std::vector<double> _getDiscountedContValues(
//     const std::vector<unsigned long>& inTheMoneyIndices,
//     const std::pair<std::vector<double>, std::vector<unsigned long>>& cashFlowAtTime,
//     double r,
//     double dt,
//     unsigned long t);

// void _updateCashFlowAtTime(
//     std::pair<std::vector<double>, std::vector<unsigned long>>& cashFlowAtTime,
//     const std::vector<unsigned long>& inTheMoneyIndices,
//     const std::vector<double>& inTheMoneyPayOffs,
//     const std::vector<double>& predDiscountedContValues,
//     unsigned long t
//     );

// std::vector<double> _getDiscountedCashFlow(const std::pair<std::vector<double>, std::vector<unsigned long>>& cashFlowAtTime, double r, double dt);
// double _getMean(const std::vector<double>& v);

class LeastSquareMonteCarloPricingEngine
{
public:
    LeastSquareMonteCarloPricingEngine(
        double spot_,
        const Wrapper<Option>& theOption_,
        double vol_,
        double r_,
        double div_,
        unsigned long numPaths_,
        unsigned long numBasisFunctions_,
        unsigned long numTimeSteps_
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
    unsigned long numBasisFunctions;
    unsigned long numTimeSteps;

    double dt;
    std::vector<std::vector<double>> assetPricePaths;
    std::vector<double> discountedCashFlows;

    void _generateAssetPricePaths();
    std::pair<std::vector<double>, std::vector<unsigned long>> _initCashFlowAtTime();
    // in the money paths at time t
    std::tuple<std::vector<double>, std::vector<double>, std::vector<unsigned long>> _getInTheMoneyTuple(unsigned long t) const;
    
    // Discounted continuation values for in the money paths at time step t
    std::vector<double> _getDiscountedContValues(
        const std::pair<std::vector<double>, std::vector<unsigned long>>& cashFlowAtTime,
        const std::vector<unsigned long>& inTheMoneyIndices,
        unsigned long t) const;

    std::vector<std::vector<double>> _transformITMAssetPricesToFeatures(
        const std::vector<double>& inTheMoneyAssetPrices,
        const Laguerre& laguerre) const;

    void _updateCashFlowAtTime(
        std::pair<std::vector<double>, std::vector<unsigned long>>& cashFlowAtTime,
        const std::vector<unsigned long>& inTheMoneyIndices,
        const std::vector<double>& inTheMoneyPayOffs,
        const std::vector<double>& predDiscountedContValues,
        unsigned long t
        );

    void _computeDiscountedCashFlows(const std::pair<std::vector<double>, std::vector<unsigned long>>& cashFlowAtTime, double r, double dt);
};
#endif
