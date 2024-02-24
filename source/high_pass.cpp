#include "../include/high_pass.h"


HighPass::HighPass(float resistance, float capacitance) : Filter(resistance, capacitance)
{}

float HighPass::calculate_magnitude(int frequency_sample)
{
    float capacitor_reactance = Capacitor::calculate_capacitive_reactance(m_capacitance, frequency_sample);

    float magnitude = m_resistance / sqrt((m_resistance * m_resistance) + (capacitor_reactance * capacitor_reactance));
    float magnitude_db = 20 * log10(magnitude);

    return magnitude_db;
}
