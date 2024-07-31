#include "include/payoff_factory.h"
#include "include/monte_carlo_pricing.h"
#include "include/least_square_monte_carlo_pricing.h"
#include "include/option.h"
#include "include/utils.h"
#include <iostream>
#include <string>
int main(){

    std::string payOffName;
    
    double expiry;
    double vol;
    double r;
    double div;
    double spot;
    unsigned long numPaths;
    double monteCarloPrice;
    double standardErrorOfMean;

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

    std::cout<< "Enter number of paths for Monte Carlo" << std::endl;
    std::cin >> numPaths;
    
    if (optionType == Option::european){
        MonteCarloPricingEngine engine(spot, theOption, vol, r, div, numPaths);
        monteCarloPrice = engine.getOptionPrice();
        standardErrorOfMean = engine.getStandardErrorOfMean();
    }
    else if (optionType == Option::american)
    {   
        unsigned long numBasisFunctions;
        unsigned long numTimeSteps;
        std::cout << "Enter number of basis functions: " << std::endl;
        std::cin >> numBasisFunctions;

        std::cout << "Enter number of time steps:" << std::endl;
        std::cin >> numTimeSteps;
        LeastSquareMonteCarloPricingEngine engine(spot, theOption, vol, r, div, numPaths, numBasisFunctions, numTimeSteps);
        monteCarloPrice = engine.getOptionPrice();
        standardErrorOfMean = engine.getStandardErrorOfMean();
    }
    
    std::cout<< "monte carlo price: "<< monteCarloPrice << std::endl;
    std::cout<< "standard error of mean: "<< standardErrorOfMean << std::endl;
    
}