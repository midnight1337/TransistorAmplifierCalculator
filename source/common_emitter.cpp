#include "../include/common_emitter.h"


CommonEmitter::CommonEmitter(Transistor *transistor, float vcc, float rc, float re, float rbc, float rbe) : Circuit(transistor, vcc)
{
    m_rbc = rbc;
    m_rbe = rbe;
    m_rc = rc;
    m_re = re;
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

void CommonEmitter::circuit_parameters()
{
    std::cout << "Input:" << std::endl;
    m_transistor->transistor_parameters();
    std::cout << "VCC[V]: " << m_vcc << std::endl;
    std::cout << "Rbc[kΩ]: " << m_rbc << std::endl;
    std::cout << "Rbe[kΩ]: " << m_rbe << std::endl;
    std::cout << "Rc[kΩ]: " << m_rc << std::endl;
    std::cout << "Re[kΩ]: " << m_re << std::endl;

    std::cout << "Output:" << std::endl;
    std::cout << "Vc[V]: " << m_vc << std::endl;
    std::cout << "Vb[V]: " << m_vb << std::endl;
    std::cout << "Ve[V]: " << m_ve << std::endl;
    std::cout << "Vce (Bias)[V]: " << m_vce << std::endl;
    std::cout << "Ic[mA]: " << m_ic << std::endl;
    std::cout << "Ib[mA]: " << m_ib << std::endl;
    std::cout << "Ie[mA]: " << m_ie << std::endl;
    std::cout << "Av (Voltage gain)[dB]: " << m_av << std::endl;
    std::cout << "Z_in[kΩ]: " << m_z_in << std::endl;
    std::cout << "Z_out[kΩ]: " << m_z_out << std::endl;
    std::cout << "r_pi[kΩ]: " << m_r_pi << std::endl;
    std::cout << "re_ac[kΩ]: " << m_re_ac << std::endl;
    std::cout << "gm[]: " << m_gm << std::endl;
}

void CommonEmitter::round_values()
{
    float* currents[] = {&m_ic, &m_ib, &m_ie};

    float* voltages[] = {&m_vc, &m_vb, &m_ve, &m_vce};

    float* resistances[] = {&m_rbe, &m_rbc, &m_rc, &m_re, &m_z_in, &m_z_out, &m_r_pi, &m_re_ac};

//    m_gm =
//
//    m_av =

//    for (float* current : currents)
//    {
//        *current = round(*current * 100.0) / 100.0;
//    }

    for (float* voltage : voltages)
    {
        *voltage = round(*voltage * 100.0) / 100.0;
    }

    for (float* resistance : resistances)
    {
        *resistance = *resistance / 1000;
    }
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
    /* DC analysis, no Emitter capacitor */
//    m_r_pi = ( m_transistor->current_gain() * ( m_re + m_re_ac ) );

    /* AC analysis, with Emitter capacitor (Two formulas) */
     m_r_pi = ( m_transistor->current_gain() * m_re );
//    m_r_pi = ( m_transistor->current_gain() / m_gm );
}

void CommonEmitter::calculate_input_impedance()
{
    float resistors[] = {m_rbe, m_rbc, m_r_pi};
    int resistors_count = sizeof(resistors) / sizeof(int);

    float equivalent_resistance = Resistor::calculate_in_parallel(resistors_count, resistors);

    m_z_in = equivalent_resistance;
}

void CommonEmitter::calculate_output_impedance()
{
    float resistors[] = {m_rc};

    int resistors_count = sizeof(resistors) / sizeof(int);

    float equivalent_resistance = Resistor::calculate_in_parallel(resistors_count, resistors);

    m_z_out = equivalent_resistance;
}

void CommonEmitter::calculate_voltage_gain()
{
    // DC analysis
//    m_av = ( m_z_out / ( m_re + m_re_ac ) );

    // AC analysis
    m_av = ( m_z_out / m_re_ac );
}

void CommonEmitter::determine_q_point()
{
    int ic_saturation = ( m_vcc / ( m_rc + m_re + m_re_ac ) );
    q_point = std::to_string(ic_saturation) + " / " + std::to_string(m_vce);
}
