#include "../../include/monte_carlo/minmax_scaler.h"

void MinMaxScaler::fit(const std::vector<double>& v){
    min = v[0];
    max = v[0];
    for (double val: v){
        if (val > max)
            max = val;
        if (val < min)
            min = val;
    }
    if (max == min){
        min = max - 1;
    }
}

std::vector<double> MinMaxScaler::transform(const std::vector<double>& v) const{
    std::vector<double> w;
    for (double val: v){
        double scaledVal = (val - min)/(max-min);
        w.push_back(scaledVal);
    }
    return w;
}

std::vector<double> MinMaxScaler::inverseTransform(const std::vector<double>& w) const{
    std::vector<double> v;
    for (double val: w){
        double originalVal = val*(max-min) + min;
        v.push_back(originalVal);
    }
    return w;
}