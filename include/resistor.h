#include <iostream>

#ifndef RESISTOR_H
#define RESISTOR_H

class Resistor
{
public:
    static float calculate_in_parallel(int argc, const float *resistors);
    static float calculate_in_series(int argc, const float* resistors);
};

#endif
