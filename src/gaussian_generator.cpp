#include "../include/gaussian_generator.h"
#include "../include/halton_sequence.h"
#include "../include/box_muller.h"

GaussianGenerator::GaussianGenerator(
    unsigned long state_): state(state_)
{}

double GaussianGenerator::getGaussian(){
    if (takeSecond == true){
        takeSecond = false;
        return storedGaussian;
    }
    else {
        double x= 0;
        double y;
        while (x==0){
            x = haltonSequence(state, 2);
            y = haltonSequence(state, 3);
            state += 1;
        }

        std::pair<double, double> p = boxMuller(x, y);
        storedGaussian = p.second;
        takeSecond = true;
        
        return p.first;
    }
}