#include "include/payoff_factory.h"
#include "include/option.h"
#include "include/utils.h"
#include "include/binomial_pricing.h"
#include <iostream>
#include <string>
int main(){

    std::string payOffName;
    
    double expiry;
    double vol;
    double r;
    double div;
    double spot;
    unsigned long numBinomialTimeSteps;

    std::vector<std::string> payOffNames = PayOffFactory::Instance().getPayOffNames();
    std::string concatenatedPayOffNames = concatenate(payOffNames);
    std::cout << "Enter the option type: {" << concatenatedPayOffNames << "}" << std::endl;
    std::cin >> payOffName;

    std::unique_ptr<PayOff> payOffPtr = PayOffFactory::Instance().createPayOff(payOffName);
    
    std::vector<std::string> paramNames = payOffPtr->getParamNames();
    std::map<std::string, double> params = inputValuesIntoMap(paramNames);
    payOffPtr->readParams(params);

    std::cout << "Enter expiry: " << std::endl;
    std::cin >> expiry;

    Option theOption(*payOffPtr, expiry);

    std::cout << "Enter volatility: " << std::endl;
    std::cin >> vol;

    std::cout << "Enter interest rate: " << std::endl;
    std::cin >> r;

    std::cout << "Enter dividend rate: " << std::endl;
    std::cin >> div;
    
    std::cout<< "Enter spot: " << std::endl;
    std::cin >> spot;

    std::cout << "Enter number of time steps for binomial pricing" << std::endl;
    std::cin >> numBinomialTimeSteps;

    double binomialPrice = getBinomialPrice(spot, theOption, vol, r, div, numBinomialTimeSteps);
    std::cout << "Option price, calculated using the binomial model is: "<< binomialPrice << std::endl;
}