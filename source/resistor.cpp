#include "../include/resistor.h"


float Resistor::calculate_in_parallel(int argc, const float *resistors)
{
    float resistance = 0.0;

    for (int i = 0; i < argc; i++)
    {
        resistance += 1 / resistors[i];
    }

    resistance = 1 / resistance;

    return resistance;
}

float Resistor::calculate_in_series(int argc, const float *resistors)
{
    float resistance = 0.0;

    for (int i = 0; i < argc; i++)
    {
        resistance += resistors[i];
    }

    return resistance;
}
