#include "../include/common_emitter.h"

CommonEmitter::CommonEmitter() {}

CommonEmitter::CommonEmitter(Transistor *transistor, int vcc, int rc, int re, int rbc, int rbe) : Circuit(transistor, vcc, rc, re)
{
    m_rbc = rbc;
    m_rbe = rbe;
}

void CommonEmitter::calculate()
{
    calculate_base_voltage();
    calculate_base_current();
    calculate_collector_current();
    calculate_emitter_current();
    calculate_collector_voltage();
    calculate_emitter_voltage();
    calculate_bias_voltage();
    calculate_internal_emitter_resistance();
    calculate_voltage_gain();
    calculate_transistor_impedance();
    calculate_input_impedance();
    calculate_output_impedance();
    determine_q_point();
}

void CommonEmitter::calculate_base_voltage()
{
    m_vb = ( m_vcc * ( m_rbe / ( m_rbe + m_rbc ) ) );
}

void CommonEmitter::calculate_base_current()
{
    float nominator;
    // ((m_rbe * m_rbc) / (m_rbe + m_rbc))

    float resistors[] = {m_rbe, m_rbc};
    int resistors_count = sizeof(resistors) / sizeof(int);

    float equivalent_resistance = Resistor::calculate_in_parallel(resistors_count, resistors);

    float denominator = ( equivalent_resistance + ( (m_transistor->current_gain() + 1) * m_re ) );

    if (Bjt* transistor = dynamic_cast<Bjt*>(m_transistor))
    {
        nominator = m_vb - transistor->vbe();
    }

   m_ib = nominator / denominator;
}

void CommonEmitter::calculate_collector_voltage()
{
    m_vc = m_vcc - ( m_ic * m_rc );
}

void CommonEmitter::calculate_collector_current()
{
    m_ic = m_transistor->current_gain() * m_ib;
}

void CommonEmitter::calculate_emitter_voltage()
{
    m_ve = m_ie * m_re;
}

void CommonEmitter::calculate_emitter_current()
{
    m_ie = m_ic + m_ib;
}

void CommonEmitter::calculate_bias_voltage()
{
    m_vce = m_vc - m_ve;
}

void CommonEmitter::calculate_internal_emitter_resistance()
{
    if (Bjt* transistor = dynamic_cast<Bjt*>(m_transistor))
    {
        m_re_ac = transistor->vt() / m_ie;
    }
}

void CommonEmitter::calculate_transistor_impedance()
{
    // DC analysis, no Emitter capacitor
//    m_rpi = ( m_transistor->current_gain() * ( m_re + m_re_ac ) );

    // AC analysis, with Emitter capacitor (Two formulas)
    m_rpi = ( m_transistor->current_gain() * m_re );
//    m_rpi = ( m_transistor->current_gain() / m_gm );
}

void CommonEmitter::calculate_input_impedance()
{
    float resistors[] = {m_rbe, m_rbc, m_rpi};
    int resistors_count = sizeof(resistors) / sizeof(int);

    float equivalent_resistance = Resistor::calculate_in_parallel(resistors_count, resistors);

    m_z_in = equivalent_resistance;
}

void CommonEmitter::calculate_output_impedance()
{
    float resistors[] = {m_rc, m_rl};
    int resistors_count = sizeof(resistors) / sizeof(int);

    float equivalent_resistance = Resistor::calculate_in_parallel(resistors_count, resistors);

    m_z_out = equivalent_resistance;
}

void CommonEmitter::calculate_voltage_gain()
{
    // DC analysis
    m_av = ( m_z_out / ( m_re + m_re_ac ) );

    // AC analysis
    m_av = ( m_z_out / m_re_ac );
}

void CommonEmitter::determine_q_point()
{
    int ic_saturation = ( m_vcc / ( m_rc + m_re + m_re_ac ) );
    q_point = std::to_string(ic_saturation) + " / " + std::to_string(m_vce);
}
