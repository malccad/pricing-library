#include "../include/box_muller.h"
#include <cmath>

std::pair<double, double> boxMuller(
    double x,
    double y
){
    double r = sqrt(-2*log(x));
    double z0 = r*cos(2*M_PI*y);
    double z1 = r*sin(2*M_PI*y);
    return std::make_pair(z0, z1);
}