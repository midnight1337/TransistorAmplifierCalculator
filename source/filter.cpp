#include "../include/filter.h"


Filter::Filter(float first_order_resistance, float first_order_capacitance)
{
    m_first_order_resistance = first_order_capacitance;
    m_first_order_capacitance = first_order_capacitance;
}

Filter::Filter(float first_order_resistance, float first_order_capacitance, float second_order_resistance, float second_order_capacitance)
{
    m_first_order_resistance = first_order_capacitance;
    m_first_order_capacitance = first_order_capacitance;
    m_second_order_resistance = second_order_resistance;
    m_second_order_capacitance = second_order_capacitance;
}

float Filter::calculate_first_order_filter_cutoff_frequency(float first_order_resistance, float first_order_capacitance)
{
    /* input: resistance[KΩ], capacitance[uF] : return: [Hz] */
    return 1 / (2 * M_PI * (first_order_capacitance / M_UF_TO_F) * first_order_resistance);
}

float Filter::calculate_second_order_filter_cutoff_frequency(float first_order_resistance, float first_order_capacitance, float second_order_resistance, float second_order_capacitance)
{
    /* input: resistance[Ω], capacitance[uF] : return: [Hz] */
    return 1 / (2 * M_PI * sqrt((first_order_capacitance / M_UF_TO_F) * first_order_resistance * (second_order_capacitance / M_UF_TO_F) * second_order_resistance));
}

void Filter::show_data()
{
    std::cout << "--Input data--" << std::endl;
    std::cout << "Resistance[Ω]: " << nullptr << std::endl;
    std::cout << "Capacitance[uF]: " << nullptr << std::endl;

    std::cout << "\n--Output data--" << std::endl;
    std::cout << "Cutoff frequency[Hz]: " << m_cutoff_frequency << std::endl;
    std::cout << "Magnitude[dB]:" << std::endl;

    for (auto magnitude : m_magnitude_samples)
    {
        std::cout << magnitude.first << " " << magnitude.second << std::endl;
    }
}

float Filter::calculate_band_pass_filter_centre_frequency()
{
    float low_pass_filter_cutoff_frequency = calculate_first_order_filter_cutoff_frequency(m_first_order_resistance, m_first_order_capacitance);
    float high_pass_filter_cutoff_frequency = calculate_first_order_filter_cutoff_frequency(m_second_order_resistance, m_second_order_capacitance);
    float centre_frequency = sqrt(low_pass_filter_cutoff_frequency * high_pass_filter_cutoff_frequency);

    return centre_frequency;
}

float Filter::calculate_first_order_high_pass_filter_magnitude(int frequency_sample)
{
    float capacitor_reactance = Capacitor::calculate_capacitive_reactance(m_first_order_capacitance, frequency_sample);

    float magnitude = m_first_order_resistance / sqrt((m_first_order_resistance * m_first_order_resistance) + (capacitor_reactance * capacitor_reactance));
    float magnitude_db = 20 * log10(magnitude);

    return magnitude_db;
}

float Filter::calculate_first_order_low_pass_filter_magnitude(int frequency_sample)
{
    float capacitor_reactance = Capacitor::calculate_capacitive_reactance(m_first_order_capacitance, frequency_sample);

    float magnitude = capacitor_reactance / sqrt((m_first_order_resistance * m_first_order_resistance) + (capacitor_reactance * capacitor_reactance));
    float magnitude_db = 20 * log10(magnitude);

    return magnitude_db;
}

float Filter::calculate_second_order_high_pass_filter_magnitude(int frequency_sample)
{
    float first_order_capacitor_reactance = Capacitor::calculate_capacitive_reactance(m_first_order_capacitance, frequency_sample);
    float first_order_magnitude = m_first_order_resistance / sqrt((m_first_order_resistance * m_first_order_resistance) + (first_order_capacitor_reactance * first_order_capacitor_reactance));
    float first_order_magnitude_db = 20 * log10(first_order_magnitude);

    float second_order_capacitor_reactance = Capacitor::calculate_capacitive_reactance(m_second_order_capacitance, frequency_sample);
    float second_order_magnitude = m_second_order_resistance / sqrt((m_second_order_resistance * m_second_order_resistance) + (second_order_capacitor_reactance * second_order_capacitor_reactance));
    float second_order_magnitude_db = 20 * log10(second_order_magnitude);

    return first_order_magnitude_db + second_order_magnitude_db;
}

float Filter::calculate_second_order_low_pass_filter_magnitude(int frequency_sample)
{
    float first_order_capacitor_reactance = Capacitor::calculate_capacitive_reactance(m_first_order_capacitance, frequency_sample);
    float first_order_magnitude = first_order_capacitor_reactance / sqrt((m_first_order_resistance * m_first_order_resistance) + (first_order_capacitor_reactance * first_order_capacitor_reactance));
    float first_order_magnitude_db = 20 * log10(first_order_magnitude);

    float second_order_capacitor_reactance = Capacitor::calculate_capacitive_reactance(m_second_order_capacitance, frequency_sample);
    float second_order_magnitude = second_order_capacitor_reactance / sqrt((m_second_order_resistance * m_second_order_resistance) + (second_order_capacitor_reactance * second_order_capacitor_reactance));
    float second_order_magnitude_db = 20 * log10(second_order_magnitude);

    return first_order_magnitude_db + second_order_magnitude_db;
}

void Filter::frequency_analysis_of_first_order_high_pass_filter()
{
    m_cutoff_frequency = calculate_first_order_filter_cutoff_frequency(m_first_order_resistance, m_first_order_capacitance);

    for (int frequency_sample = 1; frequency_sample < (int)m_cutoff_frequency * 2; frequency_sample++)
    {
        m_magnitude_samples[frequency_sample] = calculate_first_order_high_pass_filter_magnitude(frequency_sample);
    }
}

void Filter::frequency_analysis_of_first_order_low_pass_filter()
{
    m_cutoff_frequency = calculate_first_order_filter_cutoff_frequency(m_first_order_resistance, m_first_order_capacitance);

    for (int frequency_sample = 1; frequency_sample < (int)m_cutoff_frequency * 2; frequency_sample++)
    {
        m_magnitude_samples[frequency_sample] = calculate_first_order_low_pass_filter_magnitude(frequency_sample);
    }
}

void Filter::frequency_analysis_of_second_order_high_pass_filter()
{
    m_cutoff_frequency = calculate_second_order_filter_cutoff_frequency(m_first_order_resistance, m_first_order_capacitance, m_second_order_resistance, m_second_order_capacitance);

    for (int frequency_sample = 1; frequency_sample < (int)m_cutoff_frequency * 2; frequency_sample++)
    {
        m_magnitude_samples[frequency_sample] = calculate_second_order_high_pass_filter_magnitude(frequency_sample);
    }
}

void Filter::frequency_analysis_of_second_order_low_pass_filter()
{
    m_cutoff_frequency = calculate_second_order_filter_cutoff_frequency(m_first_order_resistance, m_first_order_capacitance, m_second_order_resistance, m_second_order_capacitance);

    for (int frequency_sample = 1; frequency_sample < (int)m_cutoff_frequency * 2; frequency_sample++)
    {
        m_magnitude_samples[frequency_sample] = calculate_second_order_low_pass_filter_magnitude(frequency_sample);
    }
}

void Filter::frequency_analysis_of_band_pass_filter()
{
    float low_pass_filter_cutoff_frequency = calculate_first_order_filter_cutoff_frequency(m_first_order_resistance, m_first_order_capacitance);
    float high_pass_filter_cutoff_frequency = calculate_first_order_filter_cutoff_frequency(m_second_order_resistance, m_second_order_capacitance);
    float centre_frequency = calculate_band_pass_filter_centre_frequency();

    for (int frequency_sample = 1; frequency_sample < centre_frequency; frequency_sample++)
    {
        m_magnitude_samples[frequency_sample] = ;
        m_magnitude_samples[centre_frequency * 2 - frequency_sample - 1] = ;
    }
}
