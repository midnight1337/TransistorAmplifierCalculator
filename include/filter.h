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
    float m_first_order_resistance;
    float m_first_order_capacitance;
    float m_second_order_resistance;
    float m_second_order_capacitance;
    float m_cutoff_frequency;
    std::map<int, float> m_magnitude_samples;

public:
    Filter(float first_order_resistance, float first_order_capacitance);
    Filter(float first_order_resistance, float first_order_capacitance, float second_order_resistance, float second_order_capacitance);

    Filter();


    static float calculate_first_order_filter_cutoff_frequency(float first_order_resistance, float first_order_capacitance);
    static float calculate_second_order_filter_cutoff_frequency(float first_order_resistance, float first_order_capacitance, float second_order_resistance, float second_order_capacitance);

    virtual void calculate_first_order_filter() = 0;
    virtual void calculate_second_order_filter() = 0;
    virtual void calculate_magnitude_of_first_order_filter() = 0;
    virtual void calculate_magnitude_of_second_order_filter() = 0;

    void show_data();
    virtual ~Filter() = default;

    float calculate_band_pass_filter_centre_frequency();

    float calculate_first_order_high_pass_filter_magnitude(int frequency_sample);
    float calculate_first_order_low_pass_filter_magnitude(int frequency_sample);
    float calculate_second_order_high_pass_filter_magnitude(int frequency_sample);
    float calculate_second_order_low_pass_filter_magnitude(int frequency_sample);

    void frequency_analysis_of_first_order_high_pass_filter();
    void frequency_analysis_of_first_order_low_pass_filter();
    void frequency_analysis_of_second_order_high_pass_filter();
    void frequency_analysis_of_second_order_low_pass_filter();
    void frequency_analysis_of_band_pass_filter();
};

#endif
