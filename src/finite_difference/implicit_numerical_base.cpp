#include "../../include/finite_difference/implicit_numerical_base.h"
#include "../../include/finite_difference/matrix_solver.h"

ImplicitBase::ImplicitBase(
    const Wrapper<Option>& theOption,
    double vol,
    double r,
    double div
):NumericalPricingEngine(theOption, vol, r, div)
{}
void ImplicitBase::buildModel(
    unsigned long numAssetStep,
    unsigned long numTimeStep,
    double upperLimit
){
    Option::OptionType optionType = theOption->getOptionType();
    double lowerLimit = 0.0;

    double expiry = theOption->getExpiry();
    double dS = (upperLimit - lowerLimit)/(numAssetStep-1);
    double dt = expiry/numTimeStep;

    double v1 = dt/(dS*dS);
    double v2 = dt/dS;

    _computeAssetPrices(lowerLimit, dS, numAssetStep);

    std::vector<double> curOptionPrices(numAssetStep);
    for (int i=0; i<numAssetStep; ++i){
        curOptionPrices[i] = theOption->getPayOff(assetPrices[i]);
    }

    std::map<std::string, std::vector<double>> triDiagonalMatrix = _getTriDiagonalMatrix(
        assetPrices, v1, v2, vol, r, div, dt);
    
    for (int k=1; k<numTimeStep+1; ++k){

        std::vector<double> target = _getTarget(curOptionPrices, assetPrices, v1, v2, vol, r, div, dt);

        std::map<std::string, std::vector<double>> curTriDiagonalMatrix(triDiagonalMatrix);

        _addBoundaryConditionsToSystem(
            target, curTriDiagonalMatrix, curOptionPrices, assetPrices, vol, v1, v2, r, div, dt
        );

        std::vector<double> v = triDiagonalSolver(target, curTriDiagonalMatrix);

        for (int i =1; i< numAssetStep-1; ++i){
            curOptionPrices[i] = v[i-1];
        }
        _updateBoundary(curOptionPrices, r, div, dt);

        if (optionType == Option::american){
            for (int i=0; i<numAssetStep; ++i){
                curOptionPrices[i] = std::max(curOptionPrices[i], theOption->getPayOff(assetPrices[i]));
            }
        }
    }
    optionPrices = curOptionPrices;
}