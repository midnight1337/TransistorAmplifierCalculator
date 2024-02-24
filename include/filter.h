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
    float m_resistance;
    float m_capacitance;
    float m_cutoff_frequency;
    std::map<int, float> m_magnitude_samples;

public:
    Filter() = default;
    Filter(float resistance, float capacitance);
    virtual ~Filter() = default;

    float cutoff_frequency() const;
    void calculate_cutoff_frequency();
    virtual float calculate_magnitude(int frequency_sample) = 0;
    virtual void filter_analysis();
    virtual void show_filter_data();
    void show_magnitude();

    static float calculate_cutoff_frequency(float resistance, float capacitance);
};

#endif
