#ifndef GAUSSIAN_GENERATOR_H
#define GAUSSIAN_GENERATOR_H
#include <vector>
class GaussianGenerator
{
public:
    GaussianGenerator(unsigned long state_=1);
    double getGaussian();
private:
    unsigned long state;
    bool takeSecond = false;
    double storedGaussian;
};

class MultiDimGaussianGenerator
{
public:
    MultiDimGaussianGenerator(unsigned long dim, unsigned long state_=1);
    std::vector<double> getGaussian();
private:
    unsigned long dim;
    unsigned long state;
    std::vector<double> primes;
};

bool isPrime(unsigned long n);
#endif