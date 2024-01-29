#include "../include/common_emitter.h"


CommonEmitter::CommonEmitter(Bjt* transistor, Resistor* resistor, Capacitor* capacitor, float vcc) : Circuit(transistor, resistor, capacitor, vcc)
{}

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
    calculate_cutoff_frequency_of_input_stage();
    calculate_cutoff_frequency_of_output_stage();
    calculate_cutoff_frequency_of_emitter_stage();
//    input_impedance_frequency_analysis(1000);
//    output_impedance_frequency_analysis(1000);
//    voltage_gain_frequency_analysis(1000);
//    cutoff_frequency_input_stage_frequency_analysis(3000);
}

void CommonEmitter::calculate_base_voltage()
{
    /* Two formulas, (m_ve + transistor->vbe()) seems to be more precised, if so then this method can't be called as first  */
//    m_vb = m_ve + transistor->vbe();
    m_vb = ((m_vcc * m_resistor->base_emitter_resistor() / ( m_resistor->base_emitter_resistor() + m_resistor->base_collector_resistor())));
}

void CommonEmitter::calculate_base_current()
{
    float nominator = m_vb - m_transistor->vbe();

    float resistors[] = {m_resistor->base_emitter_resistor(), m_resistor->base_collector_resistor()};
    int arg_count = sizeof(resistors) / sizeof(float);

    float equivalent_resistance = Resistor::calculate_in_parallel(arg_count, resistors);

    float denominator = (equivalent_resistance + (static_cast<float>(m_transistor->current_gain() + 1) * m_resistor->emitter_resistor()));

    m_ib = nominator / denominator;
}

void CommonEmitter::calculate_collector_voltage()
{
    m_vc = m_vcc - (m_ic * m_resistor->collector_resistor());
}

void CommonEmitter::calculate_collector_current()
{
    m_ic = static_cast<float>(m_transistor->current_gain()) * m_ib;
}

void CommonEmitter::calculate_emitter_voltage()
{
    m_ve = m_ie * m_resistor->emitter_resistor();
}

void CommonEmitter::calculate_emitter_current()
{
    m_ie = m_ic + m_ib;
}

void CommonEmitter::calculate_saturation_current()
{
    m_ic_sat = m_vcc / (m_resistor->collector_resistor() + m_resistor->emitter_resistor());
}

void CommonEmitter::calculate_bias_voltage()
{
    m_vce = m_vc - m_ve;
}

void CommonEmitter::calculate_transistor_internal_emitter_resistance()
{
    /* AC analysis, bypass through Emitter capacitor */
    m_re_ac = m_transistor->vt() / m_ie;
}

void CommonEmitter::calculate_transistor_transconductance()
{
    m_gm = m_ie / m_transistor->vt();
}

void CommonEmitter::calculate_transistor_impedance()
{
    /* DC analysis, no bypass through Emitter capacitor */
    m_rpi_dc = (static_cast<float>(m_transistor->current_gain()) * (m_resistor->emitter_resistor() + m_re_ac));

    /* AC analysis, bypass through Emitter capacitor (Two valid formulas) */
//    m_rpi_ac = (static_cast<float>(m_transistor->current_gain() + 1) / m_gm);
    m_rpi_ac = (static_cast<float>(m_transistor->current_gain()) * m_re_ac);
}

void CommonEmitter::calculate_voltage_gain()
{
    // DC analysis, no bypass through Emitter capacitor
    m_av_dc = (m_z_out / (m_resistor->emitter_resistor() + m_re_ac));

    m_av_dc_db = 20 * log10(m_av_dc);

    /* AC analysis, bypass through Emitter capacitor (Two valid formulas) */
//    m_av_ac = m_gm * m_z_out;
    m_av_ac = (m_z_out / m_re_ac);

    m_av_ac_db = 20 * log10(m_av_ac);
}

void CommonEmitter::calculate_input_impedance()
{
    float resistors[] = {m_resistor->base_emitter_resistor(), m_resistor->base_collector_resistor(), m_rpi_ac};
    int arg_count = sizeof(resistors) / sizeof(float);

    m_z_in = Resistor::calculate_in_parallel(arg_count, resistors);
}

void CommonEmitter::calculate_output_impedance()
{
    /* Include Load Resistor */
//    float resistors[] = {m_resistor->collector_resistor(), m_resistor->load_resistor()};
//    int arg_count = sizeof(resistors) / sizeof(float);
//    m_z_out = Resistor::calculate_in_parallel(arg_count, resistors);

    /* No Load Resistor */
    m_z_out = m_resistor->collector_resistor();
}

void CommonEmitter::calculate_cutoff_frequency_of_input_stage()
{
    m_fc_in = Filter::high_pass(m_z_in, m_capacitor->base_capacitor());
}

void CommonEmitter::calculate_cutoff_frequency_of_output_stage()
{
    m_fc_out = Filter::high_pass(m_resistor->load_resistor(), m_capacitor->collector_capacitor());
}

void CommonEmitter::calculate_cutoff_frequency_of_emitter_stage()
{
    m_fc_emitter = Filter::high_pass(m_resistor->emitter_resistor(), m_capacitor->emitter_capacitor());
}

void CommonEmitter::input_impedance_frequency_analysis(int frequency_range)
{
    for (int frequency = 1; frequency < frequency_range; frequency++)
    {
        //1. Calculate reactance of 'Cb' for given frequency sample
        float xc = Capacitor::calculate_reactance(m_capacitor->base_capacitor(), frequency);

        //2. Calculate impedance of transistor for given frequency sample
        float transistor_impedance = transistor_impedance_frequency_analysis(frequency);

        //3. Calculate input impedance of circuit
        float resistors[] = {m_resistor->base_emitter_resistor(), m_resistor->base_collector_resistor(), transistor_impedance};
        int arg_count = sizeof(resistors) / sizeof(float);

        float in_parallel = Resistor::calculate_in_parallel(arg_count, resistors);

        float impedance = in_parallel + xc;

        //4. Plot sample (X: impedance, Y: frequency)
        std::cout << "f[Hz]: " << frequency << ", Z input[KΩ]: " << impedance / 1000 << std::endl;
    }
}

float CommonEmitter::transistor_impedance_frequency_analysis(int frequency_sample)
{
    //1. Calculate reactance of 'Ce' for given frequency sample
    float xc = Capacitor::calculate_reactance(m_capacitor->emitter_capacitor(), frequency_sample);

    //2. Calculate parallel resistance of Xc and Re
    float resistances[] = {m_resistor->emitter_resistor(), xc};
    int arg_count = sizeof(resistances) / sizeof(float);

    float in_parallel = Resistor::calculate_in_parallel(arg_count, resistances);

    //3. Calculate series resistance of emitter leg and parallel Xc and Re
    float in_series = in_parallel + m_re_ac;

    //4. Calculate transistor impedance
    return static_cast<float>(m_transistor->current_gain()) * in_series;
}

void CommonEmitter::output_impedance_frequency_analysis(int frequency_range)
{
    for (int frequency = 1; frequency < frequency_range; frequency++)
    {
        //1. Calculate reactance of 'Cc' for given frequency sample
        float xc = Capacitor::calculate_reactance(m_capacitor->collector_capacitor(), frequency);

        //2. Calculate output impedance
        float in_series = xc; // in_series: reactance + r_load

        float resistances[] = {m_resistor->collector_resistor(), in_series};
        int arg_count = sizeof(resistances) / sizeof(float);

        float impedance =  Resistor::calculate_in_parallel(arg_count, resistances);

        //3. Plot sample (X: impedance, Y: frequency)
        std::cout << "f[Hz]: " << frequency << ", Z output[KΩ]: " << impedance / 1000 << std::endl;
    }
}

void CommonEmitter::voltage_gain_frequency_analysis(int frequency_range)
{
    for (int frequency = 1; frequency < frequency_range; frequency++)
    {
        //1. Calculate reactance of Ce and Cc
        float xc_ce = Capacitor::calculate_reactance(m_capacitor->emitter_capacitor(), frequency);
        float xc_cc = Capacitor::calculate_reactance(m_capacitor->collector_capacitor(), frequency);

        //2. Calculate impedance of emitter
        float resistances_emitter[] = {m_resistor->emitter_resistor(), xc_ce};
        int arg_count_emitter = sizeof(resistances_emitter) / sizeof(float);

        float in_parallel_emitter = Resistor::calculate_in_parallel(arg_count_emitter, resistances_emitter);

        float emitter_impedance = in_parallel_emitter + m_re_ac;

        //3. Calculate impedance of collector
//        float in_series = xc_cc;
        float in_series = xc_cc + m_resistor->load_resistor();

        float resistances_collector[] = {m_resistor->collector_resistor(), in_series};
        int arg_count_collector = sizeof(resistances_emitter) / sizeof(float);

        float collector_impedance = Resistor::calculate_in_parallel(arg_count_collector, resistances_collector);
//        float collector_impedance = m_resistor->collector_resistor();

        //4. Calculate voltage gain
        float voltage_gain = collector_impedance / emitter_impedance;

        float voltage_gain_db = 20 * log10(voltage_gain);

        //5. Plot (X: voltage gain[dB], Y: frequency)
        std::cout << "f[Hz]: " << frequency << ", Av: " << voltage_gain << ", Av[dB]" << voltage_gain_db << std::endl;
    }
}

void CommonEmitter::cutoff_frequency_input_stage_frequency_analysis(int frequency_range)
{
    for (int frequency = 1; frequency < frequency_range; frequency++)
    {
        //1.Ib should be recalculate according to frequency??

        //2.Calculate impedance of transistor for given frequency sample
        float transistor_impedance = transistor_impedance_frequency_analysis(frequency);

        //3.Calculate input impedance of circuit without Cb
        float resistors[] = {m_resistor->base_emitter_resistor(), m_resistor->base_collector_resistor(), transistor_impedance};
        int arg_count = sizeof(resistors) / sizeof(float);

        float impedance = Resistor::calculate_in_parallel(arg_count, resistors);

        //4.Calculate cutoff frequency
        float cutoff_frequency = Filter::high_pass(impedance, m_capacitor->base_capacitor());

        std::cout << "f[Hz]: " << frequency << ", cutoff_frequency[Hz]: " << cutoff_frequency << std::endl;
    }
}

void CommonEmitter::convert_data()
{
    m_ib = m_ib * 1000000;  // Convert from A to uA
    m_ic = m_ic * 1000;     // Convert from A to mA
    m_ie = m_ie * 1000;     // Convert from A to mA
    m_ic_sat = m_ic_sat * 1000; // Convert from A to mA
    m_gm = round(m_gm * 10000.0) / 10000.0;     // Convert from ? to four decimal places

    float* resistances_to_kohms[] = {&m_z_in, &m_z_out, &m_rpi_ac, &m_rpi_dc};

    // Convert given data into two decimal float
    float* convert_data[] = {&m_vc, &m_vb, &m_ve, &m_ic, &m_ib, &m_ie, &m_ic_sat, &m_vce,
                             &m_z_in, &m_z_out, &m_rpi_ac, &m_rpi_dc, &m_re_ac, &m_av_ac,
                             &m_av_dc, &m_av_ac_db, &m_av_dc_db,&m_fc_in, &m_fc_out, &m_fc_emitter};

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
    m_resistor->resistors_values();
    m_capacitor->capacitors_values();
    std::cout << "VCC[V]: " << m_vcc << std::endl;

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
    std::cout << "fc_in(HP)[Hz]: " << m_fc_in << std::endl;
    std::cout << "fc_out(HP)[Hz]: " << m_fc_out << std::endl;
    std::cout << "fc_emitter(HP)[Hz]: " << m_fc_emitter << std::endl;
    std::cout << "Q_point: " << m_ic_sat << "/" << m_vcc << "[Ic(sat)/Vcc] | " << m_ic << "/" << m_vce << "[Ic/Vce]" << std::endl;

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
