#include "../include/implicit_vanilla.h"
#include "../include/matrix_solver.h"

Implicit::Implicit(
    const Wrapper<Option>& theOption,
    double vol,
    double r,
    double div
):ImplicitBase(theOption, vol, r, div)
{}

std::map<std::string, std::vector<double>> Implicit::_getTriDiagonalMatrix(
    const std::vector<double>& assetPrices,
    double v1,
    double v2,
    double vol,
    double r,
    double div,
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
        triDiagonalMatrix["superDiag"][k-1] = 0.5*v1*vol*vol*assetPrices[k]*assetPrices[k] + 0.5*v2*(r-div)*assetPrices[k];
    }
    for (int k=2; k<numAssetStep-1; ++k){
        triDiagonalMatrix["subDiag"][k-2] = 0.5*v1*vol*vol*assetPrices[k]*assetPrices[k]-0.5*v2*(r-div)*assetPrices[k];
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
    double div,
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
    double div,
    double dt
){
    unsigned long numAssetStep =assetPrices.size();
    target[0] -= (0.5*v1*vol*vol*assetPrices[1]*assetPrices[1]-0.5*v2*(r-div)*assetPrices[1])*curOptionPrices[0]*(1- r*dt);
    curTriDiagonalMatrix["subDiag"][numAssetStep-4] -= (0.5*v1*vol*vol*assetPrices[numAssetStep-2]*assetPrices[numAssetStep-2] + 0.5*v2*(r-div)*assetPrices[numAssetStep-2]);
    curTriDiagonalMatrix["diag"][numAssetStep-3] += (v1*vol*vol*assetPrices[numAssetStep-2]*assetPrices[numAssetStep-2] + v2*(r-div)*assetPrices[numAssetStep-2]);
}

void Implicit::_updateBoundary(
    std::vector<double>& curOptionPrices,
    double r,
    double div,
    double dt
){
    unsigned long numAssetStep = curOptionPrices.size();
    curOptionPrices[0] = curOptionPrices[0]*(1- r*dt);
    curOptionPrices[numAssetStep - 1] = 2*curOptionPrices[numAssetStep-2] - curOptionPrices[numAssetStep -3];
}