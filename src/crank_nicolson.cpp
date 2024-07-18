#include "../include/crank_nicolson.h"

CrankNicolson::CrankNicolson(
    const Wrapper<EuropeanOption>& theOption,
    double vol,
    double r
):ImplicitBase(theOption, vol, r)
{}

std::map<std::string, std::vector<double>> CrankNicolson::_getTriDiagonalMatrix(
    const std::vector<double>& assetPrices,
    double v1,
    double v2,
    double vol,
    double r,
    double dt
) const{
    unsigned long numAssetStep = assetPrices.size();
    std::map<std::string, std::vector<double>> triDiagonalMatrix;
    triDiagonalMatrix["diag"] = std::vector<double>(numAssetStep-2);
    triDiagonalMatrix["superDiag"] = std::vector<double>(numAssetStep-3);
    triDiagonalMatrix["subDiag"] = std::vector<double>(numAssetStep-3);

    for (int k=1; k<numAssetStep-1; ++k){
        triDiagonalMatrix["diag"][k-1] = -1 -0.5*v1*vol*vol*assetPrices[k]*assetPrices[k] - 0.5*r*dt;
    }
    for (int k=1; k<numAssetStep-2; ++k){
        triDiagonalMatrix["superDiag"][k-1] = 0.25*v1*vol*vol*assetPrices[k]*assetPrices[k] + 0.25*v2*r*assetPrices[k];
    }
    for (int k=2; k<numAssetStep-1; ++k){
        triDiagonalMatrix["subDiag"][k-2] = 0.25*v1*vol*vol*assetPrices[k]*assetPrices[k]-0.25*v2*r*assetPrices[k];
    }

    return triDiagonalMatrix;
}

std::vector<double> CrankNicolson::_getTarget(
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
        target[i-1] = -(0.25*v1*vol*vol*assetPrices[i]*assetPrices[i] - 0.25*r*assetPrices[i]*v2)*curOptionPrices[i-1] \
                    -(1- 0.5*vol*vol*assetPrices[i]*assetPrices[i]*v1 - 0.5*r*dt)*curOptionPrices[i] \
                    -(0.25*v1*vol*vol*assetPrices[i]*assetPrices[i] + 0.25*r*assetPrices[i]*v2)*curOptionPrices[i+1];
    }
    return target;
}

void CrankNicolson::_addBoundaryConditionsToSystem(
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
    unsigned long numAssetStep = curOptionPrices.size();

    target[0] -= (0.25*v1*vol*vol*assetPrices[1]*assetPrices[1]-0.25*v2*r*assetPrices[1])*curOptionPrices[0]*(1-r*dt);
    curTriDiagonalMatrix["diag"][numAssetStep-3] += 2*(0.25*v1*vol*vol*assetPrices[numAssetStep-2]*assetPrices[numAssetStep-2] + 0.25*v2*r*assetPrices[numAssetStep-2]);
    curTriDiagonalMatrix["subDiag"][numAssetStep-4] -= (0.25*v1*vol*vol*assetPrices[numAssetStep-2]*assetPrices[numAssetStep-2] + 0.25*v2*r*assetPrices[numAssetStep-2]);
}

void CrankNicolson::_updateBoundary(
    std::vector<double>& curOptionPrices,
    double r,
    double dt
){
    unsigned long numAssetStep = curOptionPrices.size();
    curOptionPrices[0] = curOptionPrices[0]*(1- r*dt);
    curOptionPrices[numAssetStep - 1] = 2*curOptionPrices[numAssetStep-2] - curOptionPrices[numAssetStep -3];
}