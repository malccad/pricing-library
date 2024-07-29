#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H
#include <vector>
class LinearRegression
{
public:
    void fit(const std::vector<std::vector<double>>& X, const std::vector<double>& y);
    std::vector<double> predict(const std::vector<std::vector<double>>& X);
    std::vector<double> getWeights(){return weights;}
private:
    std::vector<double> weights;
};
#endif