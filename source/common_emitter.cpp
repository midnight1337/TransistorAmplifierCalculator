#include "../include/common_emitter.h"


CommonEmitter::CommonEmitter(Transistor *transistor, float vcc, float rc, float re, float rbc, float rbe) : Circuit(transistor, vcc)
{
    m_rbc = rbc;
    m_rbe = rbe;
    m_rc = rc;
    m_re = re;
}

void CommonEmitter::calculate_data()
{
    calculate_base_voltage();
    calculate_base_current();
    calculate_collector_current();
    calculate_saturation_current();
    calculate_emitter_current();
    calculate_collector_voltage();
    calculate_emitter_voltage();
    calculate_bias_voltage();
    calculate_transistor_internal_emitter_resistance();
    calculate_transistor_transconductance();
    calculate_transistor_impedance();
    calculate_input_impedance();
    calculate_output_impedance();
    calculate_voltage_gain();
}

void CommonEmitter::calculate_base_voltage()
{
    /* Two formulas, (m_ve + transistor->vbe()) seems to be more precised, if so then this method can't be called as first  */
    m_vb = ((m_vcc * m_rbe / ( m_rbe + m_rbc)));

//    float vbe;
//    if (Bjt* transistor = dynamic_cast<Bjt*>(m_transistor))
//    {
//        vbe = transistor->vbe();
//    }
//    m_vb = m_ve + vbe;
}

void CommonEmitter::calculate_base_current()
{
    float nominator;

    float resistors[] = {m_rbe, m_rbc};
    int arg_count = sizeof(resistors) / sizeof(float);

    float equivalent_resistance = Resistor::calculate_in_parallel(arg_count, resistors);

    float denominator = (equivalent_resistance + ( static_cast<float>(m_transistor->current_gain() + 1) * m_re ));

    if (Bjt* transistor = dynamic_cast<Bjt*>(m_transistor))
    {
        nominator = m_vb - transistor->vbe();
    }

    m_ib = nominator / denominator;
}

void CommonEmitter::calculate_collector_voltage()
{
    m_vc = m_vcc - (m_ic * m_rc);
}

void CommonEmitter::calculate_collector_current()
{
    m_ic = static_cast<float>(m_transistor->current_gain()) * m_ib;
}

void CommonEmitter::calculate_emitter_voltage()
{
    m_ve = m_ie * m_re;
}

void CommonEmitter::calculate_emitter_current()
{
    m_ie = m_ic + m_ib;
}

void CommonEmitter::calculate_saturation_current()
{
    m_ic_sat = m_vcc / (m_rc + m_re);
}

void CommonEmitter::calculate_bias_voltage()
{
    m_vce = m_vc - m_ve;
}

void CommonEmitter::calculate_transistor_internal_emitter_resistance()
{
    /* AC analysis, bypass through Emitter capacitor */
    if (Bjt* transistor = dynamic_cast<Bjt*>(m_transistor))
    {
        m_re_ac = transistor->vt() / m_ie;
    }
}

void CommonEmitter::calculate_transistor_transconductance()
{
    if (Bjt* transistor = dynamic_cast<Bjt*>(m_transistor))
    {
        m_gm = m_ie / transistor->vt();
    }
}

void CommonEmitter::calculate_transistor_impedance()
{
    /* DC analysis, no bypass through Emitter capacitor */
    m_rpi_dc = (static_cast<float>(m_transistor->current_gain()) * (m_re + m_re_ac));

    /* AC analysis, bypass through Emitter capacitor (Two valid formulas) */
    //    m_rpi_ac = (static_cast<float>(m_transistor->current_gain()) / m_gm );
    m_rpi_ac = (static_cast<float>(m_transistor->current_gain()) * m_re_ac);
}

void CommonEmitter::calculate_voltage_gain()
{
    // DC analysis, no bypass through Emitter capacitor
    m_av_dc = (m_z_out / (m_re + m_re_ac));

    m_av_dc_db = 20 * log10(m_av_dc);

    /* AC analysis, bypass through Emitter capacitor (Two valid formulas) */
//    m_av_ac = m_gm * m_z_out;
    m_av_ac = (m_z_out / m_re_ac);

    m_av_ac_db = 20 * log10(m_av_ac);
}

void CommonEmitter::calculate_input_impedance()
{
    float resistors[] = {m_rbe, m_rbc, m_rpi_ac};
    int arg_count = sizeof(resistors) / sizeof(float);

    float equivalent_resistance = Resistor::calculate_in_parallel(arg_count, resistors);

    m_z_in = equivalent_resistance;
}

void CommonEmitter::calculate_output_impedance()
{
    /* Add here R LOAD?? */
    float resistors[] = {m_rc};
    int arg_count = sizeof(resistors) / sizeof(float);

    float equivalent_resistance = Resistor::calculate_in_parallel(arg_count, resistors);

    m_z_out = equivalent_resistance;
}

void CommonEmitter::convert_data()
{
    m_ib = m_ib * 1000000;  // Convert from A to uA
    m_ic = m_ic * 1000;     // Convert from A to mA
    m_ie = m_ie * 1000;     // Convert from A to mA
    m_ic_sat = m_ic_sat * 1000; // Convert from A to mA
    m_gm = round(m_gm * 10000.0) / 10000.0;     // Convert from ? to four decimal places

    // Change given resistances into KOHMS
    float* resistances_to_kohms[] = {&m_rbe, &m_rbc, &m_rc, &m_re, &m_z_in, &m_z_out, &m_rpi_ac, &m_rpi_dc};

    // Convert given data into two decimal float
    float* convert_data[] = {&m_vc, &m_vb, &m_ve, &m_ic, &m_ib, &m_ie, &m_ic_sat,
                             &m_vce, &m_rbe, &m_rbc, &m_rc, &m_re, &m_z_in, &m_z_out,
                             &m_rpi_ac, &m_rpi_dc, &m_re_ac, &m_av_ac};

    for (float* resistance : resistances_to_kohms)
    {
        *resistance = *resistance / 1000;
    }

    for (float* data : convert_data)
    {
        *data = round(*data * 100.0) / 100.0;
    }
}

void CommonEmitter::circuit_data()
{
    std::cout << "--Input data--" << std::endl;
    m_transistor->transistor_parameters();
    std::cout << "VCC[V]: " << m_vcc << std::endl;
    std::cout << "Rbc[kΩ]: " << m_rbc << std::endl;
    std::cout << "Rbe[kΩ]: " << m_rbe << std::endl;
    std::cout << "Rc[kΩ]: " << m_rc << std::endl;
    std::cout << "Re[kΩ]: " << m_re << std::endl;

    std::cout << "\n--Output data--" << std::endl;
    std::cout << "Vc[V]: " << m_vc << std::endl;
    std::cout << "Vb[V]: " << m_vb << std::endl;
    std::cout << "Ve[V]: " << m_ve << std::endl;
    std::cout << "Vce[V] (bias): " << m_vce << std::endl;
    std::cout << "Ic[mA]: " << m_ic << std::endl;
    std::cout << "Ib[uA]: " << m_ib << std::endl;
    std::cout << "Ie[mA]: " << m_ie << std::endl;
    std::cout << "Ic[mA] (saturation): " << m_ic_sat << std::endl;
    std::cout << "gm[?]: " << m_gm << std::endl;
    std::cout << "Z_in[kΩ]: " << m_z_in << std::endl;
    std::cout << "Z_out[kΩ]: " << m_z_out << std::endl;
    std::cout << "q_point[Ic(sat)/Vcc|Ic/Vce]: " << m_ic_sat << "/" << m_vcc << " | " << m_ic << "/" << m_vce << std::endl;

    std::cout << "\n--Output data DC analysis--" << std::endl;
    std::cout << "Av_dc (Voltage gain): " << m_av_dc << std::endl;
    std::cout << "Av_dc[dB]: " << m_av_dc_db << std::endl;
    std::cout << "r_pi_dc[kΩ]: " << m_rpi_dc << std::endl;

    std::cout << "\n--Output data AC analysis--" << std::endl;
    std::cout << "Av_ac (Voltage gain): " << m_av_ac << std::endl;
    std::cout << "Av_ac[dB]: " << m_av_ac_db << std::endl;
    std::cout << "re_ac[Ω]: " << m_re_ac << std::endl;
    std::cout << "rpi_ac[kΩ]: " << m_rpi_ac << std::endl;
}
