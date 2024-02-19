#include <iostream>
#include <cmath>
#include <map>
#include "capacitor.h"

#ifndef FILTER_H
#define FILTER_H


class Filter
{
protected:
    static const int M_UF_TO_F = 1000000;
    float m_cutoff_frequency;
    float m_first_order_resistance;
    float m_first_order_capacitance;
    float m_second_order_resistance;
    float m_second_order_capacitance;
    std::map<int, float> m_magnitude_samples;

public:
    Filter(float first_order_resistance, float first_order_capacitance);
    Filter(float first_order_resistance, float first_order_capacitance, float second_order_resistance, float second_order_capacitance);
    static float calculate_first_order_filter_cutoff_frequency(float first_order_resistance, float first_order_capacitance);
    float calculate_second_order_filter_cutoff_frequency();
    float calculate_band_pass_filter_cutoff_frequency();
    void calculate_first_order_high_pass_magnitude(int frequency_sample);
    void calculate_first_order_low_pass_magnitude(int frequency_sample);
    void calculate_second_order_high_pass_magnitude(int frequency_sample);
    void calculate_second_order_low_pass_magnitude(int frequency_sample);
    void frequency_analysis();
    void show_data();
};

#endif
