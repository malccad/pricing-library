#include "../include/option/payoff_factory.h"
#include "../include/option/option.h"
#include "../include/utils/utils.h"
#include "../include/binomial/binomial_pricing.h"
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
    std::cout << "Enter the payoff type: {" << concatenatedPayOffNames << "}" << std::endl;
    std::cin >> payOffName;
    std::vector<std::string> paramNames = PayOffFactory::Instance().getParamNames(payOffName);
    std::map<std::string, double> params = inputValuesIntoMap(paramNames);
    std::unique_ptr<PayOff> payOffPtr = PayOffFactory::Instance().createPayOff(payOffName, params);

    std::cout << "Enter expiry: " << std::endl;
    std::cin >> expiry;
    Option::OptionType optionType = inputOptionType();
    Option theOption(*payOffPtr, expiry, optionType);

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

    BinomialPricingEngine engine(spot, theOption, vol, r, div, numBinomialTimeSteps);
    double binomialPrice = engine.getOptionPrice();
    std::cout << "Option price, calculated using the binomial model is: "<< binomialPrice << std::endl;
}