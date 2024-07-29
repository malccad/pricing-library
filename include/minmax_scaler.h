#ifndef STANDARD_SCALER_H
#define STANDARD_SCALER_H
#include <vector>

class MinMaxScaler
{
public:
    void fit(const std::vector<double>& v);
    std::vector<double> transform(const std::vector<double>& v) const;
    std::vector<double> inverseTransform(const std::vector<double>& w) const;
private:
    double min;
    double max;
};
#endif