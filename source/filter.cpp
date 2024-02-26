#include "../include/filter.h"


Filter::Filter(float resistance, float capacitance)
{
    m_resistance = resistance;
    m_capacitance = capacitance;
    m_cutoff_frequency = 0;
}

float Filter::calculate_cutoff_frequency(float resistance, float capacitance)
{
    /* input: resistance[KΩ], capacitance[uF] : return: [Hz] */
    return 1 / (2 * M_PI * (capacitance / M_UF_TO_F) * resistance);
}

void Filter::calculate_cutoff_frequency()
{
    m_cutoff_frequency = 1 / (2 * M_PI * (m_capacitance / M_UF_TO_F) * m_resistance);
}

float Filter::cutoff_frequency() const
{
    return m_cutoff_frequency;
}

void Filter::filter_analysis()
{
    calculate_cutoff_frequency();

    for (int frequency_sample = 1; frequency_sample < (int)m_cutoff_frequency * 10; frequency_sample++)
    {
        m_magnitude_samples[frequency_sample] = calculate_magnitude(frequency_sample);
    }
}

void Filter::show_filter_data()
{
    std::cout << "--Input data--" << std::endl;
    std::cout << "Resistance[Ω]: " << m_resistance << std::endl;
    std::cout << "Capacitance[uF]: " << m_capacitance << std::endl;
    std::cout << "Cutoff frequency[Hz]: " << m_cutoff_frequency << std::endl;
}

void Filter::show_magnitude()
{
    std::cout << "Magnitude[dB]:" << std::endl;

    for (auto magnitude : m_magnitude_samples)
    {
        std::cout << magnitude.first << " " << magnitude.second << std::endl;
    }
}
