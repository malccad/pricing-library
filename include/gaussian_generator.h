#ifndef GAUSSIAN_GENERATOR_H
#define GAUSSIAN_GENERATOR_H
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
#endif