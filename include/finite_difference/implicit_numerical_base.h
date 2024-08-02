#ifndef IMPLICIT_NUMERICAL_BASE_H
#define IMPLICIT_NUMERICAL_BASE_H

#include <vector>

#include "numerical_pricing_engine.h"
class ImplicitBase: public NumericalPricingEngine
{
public:
    ImplicitBase(
        const Wrapper<Option>& theOption,
        double vol,
        double r,
        double div
    );
    void buildModel(
        unsigned long numAssetStep,
        unsigned long numTimeStep,
        double upperLimit
    ) override;

    virtual ~ImplicitBase(){}
protected:
    virtual std::map<std::string, std::vector<double>> _getTriDiagonalMatrix(
        const std::vector<double>& assetPrices,
        double v1,
        double v2,
        double vol,
        double r,
        double div,
        double dt
    ) const=0;

    virtual std::vector<double> _getTarget(
        const std::vector<double>& curOptionPrices,
        const std::vector<double>& assetPrices,
        double v1,
        double v2,
        double vol,
        double r,
        double div,
        double dt
    ) const=0;

    virtual void _addBoundaryConditionsToSystem(
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
    )=0;

    virtual void _updateBoundary(
        std::vector<double>& curOptionPrices,
        double r,
        double div,
        double dt
    )=0;
};
#endif