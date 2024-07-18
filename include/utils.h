#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <map>
std::string concatenate(std::vector<std::string> l, std::string delimiter=",");
std::map<std::string, double> inputValuesIntoMap(std::vector<std::string> keys);
#endif