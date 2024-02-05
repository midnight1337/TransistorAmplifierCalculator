#include "../include/collector_feedback.h"


CollectorFeedback::CollectorFeedback(Bjt *transistor, Resistor *resistor, Capacitor *capacitor, float vcc) : Circuit(transistor, resistor, capacitor, vcc)
{

}

void CollectorFeedback::calculate_data()
{
    calculate_base_voltage();
    calculate_base_current();
    calculate_collector_current();
    calculate_emitter_current();
    calculate_saturation_current();
    calculate_collector_voltage();
    calculate_emitter_voltage();
    calculate_bias_voltage();
    calculate_transistor_internal_emitter_resistance();
    calculate_transistor_transconductance();
    calculate_transistor_impedance();
    calculate_input_impedance();
    calculate_output_impedance();
    calculate_voltage_gain();
    calculate_cutoff_frequency_of_input_stage();
    calculate_cutoff_frequency_of_output_stage();
    calculate_cutoff_frequency_of_emitter_stage();
    frequency_analysis(1, 3000);
}

void CollectorFeedback::calculate_base_current()
{
    float nominator = m_vcc - m_transistor->vbe();
    float denominator = m_resistor->base_collector_resistor() + (m_transistor->current_gain() + 1) * (m_resistor->emitter_resistor() + m_resistor->collector_resistor());

    m_ib = nominator / denominator;
}

void CollectorFeedback::calculate_collector_current()
{
    m_ic = m_ib * static_cast<float>(m_transistor->current_gain());
}

void CollectorFeedback::calculate_emitter_current()
{
    m_ie = m_ic + m_ib;
}

void CollectorFeedback::calculate_emitter_voltage()
{
    m_ve = m_ie * m_resistor->emitter_resistor();
}

void CollectorFeedback::calculate_base_voltage()
{
    m_vb = m_ve + m_transistor->vbe();
}

void CollectorFeedback::calculate_collector_voltage()
{
    m_vc = m_vcc - (m_ic * m_resistor->collector_resistor());
}

void CollectorFeedback::calculate_bias_voltage()
{
    m_vce = m_vc - m_ve;
}

void CollectorFeedback::calculate_saturation_current()
{
    m_ic_sat = m_vcc / (m_resistor->collector_resistor() + m_resistor->emitter_resistor());
}
