#include "../include/common_emitter.h"


CommonEmitter::CommonEmitter(Bjt *transistor, Resistor *resistor, Capacitor *capacitor, float vcc) :
Circuit(transistor, resistor, capacitor, vcc)
{}

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

    float denominator = (equivalent_resistance + (m_transistor->hfe() + 1) * m_resistor->emitter_resistor());

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
    m_ic_sat = m_vcc / (m_resistor->collector_resistor() + m_resistor->emitter_resistor() + m_re_ac);
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
    m_rpi_dc = ((m_transistor->hfe() + 1) * (m_resistor->emitter_resistor() + m_re_ac));

    /* AC analysis, bypass through Emitter capacitor (Two valid formulas) */
//    m_rpi_ac = (m_transistor->hfe() + 1) / m_gm;
    m_rpi_ac = ((m_transistor->hfe() + 1) * m_re_ac);
}

void CommonEmitter::calculate_input_impedance()
{
    float resistors[] = {m_resistor->base_emitter_resistor(), m_resistor->base_collector_resistor(), m_rpi_ac};
    int arg_count = sizeof(resistors) / sizeof(float);

    m_z_in = Resistor::calculate_in_parallel(arg_count, resistors);
}

void CommonEmitter::calculate_output_impedance()
{
    float resistors[] = {m_resistor->collector_resistor(), m_resistor->load_resistor()};
    int arg_count = sizeof(resistors) / sizeof(float);

    m_z_out = Resistor::calculate_in_parallel(arg_count, resistors);
}

void CommonEmitter::calculate_voltage_gain()
{
    /* DC analysis, no bypass through Emitter capacitor */
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
    /* 1.Calculate reactance of 'Cb' */
    float xc = Capacitor::calculate_reactance(m_capacitor->base_capacitor(), frequency_sample);

    /* 2.Calculate impedance of transistor */
    float transistor_impedance = calculate_transistor_impedance(frequency_sample);

    /* 3.Calculate in parallel impedance of: rpi || Rbc || Rbe */
    float resistors[] = {m_resistor->base_emitter_resistor(), m_resistor->base_collector_resistor(), transistor_impedance};
    int arg_count = sizeof(resistors) / sizeof(float);
    float in_parallel = Resistor::calculate_in_parallel(arg_count, resistors);

    /* 4. Input impedance of the circuit */
    float impedance = in_parallel + xc;

    /* Plot (X: impedance, Y: frequency) */
    std::cout << "Input impedance[KΩ]: " << impedance / 1000 << std::endl;

    return impedance;
}

float CommonEmitter::calculate_transistor_impedance(int frequency_sample)
{
    /* 1.Calculate emitter leg impedance */
    float emitter_impedance = calculate_transistor_emitter_impedance(frequency_sample);

    /* 2.Calculate transistor impedance */
    float impedance = (m_transistor->hfe() + 1) * emitter_impedance;

    /* Plot (X: impedance, Y: frequency) */
    std::cout << "Rpi[KΩ]: " << impedance / 1000 << std::endl;

    return impedance;
}

float CommonEmitter::calculate_transistor_emitter_impedance(int frequency_sample)
{
    /* 1.Calculate reactance of 'Ce' */
    float xc = Capacitor::calculate_reactance(m_capacitor->emitter_capacitor(), frequency_sample);

    /* 2.Calculate in parallel impedance of: Re || Xc */
    float resistors[] = {m_resistor->emitter_resistor(), xc};
    int arg_count = sizeof(resistors) / sizeof(float);
    float in_parallel = Resistor::calculate_in_parallel(arg_count, resistors);

    /* 3.Calculate in series impedance of: (Xc || Re) + re' */
    float impedance = in_parallel + m_re_ac;

    return impedance;
}

float CommonEmitter::calculate_output_impedance(int frequency_sample)
{
    /* 1.Calculate reactance of 'Cc' */
    float xc = Capacitor::calculate_reactance(m_capacitor->collector_capacitor(), frequency_sample);

    /* 2.Calculate in series impedance of: Xc + Rl */
    float in_series = xc + m_resistor->load_resistor();

    /* 3.Calculate in parallel impedance of: Rc || (Xc + Rl) */
    float resistors[] = {m_resistor->collector_resistor(), in_series};
    int arg_count = sizeof(resistors) / sizeof(float);
    float in_parallel = Resistor::calculate_in_parallel(arg_count, resistors);

    /* 4.Output impedance of the circuit */
    float impedance = in_parallel;

    /* Plot (X: impedance, Y: frequency) */
    std::cout << "Output impedance[KΩ]: " << impedance / 1000 << std::endl;

    return impedance;
}

float CommonEmitter::calculate_voltage_gain(int frequency_sample)
{
    /* 1.Calculate impedance of emitter */
    float emitter_impedance = calculate_transistor_emitter_impedance(frequency_sample);

    /* 2.Calculate impedance of collector */
    float collector_impedance = calculate_output_impedance(frequency_sample);

    /* 3.Calculate voltage gain of transistor [dB] */
    float av_transistor = collector_impedance / emitter_impedance;
    float av_transistor_db = 20 * log10(av_transistor);

    /* 4.Calculate loss of input and output stage affected by filters [dB] */
    float input_loss_db = calculate_loss_of_input_stage(frequency_sample);
    float output_loss_db = calculate_loss_of_output_stage(frequency_sample);

    /* 5.Determine overall voltage gain */
    float av_db = av_transistor_db - input_loss_db - output_loss_db;
    if (av_db < 0) { av_db = 0; }

    /* Plot (X: voltage gain[dB], Y: frequency) */
    std::cout << "Av[dB]: " << av_db << std::endl;

    return av_db;
}

float CommonEmitter::calculate_loss_of_input_stage(int frequency_sample)
{
    /* 1.Calculate impedance of transistor */
    float transistor_impedance = calculate_transistor_impedance(frequency_sample);

    /* 2.Calculate input impedance of circuit (not including Xc of 'Cb') */
    float resistors[] = {m_resistor->base_emitter_resistor(), m_resistor->base_collector_resistor(), transistor_impedance};
    int arg_count = sizeof(resistors) / sizeof(float);
    float impedance = Resistor::calculate_in_parallel(arg_count, resistors);

    /* 3.Calculate loss */
    /* a) first approach */
    float xc = Capacitor::calculate_reactance(m_capacitor->base_capacitor(), frequency_sample);
    float loss = impedance / sqrt((impedance * impedance) + (xc * xc));
    float loss_ratio = impedance / (xc + impedance);

    /* b) second approach - (This produces the same output as loss calculated on first approach) */
//    float cutoff_frequency = Filter::high_pass(impedance, m_capacitor->base_capacitor());
//    float loss_numerator = 2 * M_PI * frequency_sample;
//    float loss_denominator = sqrt(pow((2 * M_PI * frequency_sample), 2) + pow((2 * M_PI * cutoff_frequency), 2));
//    float loss = loss_numerator / loss_denominator;

    /* 4.Convert loss to absolute value and to dB */
    float loss_db = abs(20 * log10(loss));

    std::cout << "Loss input: " << loss << ", Loss[dB]" << loss_db << ", Ratio(Zin/Xc): " << loss_ratio << std::endl;

    return loss_db;
}

float CommonEmitter::calculate_loss_of_output_stage(int frequency_sample)
{
    /* 1.Calculate loss */
    float xc = Capacitor::calculate_reactance(m_capacitor->collector_capacitor(), frequency_sample);
    float loss = m_resistor->load_resistor() / sqrt((m_resistor->load_resistor() * m_resistor->load_resistor()) + (xc * xc));
    float loss_ratio = m_resistor->load_resistor() / (xc + m_resistor->load_resistor());

    /* 2.Convert loss to absolute value and to dB */
    float loss_db = abs(20 * log10(loss));

    std::cout << "Loss output: " << loss << ", Loss[dB]" << loss_db << ", Ratio(Zin/Xc): " << loss_ratio << std::endl;

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
