#include "../include/linear_regression.h"
#include "../include/linear_algebra.h"
#include <iostream>
void LinearRegression::fit(const std::vector<std::vector<double>>& X, const std::vector<double>& y){
    assert (X.size() == y.size());
    // add bias
    std::vector<std::vector<double>> X_1(X);
    for (std::vector<double>& v: X_1){
        v.push_back(1.0);
    }
    std::vector<std::vector<double>> gramMatrix = getGramMatrix(X_1);
    std::vector<std::vector<double>> gramMatrix_inv = invertPosSymDefMat(gramMatrix);
    weights = matMulVector(matMul(gramMatrix_inv, transpose(X_1)), y);
}

std::vector<double> LinearRegression::predict(const std::vector<std::vector<double>>& X){
    std::vector<std::vector<double>> X_1(X);
    for (std::vector<double>& v: X_1){
        v.push_back(1.0);
    }
    return matMulVector(X_1, weights);
}