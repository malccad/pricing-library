#ifndef IMPLICIT_VANILLA_H
#define IMPLICIT_VANILLA_H

#include <vector>

#include "implicit_numerical_base.h"
class Implicit: public ImplicitBase
{
public:
    Implicit(
        const Wrapper<Option>& theOption,
        double vol,
        double r,
        double div
    );
    virtual ~Implicit(){}
private:
    std::map<std::string, std::vector<double>> _getTriDiagonalMatrix(
        const std::vector<double>& assetPrices,
        double v1,
        double v2,
        double vol,
        double r,
        double div,
        double dt
    ) const override;

    std::vector<double> _getTarget(
        const std::vector<double>& curOptionPrices,
        const std::vector<double>& assetPrices,
        double v1,
        double v2,
        double vol,
        double r,
        double div,
        double dt
    ) const override;

    void _addBoundaryConditionsToSystem(
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
    ) override;

    void _updateBoundary(
        std::vector<double>& curOptionPrices,
        double r,
        double div,
        double dt
    ) override;
};
#endif