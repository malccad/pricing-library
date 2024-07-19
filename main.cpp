#include "include/crank_nicolson.h"
#include "include/explicit_numerical.h"
#include "include/implicit_vanilla.h"
#include "include/payoff_factory.h"
#include "include/numerical_pricing_engine_factory.h"
#include "include/monte_carlo_pricing.h"
#include "include/utils.h"
#include "include/binomial_pricing.h"
#include <iostream>
#include <string>
int main(){

    std::string payOffName;
    
    double expiry;
    std::string engineName;
    double vol;
    double r;
    double div;
    double spot;
    unsigned long numPaths;
    unsigned long numAssetSteps;
    unsigned long numTimeSteps;
    double upperPriceLimit;
    unsigned long numBinomialTimeSteps;

    std::vector<std::string> payOffNames = PayOffFactory::Instance().getPayOffNames();
    std::string concatenatedPayOffNames = concatenate(payOffNames);
    std::vector<std::string> engineNames = NumericalPricingEngineFactory::Instance().getEngineNames();
    std::string concatenatedEngineNames = concatenate(engineNames);
    std::cout << "Enter the option type: {" << concatenatedPayOffNames << "}" << std::endl;
    std::cin >> payOffName;

    std::unique_ptr<PayOff> payOffPtr = PayOffFactory::Instance().createPayOff(payOffName);
    
    std::vector<std::string> paramNames = payOffPtr->getParamNames();
    std::map<std::string, double> params = inputValuesIntoMap(paramNames);
    payOffPtr->readParams(params);

    std::cout << "Enter expiry: " << std::endl;
    std::cin >> expiry;
    EuropeanOption theOption(*payOffPtr, expiry);

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

    std::cout << "Enter number of time steps for binomial pricing" << std::endl;
    std::cin >> numBinomialTimeSteps;

    double binomialPrice = getBinomialPrice(spot, theOption, vol, r, div, numBinomialTimeSteps);
    std::cout << "Option price, calculated using the binomial model is: "<< binomialPrice << std::endl;

    std::cout<< "Enter number of paths for Monte Carlo" << std::endl;
    std::cin >> numPaths; 
    double monteCarloPrice = getMonteCarloPrice(spot, theOption, vol, r, div, numPaths);
    std::cout<< "monte carlo price: "<< monteCarloPrice << std::endl;
    
}