#include "../include/filter.h"


Filter::Filter() = default;

float Filter::low_pass(float resistance, float capacitance)
{
    /* input: resistance[Ω], capacitance[uF], return: [Hz] */
    capacitance = capacitance * 1000000;    // Convert from uF to F
    return 1 / (2 * 3.14 * capacitance * resistance);
}

float Filter::high_pass(float resistance, float capacitance)
{
    /* input: resistance[KΩ], capacitance[uF], return: [Hz] */
    capacitance = capacitance / 1000000;    // Convert from uF to F
    return 1 / (2 * 3.14 * capacitance * resistance);
}
