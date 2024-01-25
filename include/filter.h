#include <iostream>

#ifndef FILTER_H
#define FILTER_H


class Filter
{
private:

public:
    Filter();
    static float low_pass(float resistance, float capacitance);
    static float high_pass(float resistance, float capacitance);
};

#endif
