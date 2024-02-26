#include "filter.h"

#ifndef HIGH_PASS_H
#define HIGH_PASS_H


class HighPass : public Filter
{
public:
    HighPass(float resistance, float capacitance);
    float calculate_magnitude(int frequency_sample) override;
};

#endif
