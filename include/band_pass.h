#include "filter.h"
#include "high_pass.h"
#include "low_pass.h"

#ifndef BAND_PASS_H
#define BAND_PASS_H


class BandPass : public Filter
{
private:
    HighPass m_high_pass;
    LowPass m_low_pass;
    float m_centre_frequency;
    float m_bandwidth;

    void calculate_centre_frequency();
    void calculate_bandwidth();

public:
    BandPass(float first_order_resistance, float first_order_capacitance, float second_order_resistance, float second_order_capacitance);
    float calculate_magnitude(int frequency_sample) override;
    void filter_analysis() override;
    void show_filter_data() override;
};

#endif
