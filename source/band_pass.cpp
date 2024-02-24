#include "../include/band_pass.h"


BandPass::BandPass(float first_order_resistance, float first_order_capacitance, float second_order_resistance, float second_order_capacitance) :
m_high_pass(HighPass(first_order_resistance, first_order_capacitance)),
m_low_pass(LowPass(second_order_resistance, second_order_capacitance))
{}

void BandPass::calculate_centre_frequency()
{
    m_high_pass.calculate_cutoff_frequency();
    m_low_pass.calculate_cutoff_frequency();

    m_centre_frequency = sqrt(m_high_pass.cutoff_frequency() * m_low_pass.cutoff_frequency());
}

float BandPass::calculate_magnitude(int frequency_sample)
{
    return 0;
}

void BandPass::filter_analysis()
{
    calculate_centre_frequency();

    // TO DO, this below is bad i guess
    for (int frequency_sample = 1; frequency_sample < m_centre_frequency; frequency_sample++)
    {
        m_magnitude_samples[frequency_sample] = m_high_pass.calculate_magnitude(frequency_sample);
    }

    for (int frequency_sample = m_centre_frequency; frequency_sample < m_centre_frequency * 2; frequency_sample++)
    {
        m_magnitude_samples[frequency_sample] = m_low_pass.calculate_magnitude(frequency_sample);
    }
}

void BandPass::show_filter_data()
{
    std::cout << "Center frequency[Hz]: " << m_centre_frequency << std::endl;

    m_high_pass.show_filter_data();
    m_low_pass.show_filter_data();
}
