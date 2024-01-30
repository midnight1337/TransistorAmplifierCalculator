#include "../include/common_emitter.h"


CommonEmitter::CommonEmitter(Bjt *transistor, Resistor *resistor, Capacitor *capacitor, float vcc) :
Circuit(transistor, resistor, capacitor, vcc) {}

void CommonEmitter::calculate_data()
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

void CommonEmitter::frequency_analysis(int frequency_start, int frequency_stop)
{
    for (int frequency_sample = frequency_start; frequency_sample < frequency_stop; frequency_sample++)
    {
//        calculate_input_impedance(frequency_sample);
//        calculate_output_impedance(frequency_sample);
        calculate_voltage_gain(frequency_sample);
//        calculate_magnitude_of_input_stage(frequency_sample);
//        calculate_magnitude_of_output_stage(frequency_sample);
    }
}

void CommonEmitter::calculate_base_voltage()
{
    /* Two formulas, (m_ve + transistor->vbe()) seems to be more precised, if so then this method can't be called as first  */
//    m_vb = m_ve + transistor->vbe();
    float nominator = m_vcc * m_resistor->base_emitter_resistor();
    float denominator = m_resistor->base_emitter_resistor() + m_resistor->base_collector_resistor();

    m_vb = nominator / denominator;
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

void CommonEmitter::calculate_collector_current()
{
    m_ic = static_cast<float>(m_transistor->current_gain()) * m_ib;
}

void CommonEmitter::calculate_emitter_current()
{
    m_ie = m_ic + m_ib;
}

void CommonEmitter::calculate_saturation_current()
{
    m_ic_sat = m_vcc / (m_resistor->collector_resistor() + m_resistor->emitter_resistor());
}

void CommonEmitter::calculate_collector_voltage()
{
    m_vc = m_vcc - (m_ic * m_resistor->collector_resistor());
}

void CommonEmitter::calculate_emitter_voltage()
{
    m_ve = m_ie * m_resistor->emitter_resistor();
}

void CommonEmitter::calculate_bias_voltage()
{
    m_vce = m_vc - m_ve;
}

void CommonEmitter::calculate_transistor_internal_emitter_resistance()
{
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

void CommonEmitter::calculate_voltage_gain()
{
    // DC analysis, no bypass through Emitter capacitor
    m_av_dc = (m_z_out / (m_resistor->emitter_resistor() + m_re_ac));

    /* AC analysis, bypass through Emitter capacitor (Two valid formulas) */
//    m_av_ac = m_gm * m_z_out;
    m_av_ac = (m_z_out / m_re_ac);

    m_av_dc_db = 20 * log10(m_av_dc);
    m_av_ac_db = 20 * log10(m_av_ac);
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

float CommonEmitter::calculate_input_impedance(int frequency_sample)
{
    // 1.Calculate reactance of 'Cb'
    float xc = Capacitor::calculate_reactance(m_capacitor->base_capacitor(), frequency_sample);

    // 2.Calculate impedance of transistor
    float transistor_impedance = calculate_transistor_impedance(frequency_sample);

    // 3.Calculate parallel resistance of the transistor impedance and the circuit
    float resistors[] = {m_resistor->base_emitter_resistor(), m_resistor->base_collector_resistor(), transistor_impedance};
    int arg_count = sizeof(resistors) / sizeof(float);
    float in_parallel = Resistor::calculate_in_parallel(arg_count, resistors);

    // 4.Calculate input impedance of the circuit
    float impedance = (in_parallel + xc);

    // 5.Plot (X: impedance, Y: frequency)
    std::cout << "f[Hz]: " << frequency_sample << ", Z_in[KΩ]: " << impedance / 1000 << std::endl;

    return impedance;
}

float CommonEmitter::calculate_transistor_impedance(int frequency_sample)
{
    // 1.Calculate reactance of 'Ce'
    float xc = Capacitor::calculate_reactance(m_capacitor->emitter_capacitor(), frequency_sample);

    // 2.Calculate parallel resistance of Xc and Re
    float resistors[] = {m_resistor->emitter_resistor(), xc};
    int arg_count = sizeof(resistors) / sizeof(float);
    float in_parallel = Resistor::calculate_in_parallel(arg_count, resistors);

    // 3.Calculate series resistance of emitter leg and parallel Xc and Re
    float in_series = in_parallel + m_re_ac;

    // 4.Calculate transistor impedance
    float impedance = static_cast<float>(m_transistor->current_gain()) * in_series;

    // 5.Plot (X: impedance, Y: frequency)
//    std::cout << "f[Hz]: " << frequency_sample << ", Rpi[KΩ]: " << impedance << std::endl;

    return impedance;
}

float CommonEmitter::calculate_output_impedance(int frequency_sample)
{
    // 1.Calculate reactance of 'Cc' for given frequency sample
    float xc = Capacitor::calculate_reactance(m_capacitor->collector_capacitor(), frequency_sample);

    // 2.Calculate in series resistance of Xc and Rl (TODO: Should Rl be included in series with xc??)
    float in_series = xc + m_resistor->load_resistor();

    // 3.Calculate output impedance, Z = Rc || ( Xc + Rl )
    float resistances[] = {m_resistor->collector_resistor(), in_series};
    int arg_count = sizeof(resistances) / sizeof(float);

    float impedance = Resistor::calculate_in_parallel(arg_count, resistances);
//    float impedance = m_resistor->collector_resistor() / 1000;

    // 5.Plot  (X: impedance, Y: frequency)
    std::cout << "f[Hz]: " << frequency_sample << ", Z_out[KΩ]: " << impedance / 1000 << std::endl;

    return impedance;
}

float CommonEmitter::calculate_voltage_gain(int frequency_sample)
{
    // 1.Calculate reactance of Ce and Cc
    float xc_ce = Capacitor::calculate_reactance(m_capacitor->emitter_capacitor(), frequency_sample);
    float xc_cc = Capacitor::calculate_reactance(m_capacitor->collector_capacitor(), frequency_sample);

    // 2.Calculate impedance of emitter
    float resistances_emitter[] = {m_resistor->emitter_resistor(), xc_ce};
    int arg_count_emitter = sizeof(resistances_emitter) / sizeof(float);
    float in_parallel_emitter = Resistor::calculate_in_parallel(arg_count_emitter, resistances_emitter);

    float emitter_impedance = in_parallel_emitter + m_re_ac;

    // 3.Calculate output impedance of collector (TODO: Should Rl and Xc be included in series??)
//        float in_series = xc_cc;
    float in_series = xc_cc + m_resistor->load_resistor();

    float resistances_collector[] = {m_resistor->collector_resistor(), in_series};
    int arg_count_collector = sizeof(resistances_emitter) / sizeof(float);

//        float collector_impedance = Resistor::calculate_in_parallel(arg_count_collector, resistances_collector);
    float collector_impedance = m_resistor->collector_resistor();
//    float collector_impedance = calculate_output_impedance(frequency_sample);

    // 4.Calculate voltage gain
    float voltage_gain_of_transistor = collector_impedance / emitter_impedance;

    // Convert to dB (TODO: absolute value of loss)
    float voltage_gain_of_transistor_db = 20 * log10(voltage_gain_of_transistor);
    float input_loss_db = calculate_magnitude_of_input_stage(frequency_sample);
    float output_stage_loss_db = calculate_magnitude_of_output_stage(frequency_sample);

    // Determine voltage gain
    float voltage_gain_db = voltage_gain_of_transistor_db + input_loss_db + output_stage_loss_db;

    if (voltage_gain_db < 0) { voltage_gain_db = 0; }

    //6. Plot (X: voltage gain[dB], Y: frequency)
    std::cout << "f[Hz]: " << frequency_sample << ", Av[dB]: " << voltage_gain_db << std::endl;

    return voltage_gain_db;
}

float CommonEmitter::calculate_magnitude_of_input_stage(int frequency_sample)
{
    // TODO: Ib should be recalculate according to frequency??
    // 1.Calculate Xc of Cb
    float xc = Capacitor::calculate_reactance(m_capacitor->base_capacitor(), frequency_sample);

    // 2.Calculate impedance of transistor
    float transistor_impedance = calculate_transistor_impedance(frequency_sample);

    // 3.Calculate input impedance of circuit, not including Cb
    float resistors[] = {m_resistor->base_emitter_resistor(), m_resistor->base_collector_resistor(), transistor_impedance};
    int arg_count = sizeof(resistors) / sizeof(float);
    float impedance = Resistor::calculate_in_parallel(arg_count, resistors);

    // 4.Calculate cutoff frequency
    float cutoff_frequency = Filter::high_pass(impedance, m_capacitor->base_capacitor());

    // Calculate loss ratio
    float loss_ratio = impedance / (xc + impedance);

    // Calculate loss and magnitude (these both loss and magnitude produces same output)
    float loss = impedance / (pow((impedance * impedance) + (xc * xc), 0.5));
    float loss_db = 20 * log10(loss);

    float magnitude_numerator = 2 * 3.14 * frequency_sample;
    float magnitude_denumerator = pow((pow((2 * 3.14 * frequency_sample), 2) + pow((2 * 3.14 * cutoff_frequency), 2)), 0.5);

    float magnitude = magnitude_numerator / magnitude_denumerator;
    float magnitude_db = 20 * log10(magnitude);

    std::cout << "f[Hz]: " << frequency_sample << ", Ratio(Xc/Zin): " << loss_ratio << ", Loss: " << loss
              << ", Loss[dB]" << loss_db << ", Magnitude: " << magnitude << ", Magnitude[dB]: " << magnitude_db << std::endl;

    return magnitude_db;
}

float CommonEmitter::calculate_magnitude_of_output_stage(int frequency_sample)
{
    float xc = Capacitor::calculate_reactance(m_capacitor->collector_capacitor(), frequency_sample);

    // Calculate loss ratio
    float loss_ratio = m_resistor->load_resistor() / (xc + m_resistor->load_resistor());

    // Calculate loss and magnitude (these both loss and magnitude produces same output)
    float loss = m_resistor->load_resistor() / (pow((m_resistor->load_resistor() * m_resistor->load_resistor()) + (xc * xc), 0.5));
    float loss_db = 20 * log10(loss);

    std::cout << "f[Hz]: " << frequency_sample << ", Ratio(Xc/Zin): " << loss_ratio << ", Loss: " << loss << ", Loss[dB]" << loss_db << std::endl;

    return loss_db;
}

void CommonEmitter::convert_data()
{
    m_ib = m_ib * 1000000;  // Convert from A to uA
    m_ic = m_ic * 1000;     // Convert from A to mA
    m_ie = m_ie * 1000;     // Convert from A to mA
    m_ic_sat = m_ic_sat * 1000; // Convert from A to mA
    m_gm = round(m_gm * 10000.0) / 10000.0;     // Convert from ? to four decimal places

    float *resistances_to_kohms[] = {&m_z_in, &m_z_out, &m_rpi_ac, &m_rpi_dc};

    // Convert given data into two decimal float
    float *convert_data[] = {&m_vc, &m_vb, &m_ve, &m_ic, &m_ib, &m_ie, &m_ic_sat, &m_vce,
                             &m_z_in, &m_z_out, &m_rpi_ac, &m_rpi_dc, &m_re_ac, &m_av_ac,
                             &m_av_dc, &m_av_ac_db, &m_av_dc_db, &m_fc_in, &m_fc_out, &m_fc_emitter};

    for (float *resistance: resistances_to_kohms) {
        *resistance = *resistance / 1000;
    }

    for (float *data: convert_data) {
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
    std::cout << "Q_point: " << m_ic_sat << "/" << m_vcc << "[Ic(sat)/Vcc] | " << m_ic << "/" << m_vce << "[Ic/Vce]"
              << std::endl;

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
