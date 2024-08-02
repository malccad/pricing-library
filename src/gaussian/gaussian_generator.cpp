#include "../../include/gaussian/gaussian_generator.h"
#include "../../include/gaussian/halton_sequence.h"
#include "../../include/gaussian/box_muller.h"
#include <iostream>
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


MultiDimGaussianGenerator::MultiDimGaussianGenerator(unsigned long dim, unsigned long state)
    :dim(dim), state(state)
{
    unsigned long n = 2;
    unsigned long numRandPerStep = dim + dim%2;
    while (primes.size() < numRandPerStep){
        if (isPrime(n) == true)
            primes.push_back(n);
        n++;
    }
}
bool isPrime(unsigned long n){
    if (n<=1)
        return false;
    for (int i=2; i <= n/2; ++i){
        if (n%i ==0)
            return false;
    }
    return true;
}

std::vector<double> MultiDimGaussianGenerator::getGaussian(){
    std::vector<double> uniformRands;
    for (unsigned long p: primes){
        double x = haltonSequence(state, p);
        uniformRands.push_back(x);
    }
    std::vector<double> gaussians;
    for (int i=0; i<uniformRands.size(); i+=2){
        std::pair<double, double> p = boxMuller(uniformRands[i], uniformRands[i+1]);
        gaussians.push_back(p.first);
        gaussians.push_back(p.second);
    }
    if (gaussians.size() > dim){
        gaussians.pop_back();
    }
    state++;
    return gaussians;
}

