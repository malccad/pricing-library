#include "../include/payoff_factory.h"
#include <iostream>

PayOffFactory& PayOffFactory::Instance(){
    static PayOffFactory theFactory;
    return theFactory;
}

void PayOffFactory::registerPayOff(std::string payOffName, CreatePayOffFunction createPayOffFunction, std::vector<std::string> paramNames){
    theCreatorFunctions.insert(std::pair<std::string, CreatePayOffFunction>(payOffName, createPayOffFunction));
    payOffParamNames.insert(std::pair<std::string, std::vector<std::string>>(payOffName, paramNames));
}

std::unique_ptr<PayOff> PayOffFactory::createPayOff(std::string payOffName, std::map<std::string, double> params){
    std::map<std::string, CreatePayOffFunction>::iterator it = theCreatorFunctions.find(payOffName);

    if (it == theCreatorFunctions.end()){
        std::cout << payOffName << " is not a registered payoff." << std::endl;
        return NULL;
    }
    return (it->second)(params);
}

std::vector<std::string> PayOffFactory::getPayOffNames() const{
    std::vector<std::string> payOffNames;
    for (const auto& pair : theCreatorFunctions){
        payOffNames.push_back(pair.first);
    }
    return payOffNames;
}

std::vector<std::string> PayOffFactory::getParamNames(std::string payOffName){
    std::map<std::string, std::vector<std::string>>::iterator it = payOffParamNames.find(payOffName);
    return it->second;
}