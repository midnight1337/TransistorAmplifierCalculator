#include "../include/band_pass.h"


BandPass::BandPass(float first_order_resistance, float first_order_capacitance, float second_order_resistance, float second_order_capacitance) :
m_high_pass(HighPass(first_order_resistance, first_order_capacitance)),
m_low_pass(LowPass(second_order_resistance, second_order_capacitance))
{
    m_centre_frequency = 0;
    m_bandwidth = 0;
}

void BandPass::calculate_centre_frequency()
{
    m_high_pass.calculate_cutoff_frequency();
    m_low_pass.calculate_cutoff_frequency();

    m_centre_frequency = sqrt(m_high_pass.cutoff_frequency() * m_low_pass.cutoff_frequency());
}

void BandPass::calculate_bandwidth()
{
    m_bandwidth = fabs(m_high_pass.cutoff_frequency() - m_low_pass.cutoff_frequency());
}

float BandPass::calculate_magnitude(int frequency_sample)
{
    float hp_magnitude = m_high_pass.calculate_magnitude(frequency_sample);
    float lp_magnitude = m_low_pass.calculate_magnitude(frequency_sample);

    float magnitude = fabs(hp_magnitude) - fabs(lp_magnitude);
    magnitude = (magnitude > 0) ? -magnitude : magnitude;

    return magnitude;
}

void BandPass::filter_analysis()
{
    calculate_centre_frequency();
    calculate_bandwidth();

    for (int frequency_sample = 1; frequency_sample < m_centre_frequency * 10; frequency_sample++)
    {
        m_magnitude_samples[frequency_sample] = calculate_magnitude(frequency_sample);
    }
}

void BandPass::show_filter_data()
{
    std::cout << "Center frequency[Hz]: " << m_centre_frequency << std::endl;
    std::cout << "Bandwidth[Hz]: " << m_bandwidth << std::endl;

    m_high_pass.show_filter_data();
    m_low_pass.show_filter_data();
}
