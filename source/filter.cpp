#include "../include/filter.h"


Filter::Filter() = default;

float Filter::low_pass(float resistance, float capacitance)
{
    /* input: resistance[Ω], capacitance[uF] : return: [Hz] */
    return 1 / (2 * M_PI * (capacitance / M_UF_TO_F) * resistance);
}

float Filter::high_pass(float resistance, float capacitance)
{
    /* input: resistance[KΩ], capacitance[uF] : return: [Hz] */
    return 1 / (2 * M_PI * (capacitance / M_UF_TO_F) * resistance);
}
