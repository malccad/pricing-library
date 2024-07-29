#include "include/linear_regression.h"
#include "include/linear_algebra.h"
#include <iostream>
#include <vector>

int main(){
    std::vector<double> a = {1,1};
    std::vector<double> b = {1,2};
    std::vector<double> c = {2,2};
    std::vector<double> d = {2,3};
    std::vector<std::vector<double>>X {a, b, c, d};
    std::vector<double> v = {1,2};
    std::vector<double> y = matMulVector(X, v);
    LinearRegression regressor = LinearRegression();
    regressor.fit(X, y);
    std::vector<double> w = regressor.getWeights();
    std::cout<< "weights: "<<std::endl;
    for (int i=0; i<w.size(); ++i){
        std::cout << w[i] << ", ";
    }

    std::vector<double> yhat = regressor.predict(X);
    std::cout << "Predictions: "<<std::endl;
    for (int i=0; i<yhat.size(); ++i){
        std::cout << yhat[i] << ", ";
    }
    std::cout << "Ground Truth: "<<std::endl;
    for (int i=0; i<y.size(); ++i){
        std::cout << y[i] << ", ";
    }    
    std::cout<<std::endl;
}