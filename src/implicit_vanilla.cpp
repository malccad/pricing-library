#include "../include/implicit_vanilla.h"
#include "../include/matrix_solver.h"

Implicit::Implicit(
    const Wrapper<EuropeanOption>& theOption,
    double vol,
    double r
):ImplicitBase(theOption, vol, r)
{}

// void Implicit::buildModel(
//     unsigned long numAssetStep,
//     unsigned long numTimeStep,
//     double upperLimit
// ){
//     double lowerLimit = 0.0;

//     double expiry = theOption->getExpiry();
//     double dS = (upperLimit - lowerLimit)/(numAssetStep-1);
//     double dt = expiry/(numTimeStep-1);

//     double v1 = dt/(dS*dS);
//     double v2 = dt/dS;

//     _computeAssetPrices(lowerLimit, dS, numAssetStep);

//     std::vector<double> curOptionPrices(numAssetStep);
//     for (int i=0; i<numAssetStep; ++i){
//         curOptionPrices[i] = theOption->getPayOff(assetPrices[i]);
//     }

//     std::map<std::string, std::vector<double>> triDiagonalMatrix = _getTriDiagonalMatrix(
//         assetPrices, v1, v2, vol, r, dt);
    
//     for (int k=1; k<numTimeStep; ++k){

//         std::vector<double> target = _getTarget(curOptionPrices);

//         std::map<std::string, std::vector<double>> curTriDiagonalMatrix(triDiagonalMatrix);

//         _addBoundaryConditionsToSystem(
//             target, curTriDiagonalMatrix, curOptionPrices, assetPrices, vol, v1, v2, r, dt
//         );

//         std::vector<double> v = triDiagonalSolver(target, curTriDiagonalMatrix);

//         for (int i =1; i< numAssetStep-1; ++i){
//             curOptionPrices[i] = v[i-1];
//         }
//         _updateBoundary(curOptionPrices, r, dt);
//     }
//     optionPrices = curOptionPrices;
// }

std::map<std::string, std::vector<double>> Implicit::_getTriDiagonalMatrix(
    const std::vector<double>& assetPrices,
    double v1,
    double v2,
    double vol,
    double r,
    double dt
) const {
    unsigned long numAssetStep = assetPrices.size();
    std::map<std::string, std::vector<double>> triDiagonalMatrix;
    triDiagonalMatrix["diag"] = std::vector<double>(numAssetStep-2);
    triDiagonalMatrix["superDiag"] = std::vector<double>(numAssetStep-3);
    triDiagonalMatrix["subDiag"] = std::vector<double>(numAssetStep-3);

    for (int k=1; k<numAssetStep-1; ++k){
        triDiagonalMatrix["diag"][k-1] = -1 -v1*vol*vol*assetPrices[k]*assetPrices[k] - r*dt;
    }
    for (int k=1; k<numAssetStep-2; ++k){
        triDiagonalMatrix["superDiag"][k-1] = 0.5*v1*vol*vol*assetPrices[k]*assetPrices[k] + 0.5*v2*r*assetPrices[k];
    }
    for (int k=2; k<numAssetStep-1; ++k){
        triDiagonalMatrix["subDiag"][k-2] = 0.5*v1*vol*vol*assetPrices[k]*assetPrices[k]-0.5*v2*r*assetPrices[k];
    }

    return triDiagonalMatrix;
}

std::vector<double> Implicit::_getTarget(
    const std::vector<double>& curOptionPrices,
    const std::vector<double>& assetPrices,
    double v1,
    double v2,
    double vol,
    double r,
    double dt
) const{
    unsigned long numAssetStep = curOptionPrices.size();
    std::vector<double> target(numAssetStep - 2);
    for (int i=1; i<numAssetStep-1; ++i){
        target[i-1] = -curOptionPrices[i];
    }
    return target;
}

void Implicit::_addBoundaryConditionsToSystem(
    std::vector<double>& target,
    std::map<std::string, std::vector<double>>& curTriDiagonalMatrix,
    const std::vector<double>& curOptionPrices,
    const std::vector<double>& assetPrices,
    double vol,
    double v1,
    double v2,
    double r,
    double dt
){
    unsigned long numAssetStep =assetPrices.size();
    target[0] -= (0.5*v1*vol*vol*assetPrices[1]*assetPrices[1]-0.5*v2*r*assetPrices[1])*curOptionPrices[0]*(1- r*dt);
    curTriDiagonalMatrix["subDiag"][numAssetStep-4] -= (0.5*v1*vol*vol*assetPrices[numAssetStep-2]*assetPrices[numAssetStep-2] + 0.5*v2*r*assetPrices[numAssetStep-2]);
    curTriDiagonalMatrix["diag"][numAssetStep-3] += (v1*vol*vol*assetPrices[numAssetStep-2]*assetPrices[numAssetStep-2] + v2*r*assetPrices[numAssetStep-2]);
}

void Implicit::_updateBoundary(
    std::vector<double>& curOptionPrices,
    double r,
    double dt
){
    unsigned long numAssetStep = curOptionPrices.size();
    curOptionPrices[0] = curOptionPrices[0]*(1- r*dt);
    curOptionPrices[numAssetStep - 1] = 2*curOptionPrices[numAssetStep-2] - curOptionPrices[numAssetStep -3];
}