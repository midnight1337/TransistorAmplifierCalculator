#include "../include/collector_feedback.h"


CollectorFeedback::CollectorFeedback(Bjt *transistor, Resistor *resistor, Capacitor *capacitor, float vcc) :
Circuit(transistor, resistor, capacitor, vcc)
{}

void CollectorFeedback::test()
{
    // voltage gain ok, currents voltages nok, impedance probably nok
    calculate_base_current();
    calculate_collector_current();
    calculate_emitter_current();
    calculate_emitter_voltage();
    calculate_base_voltage();
    calculate_collector_voltage();
    calculate_bias_voltage();
    calculate_transistor_internal_emitter_resistance();
    calculate_saturation_current();
    calculate_transistor_transconductance();
    calculate_transistor_impedance();
    calculate_input_impedance();
    calculate_output_impedance();

    calculate_voltage_gain();
}

void CollectorFeedback::calculate_base_current()
{
    float nominator = m_vcc - m_transistor->vbe();
    float denominator = m_resistor->base_collector_resistance() + (static_cast<float>(m_transistor->hfe()) + 1) * (m_resistor->emitter_resistance() + m_resistor->collector_resistance());

    m_ib = nominator / denominator;
}

void CollectorFeedback::calculate_collector_current()
{
    m_ic = m_ib * static_cast<float>(m_transistor->hfe());
}

void CollectorFeedback::calculate_emitter_current()
{
    m_ie = m_ic + m_ib;
}

void CollectorFeedback::calculate_emitter_voltage()
{
    m_ve = m_ie * m_resistor->emitter_resistance();
}

void CollectorFeedback::calculate_base_voltage()
{
    m_vb = m_ve + m_transistor->vbe();
}

void CollectorFeedback::calculate_collector_voltage()
{
    m_vc = m_vcc - (m_ic * m_resistor->collector_resistance());
}

void CollectorFeedback::calculate_bias_voltage()
{
    m_vce = m_vc - m_ve;
}

void CollectorFeedback::calculate_transistor_internal_emitter_resistance()
{
    m_re_ac = m_transistor->vt() / m_ie;
}

void CollectorFeedback::calculate_saturation_current()
{
    m_ic_sat = m_vcc / (m_resistor->collector_resistance() + m_resistor->emitter_resistance() + m_re_ac);
}

void CollectorFeedback::calculate_transistor_transconductance()
{
    m_gm = m_ie / m_transistor->vt();
}

void CollectorFeedback::calculate_transistor_impedance()
{
    /* DC analysis, no bypass through Emitter capacitor */
    m_rpi_dc = (static_cast<float>(m_transistor->hfe()) * (m_resistor->emitter_resistance() + m_re_ac));

    /* AC analysis, bypass through Emitter capacitor (Two valid formulas) */
//    m_rpi_ac = (static_cast<float>(m_transistor->hfe() + 1) / m_gm);
    m_rpi_ac = (static_cast<float>(m_transistor->hfe()) * m_re_ac);
}

void CollectorFeedback::calculate_input_impedance()
{
    // Input impedance formula to be confirmed (no source resistance) Zin = (Rb + Rc)(rpi * (hfe + 1) * Re) / rpi(hfe + 1)(Rc + Re) + Rb

    // AC analysis
    float numerator = (m_resistor->base_collector_resistance() + m_resistor->collector_resistance()) * (m_rpi_ac * (static_cast<float>(m_transistor->hfe()) + 1) * m_re_ac);
    float denominator = m_rpi_ac * (static_cast<float>(m_transistor->hfe() + 1)) * (m_resistor->collector_resistance() + m_resistor->emitter_resistance()) + m_resistor->base_collector_resistance();

    m_z_in = numerator / denominator;   // With Rs would it be??: m_z_in = Rs + (numerator / denominator)
}

void CollectorFeedback::calculate_output_impedance()
{
    // Ouput impedance formula to be confirmed (no emitter resistance): Rout = (Rc||RF)/(1 + gm*(Rc||RF)*(Rg||RF||rpi) * 1/RF)
    float resistors[] = {m_resistor->collector_resistance(), m_resistor->base_collector_resistance()};
}

void CollectorFeedback::calculate_voltage_gain()
{
    // Voltage gain formula to be confirmed (no emitter resistance): Av = gm*(Rc || RF) - Rc/(RF + Rc)
    // Voltage gain 2nd formula to be confirmed: Av = (Rc || (Rc || Rcb)) / (Re + re_ac)
    // FIRST APPROACH - these two are only for collector feedback with no emitter resitsance i guess
    std::vector<float> resistors = {m_resistor->collector_resistance(), m_resistor->base_collector_resistance()};
    float in_parallel = Resistor::calculate_resistance_in_parallel(resistors);
    float av_1 = (m_gm * in_parallel) - (m_resistor->collector_resistance() / (m_resistor->base_collector_resistance() + m_resistor->collector_resistance()));
    float av_1_db = 20 * log10(av_1);

    std::vector<float> resistors_av_2 = {m_resistor->collector_resistance(), m_resistor->base_collector_resistance()};
    float resistors_av_2_r = Resistor::calculate_resistance_in_parallel(resistors_av_2);
    std::vector<float> resistors_av_2ss = {m_resistor->collector_resistance(), resistors_av_2_r};
    float resistors_av_2_rss = Resistor::calculate_resistance_in_parallel(resistors_av_2ss);
    float av_2 = resistors_av_2_rss / m_resistor->emitter_resistance();
    float av_2_db = 20 * log10(av_2);

    std::cout << av_2 << " " << av_2_db << std::endl;


    // SECOND APPROACH - electrosmash analysis (add re' in series with emitter?, for freq analysis add capacitor reactance in parallel with Rf)
    std::vector<float> resistors_rb = {m_resistor->source_resistance(), m_resistor->base_emitter_resistance(), m_resistor->base_collector_resistance()};
    float resistance_rb = Resistor::calculate_resistance_in_parallel(resistors_rb);

    std::vector<float> resistors_rl = {m_resistor->load_resistance(), m_resistor->collector_resistance(), m_resistor->base_collector_resistance()};
    float resistance_rl = Resistor::calculate_resistance_in_parallel(resistors_rl);

    // Voltage shunt gain without feedback
    float az = (resistance_rb * resistance_rl) / (m_re_ac + m_resistor->emitter_resistance());

    // Feedback voltage shunt formula
    float bg = 1 / m_resistor->base_collector_resistance();

    // Voltage shunt gain with feedback
    float azf = az / (1 + (az * bg));

    // Voltage gain
    float gv = azf / m_resistor->source_resistance();

    std::cout << "zin: " << m_z_in << std::endl;
    std::cout << "re': " << m_re_ac << std::endl;
    std::cout << "gv: "<< gv << ", gv[db]:  " << 20 * log10(gv) << std::endl;
}

void CollectorFeedback::calculate_cutoff_frequency_of_input_stage() {

}

void CollectorFeedback::calculate_cutoff_frequency_of_output_stage() {

}

void CollectorFeedback::calculate_cutoff_frequency_of_emitter_stage() {

}

float CollectorFeedback::calculate_input_impedance(int frequency_sample) {
    return 0;
}

float CollectorFeedback::calculate_output_impedance(int frequency_sample) {
    return 0;
}

float CollectorFeedback::calculate_transistor_impedance(int frequency_sample) {
    return 0;
}

float CollectorFeedback::calculate_voltage_gain(int frequency_sample) {
    return 0;
}

float CollectorFeedback::calculate_loss_of_input_stage(int frequency_sample) {
    return 0;
}

float CollectorFeedback::calculate_loss_of_output_stage(int frequency_sample) {
    return 0;
}

