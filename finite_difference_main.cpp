#include "include/crank_nicolson.h"
#include "include/explicit_numerical.h"
#include "include/implicit_vanilla.h"
#include "include/payoff_factory.h"
#include "include/numerical_pricing_engine_factory.h"
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

    std::string engineName;
    unsigned long numAssetSteps;
    unsigned long numTimeSteps;
    double upperPriceLimit;

    std::vector<std::string> payOffNames = PayOffFactory::Instance().getPayOffNames();
    std::string concatenatedPayOffNames = concatenate(payOffNames);
    std::cout << "Enter the payoff type: {" << concatenatedPayOffNames << "}" << std::endl;
    std::cin >> payOffName;
    std::vector<std::string> paramNames = PayOffFactory::Instance().getParamNames(payOffName);
    std::map<std::string, double> params = inputValuesIntoMap(paramNames);
    std::unique_ptr<PayOff> payOffPtr = PayOffFactory::Instance().createPayOff(payOffName, params);

    std::vector<std::string> engineNames = NumericalPricingEngineFactory::Instance().getEngineNames();
    std::string concatenatedEngineNames = concatenate(engineNames);

    Option::OptionType optionType = inputOptionType();

    std::cout << "Enter expiry: " << std::endl;
    std::cin >> expiry;
    Option theOption(*payOffPtr, expiry, optionType);

    std::cout << "Enter volatility: " << std::endl;
    std::cin >> vol;

    std::cout << "Enter interest rate: " << std::endl;
    std::cin >> r;

    std::cout << "Enter dividend rate: " << std::endl;
    std::cin >> div;
    
    std::cout<< "Enter spot: " << std::endl;
    std::cin >> spot; 

    std::cout << "Enter engine type: {" << concatenatedEngineNames << "}" << std::endl;
    std::cin >> engineName;

    std::unique_ptr<NumericalPricingEngine> enginePtr = NumericalPricingEngineFactory::Instance().createEngine(
        engineName, theOption, vol, r, div
    );
    std::cout << "Enter number of asset steps for numerical solver: "<< std::endl;
    std::cin >> numAssetSteps;

    std::cout << "Enter number of time steps for numerical solver: "<< std::endl;
    std::cin >> numTimeSteps;

    std::cout << "Enter upper price limit for numerical solver: "<< std::endl;
    std::cin >> upperPriceLimit;

    enginePtr->buildModel(numAssetSteps, numTimeSteps, upperPriceLimit);

    double p = enginePtr->getOptionPrice(spot);

    std::cout << "Option price, calculated using " << engineName << " method is: "  << p <<std::endl;

}