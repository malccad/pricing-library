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
