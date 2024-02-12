#include <iostream>
#include <cmath>

#ifndef FILTER_H
#define FILTER_H


class Filter
{
private:
    static const int M_UF_TO_F = 1000000;

public:
    Filter();
    static float low_pass(float resistance, float capacitance);
    static float high_pass(float resistance, float capacitance);
};

#endif
