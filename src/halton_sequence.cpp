#include "../include/halton_sequence.h"

double haltonSequence(
    unsigned long i,
    unsigned long base
){
    // find base number representation
    double out = 0;
    unsigned long j = i;
    double invertedBase = static_cast<double>(1)/base;
    while (j != 0){
        unsigned long q = j/base;
        unsigned long r = j - q*base;
        out += r*invertedBase;
        invertedBase /=base;
        j=q;
    }
    return out;
}