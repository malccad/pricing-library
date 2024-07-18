#include "../include/payoff_factory.h"
#include <iostream>

PayOffFactory& PayOffFactory::Instance(){
    static PayOffFactory theFactory;
    return theFactory;
}

void PayOffFactory::registerPayOff(std::string payOffName, CreatePayOffFunction createPayOffFunction){
    theCreatorFunctions.insert(std::pair<std::string, CreatePayOffFunction>(payOffName, createPayOffFunction));
}

std::unique_ptr<PayOff> PayOffFactory::createPayOff(std::string payOffName){
    std::map<std::string, CreatePayOffFunction>::iterator it = theCreatorFunctions.find(payOffName);

    if (it == theCreatorFunctions.end()){
        std::cout << payOffName << " is not a registered payoff." << std::endl;
        return NULL;
    }
    return (it->second)();
}

std::vector<std::string> PayOffFactory::getPayOffNames() const{
    std::vector<std::string> payOffNames;
    for (const auto& pair : theCreatorFunctions){
        payOffNames.push_back(pair.first);
    }
    return payOffNames;
}