#include "../include/common_emitter.h"


CommonEmitter::CommonEmitter(Bjt *transistor, Resistor *resistor, Capacitor *capacitor, float vcc) :
Circuit(transistor, resistor, capacitor, vcc)
{}

void CommonEmitter::calculate_base_voltage()
{
    /* Two formulas, (m_ve + transistor->vbe()) seems to be more precised, if so then this method can't be called as first  */
//    m_vb = m_ve + transistor->vbe();
    float nominator = m_vcc * m_resistor->base_emitter_resistance();
    float denominator = m_resistor->base_emitter_resistance() + m_resistor->base_collector_resistance();

    m_vb = nominator / denominator;
}

void CommonEmitter::calculate_base_current()
{
    std::vector<float> resistors = {m_resistor->base_emitter_resistance(), m_resistor->base_collector_resistance()};
    float total_resistance_in_parallel = Resistor::calculate_resistance_in_parallel(resistors);

    float nominator = m_vb - m_transistor->vbe();
    float denominator = (total_resistance_in_parallel + (m_transistor->hfe() + 1) * m_resistor->emitter_resistance());

    m_ib = nominator / denominator;
}

void CommonEmitter::calculate_collector_current()
{
    m_ic = m_transistor->hfe() * m_ib;
}

void CommonEmitter::calculate_emitter_current()
{
    m_ie = m_ic + m_ib;
}

void CommonEmitter::calculate_saturation_current()
{
    m_ic_sat = m_vcc / (m_resistor->collector_resistance() + m_resistor->emitter_resistance() + m_re_ac);
}

void CommonEmitter::calculate_collector_voltage()
{
    m_vc = m_vcc - (m_ic * m_resistor->collector_resistance());
}

void CommonEmitter::calculate_emitter_voltage()
{
    m_ve = m_ie * m_resistor->emitter_resistance();
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
    m_rpi_dc = ((m_transistor->hfe() + 1) * (m_resistor->emitter_resistance() + m_re_ac));

    /* AC analysis, bypass through Emitter capacitor (Two valid formulas) */
//    m_rpi_ac = (m_transistor->hfe() + 1) / m_gm;
    m_rpi_ac = ((m_transistor->hfe() + 1) * m_re_ac);
}

void CommonEmitter::calculate_input_impedance()
{
    std::vector<float> resistors = {m_resistor->base_emitter_resistance(), m_resistor->base_collector_resistance(), m_rpi_ac};

    m_z_in = Resistor::calculate_resistance_in_parallel(resistors);
}

void CommonEmitter::calculate_output_impedance()
{
    std::vector<float> resistors = {m_resistor->collector_resistance(), m_resistor->load_resistance()};

    m_z_out = Resistor::calculate_resistance_in_parallel(resistors);
}

void CommonEmitter::calculate_voltage_gain()
{
    /* DC analysis, no bypass through Emitter capacitor */
    m_av_dc = (m_z_out / (m_resistor->emitter_resistance() + m_re_ac));

    /* AC analysis, bypass through Emitter capacitor (Two valid formulas) */
//    m_av_ac = m_gm * m_z_out;
    m_av_ac = (m_z_out / m_re_ac);

    m_av_dc_db = 20 * log10(m_av_dc);
    m_av_ac_db = 20 * log10(m_av_ac);
}

void CommonEmitter::calculate_cutoff_frequency_of_input_stage()
{
    m_fc_in = Filter::calculate_first_order_filter_cutoff_frequency(m_z_in, m_capacitor->base_capacitance());
}

void CommonEmitter::calculate_cutoff_frequency_of_output_stage()
{
    m_fc_out = Filter::calculate_first_order_filter_cutoff_frequency(m_resistor->load_resistance(),
                                                                     m_capacitor->collector_capacitance());
}

void CommonEmitter::calculate_cutoff_frequency_of_emitter_stage()
{
    m_fc_emitter = Filter::calculate_first_order_filter_cutoff_frequency(m_resistor->emitter_resistance(),
                                                                         m_capacitor->emitter_capacitance());
}

float CommonEmitter::calculate_input_impedance(int frequency_sample)
{
    /* 1.Calculate base capacitor reactance */
    float base_reactance = Capacitor::calculate_capacitive_reactance(m_capacitor->base_capacitance(), frequency_sample);

    /* 2.Calculate transistor impedance */
    float transistor_impedance = calculate_transistor_impedance(frequency_sample);

    /* 3.Calculate total parallel impedance: rpi || Rbc || Rbe */
    std::vector<float> resistors = {m_resistor->base_emitter_resistance(), m_resistor->base_collector_resistance(), transistor_impedance};
    float in_parallel = Resistor::calculate_resistance_in_parallel(resistors);

    /* 4. Calculate input impedance as total in series impedance */
    float impedance = in_parallel + base_reactance;

    /* Plot (X: impedance, Y: frequency) */
    int KILOHM = 1000;
//    std::cout << "Input impedance[KΩ]: " << impedance / KILOHM << std::endl;

    return impedance;
}

float CommonEmitter::calculate_transistor_impedance(int frequency_sample)
{
    /* 1.Calculate emitter leg impedance */
    float emitter_impedance = calculate_transistor_emitter_impedance(frequency_sample);

    /* 2.Calculate transistor impedance */
    float impedance = (m_transistor->hfe() + 1) * emitter_impedance;

    /* Plot (X: impedance, Y: frequency) */
    int KILOHM = 1000;
//    std::cout << "Rpi[KΩ]: " << impedance / KILOHM << std::endl;

    return impedance;
}

float CommonEmitter::calculate_transistor_emitter_impedance(int frequency_sample)
{
    /* 1.Calculate emitter capacitor reactance */
    float emitter_reactance = Capacitor::calculate_capacitive_reactance(m_capacitor->emitter_capacitance(),
                                                                          frequency_sample);

    /* 2.Calculate total parallel impedance: Re || Xc */
    std::vector<float> resistors = {m_resistor->emitter_resistance(), emitter_reactance};
    float total_parallel_impedance = Resistor::calculate_resistance_in_parallel(resistors);

    /* 3.Calculate transistor impedance as total series impedance: (Xc || Re) + re' */
    float impedance = total_parallel_impedance + m_re_ac;

    return impedance;
}

float CommonEmitter::calculate_output_impedance(int frequency_sample)
{
    /* 1.Calculate collector capacitor reactance */
    float collector_reactance = Capacitor::calculate_capacitive_reactance(m_capacitor->collector_capacitance(),
                                                                            frequency_sample);

    /* 2.Calculate total series impedance: Xc + Rl */
    float total_series_impedance = collector_reactance + m_resistor->load_resistance();

    /* 3.Calculate output impedance as total parallel impedance: Rc || (Xc + Rl) */
    std::vector<float> resistors = {m_resistor->collector_resistance(), total_series_impedance};
    float impedance = Resistor::calculate_resistance_in_parallel(resistors);

    /* Plot (X: impedance, Y: frequency) */
    int KILOHM = 1000;
//    std::cout << "Output impedance[KΩ]: " << impedance / KILOHM << std::endl;

    return impedance;
}

float CommonEmitter::calculate_voltage_gain(int frequency_sample)
{
    /* 1.Calculate emitter impedance */
    float emitter_impedance = calculate_transistor_emitter_impedance(frequency_sample);

    /* 2.Calculate collector impedance */
    float collector_impedance = calculate_output_impedance(frequency_sample);

    /* 3.Calculate transistor voltage gain [dB] */
    float av_transistor = collector_impedance / emitter_impedance;
    float av_transistor_db = 20 * log10(av_transistor);

    /* 4.Calculate input and output stage losses due to filters affection [dB] */
    float input_loss_db = calculate_loss_of_input_stage(frequency_sample);
    float output_loss_db = calculate_loss_of_output_stage(frequency_sample);

    /* 5.Determine overall voltage gain */
    float av_db = av_transistor_db - input_loss_db - output_loss_db;
    av_db = (av_db < 0) ? 0 : av_db;

    /* Plot (X: voltage gain[dB], Y: frequency) */
//    std::cout << "Av[dB]: " << av_db << std::endl;

    return av_db;
}

float CommonEmitter::calculate_loss_of_input_stage(int frequency_sample)
{
    /* 1.Calculate transistor impedance */
    float transistor_impedance = calculate_transistor_impedance(frequency_sample);

    /* 2.Calculate circuit input impedance (excluding capacitance of base capacitor) */
    std::vector<float> resistors = {m_resistor->base_emitter_resistance(), m_resistor->base_collector_resistance(), transistor_impedance};
    float impedance = Resistor::calculate_resistance_in_parallel(resistors);

    /* 3.Calculate loss: Av = Vout / Vin = R / sqrt2(R^2 + Xc^2) = R/Z */
    /* a) first approach */
    float base_reactance = Capacitor::calculate_capacitive_reactance(m_capacitor->base_capacitance(), frequency_sample);
    float loss = impedance / sqrt((impedance * impedance) + (base_reactance * base_reactance));
    float loss_ratio = impedance / (base_reactance + impedance);

    /* b) second approach - (This produces the same output as loss calculated on first approach) */
//    float cutoff_frequency = Filter::calculate_first_order_filter_cutoff_frequency(impedance, m_capacitor->base_capacitance());
//    float loss_numerator = 2 * M_PI * frequency_sample;
//    float loss_denominator = sqrt(pow((2 * M_PI * frequency_sample), 2) + pow((2 * M_PI * cutoff_frequency), 2));
//    float loss = loss_numerator / loss_denominator;

    /* 4.Convert loss to absolute value and to dB */
    float loss_db = abs(20 * log10(loss));

//    std::cout << "Loss input: " << loss << ", Loss[dB]" << loss_db << ", Ratio(Zin/Xc): " << loss_ratio << std::endl;

    return loss_db;
}

float CommonEmitter::calculate_loss_of_output_stage(int frequency_sample)
{
    /* 1.Calculate loss */
    float collector_reactance = Capacitor::calculate_capacitive_reactance(m_capacitor->collector_capacitance(), frequency_sample);
    float loss = m_resistor->load_resistance() / sqrt((m_resistor->load_resistance() * m_resistor->load_resistance()) + (collector_reactance * collector_reactance));
    float loss_ratio = m_resistor->load_resistance() / (collector_reactance + m_resistor->load_resistance());

    /* 2.Convert loss to absolute value and to dB */
    float loss_db = abs(20 * log10(loss));

//    std::cout << "Loss output: " << loss << ", Loss[dB]" << loss_db << ", Ratio(Zin/Xc): " << loss_ratio << std::endl;

    return loss_db;
}
