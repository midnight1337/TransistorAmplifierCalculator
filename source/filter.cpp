#include "../include/filter.h"


Filter::Filter(float first_order_resistance, float first_order_capacitance)
{
    m_first_order_resistance = first_order_resistance;
    m_first_order_capacitance = first_order_capacitance;
}

Filter::Filter(float first_order_resistance, float first_order_capacitance, float second_order_resistance, float second_order_capacitance)
{
    m_first_order_resistance = first_order_resistance;
    m_first_order_capacitance = first_order_capacitance;
    m_second_order_resistance = second_order_resistance;
    m_second_order_capacitance = second_order_capacitance;
}

float Filter::calculate_first_order_filter_cutoff_frequency(float first_order_resistance, float first_order_capacitance)
{
    /* input: resistance[KΩ], capacitance[uF] : return: [Hz] */
    return 1 / (2 * M_PI * (first_order_capacitance / M_UF_TO_F) * first_order_resistance);
}

float Filter::calculate_second_order_filter_cutoff_frequency()
{
    /* input: resistance[Ω], capacitance[uF] : return: [Hz] */
    return 1 / (2 * M_PI * sqrt((m_first_order_capacitance / M_UF_TO_F) * m_first_order_resistance * (m_second_order_capacitance / M_UF_TO_F) * m_second_order_resistance));
}

float Filter::calculate_band_pass_filter_cutoff_frequency()
{
    return 0;
}


void Filter::calculate_first_order_high_pass_magnitude(int frequency_sample)
{
    float capacitor_reactance = Capacitor::calculate_capacitive_reactance(m_first_order_capacitance, frequency_sample);
    float magnitude = m_first_order_resistance / sqrt((m_first_order_resistance * m_first_order_resistance) + (capacitor_reactance * capacitor_reactance));
    float magnitude_db = 20 * log10(magnitude);

    m_magnitude_samples[frequency_sample] = magnitude_db;
}

void Filter::calculate_first_order_low_pass_magnitude(int frequency_sample)
{
    float capacitor_reactance = Capacitor::calculate_capacitive_reactance(m_first_order_capacitance, frequency_sample);
    float magnitude = capacitor_reactance / sqrt((m_first_order_resistance * m_first_order_resistance) + (capacitor_reactance * capacitor_reactance));
    float magnitude_db = abs(20 * log10(magnitude));

    m_magnitude_samples[frequency_sample] = magnitude_db;
}

void Filter::calculate_second_order_high_pass_magnitude(int frequency_sample)
{
    float first_order_capacitor_reactance = Capacitor::calculate_capacitive_reactance(m_first_order_capacitance, frequency_sample);
    float first_order_magnitude = m_first_order_resistance / sqrt((m_first_order_resistance * m_first_order_resistance) + (first_order_capacitor_reactance * first_order_capacitor_reactance));
    float first_order_magnitude_db = 20 * log10(first_order_magnitude);

    float second_order_capacitor_reactance = Capacitor::calculate_capacitive_reactance(m_second_order_capacitance, frequency_sample);
    float second_order_magnitude = m_second_order_resistance / sqrt((m_second_order_resistance * m_second_order_resistance) + (second_order_capacitor_reactance * second_order_capacitor_reactance));
    float second_order_magnitude_db = 20 * log10(second_order_magnitude);

    m_magnitude_samples[frequency_sample] = first_order_magnitude_db + second_order_magnitude_db;
}

void Filter::calculate_second_order_low_pass_magnitude(int frequency_sample)
{

}

void Filter::show_data()
{
    std::cout << "--Input data--" << std::endl;
    std::cout << "Resistance[Ω]: " << nullptr << std::endl;
    std::cout << "Capacitance[uF]: " << nullptr << std::endl;

    std::cout << "\n--Output data--" << std::endl;
    std::cout << "Cutoff frequency[Hz]: " << m_cutoff_frequency << std::endl;
    std::cout << "Loss[dB]:" << std::endl;
    // Access samples from hash map
    for (auto loss : m_magnitude_samples)
    {
        std::cout << loss.first << " " << loss.second << std::endl;
    }
}

void Filter::frequency_analysis()
{
//    m_cutoff_frequency = calculate_first_order_filter_cutoff_frequency(m_first_order_resistance, m_first_order_capacitance);
    m_cutoff_frequency = calculate_second_order_filter_cutoff_frequency();
    for (int frequency_sample = 0; frequency_sample < m_cutoff_frequency * 2; frequency_sample++)
    {
//        calculate_first_order_high_pass_magnitude(frequency_sample);
        calculate_second_order_high_pass_magnitude(frequency_sample);
    }
}
