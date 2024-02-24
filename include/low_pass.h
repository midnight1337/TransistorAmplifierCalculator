#include "filter.h"

#ifndef LOW_PASS_H
#define LOW_PASS_H


class LowPass : public Filter
{

public:
    LowPass(float resistance, float capacitance);
    float calculate_magnitude(int frequency_sample) override;
};

#endif
