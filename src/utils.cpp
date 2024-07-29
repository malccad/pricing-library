#include "../include/utils.h"
#include <iostream>

std::string concatenate(std::vector<std::string> l, std::string delimiter){
    std::string out = "";
    for (int i=0; i<l.size();++i){
        out += l[i];
        if (i<l.size()-1){
            out += delimiter;
            out += " ";
        }
    }
    return out;
}

std::map<std::string, double> inputValuesIntoMap(std::vector<std::string> keys){
    std::map<std::string, double> m;
    for (std::string key: keys){
        std::cout << "Enter " << key << std::endl;
        double input;
        std::cin >> input;
        m[key] = input;
    }
    return m;
}

Option::OptionType inputOptionType(){
    Option::OptionType optionType;
    int input;
    std::cout << "Enter option type (0 = european, 1 = american):" <<  std::endl;
    std::cin >> input;
    switch (input){
        case 0:
            optionType = Option::european;
            break;
        case 1:
            optionType = Option::american;
            break;
        default:
            std::cout << "Invalid choice. Defaulting to european option." << std::endl;
            optionType = Option::european;
            break;
    }
    return optionType;

}
