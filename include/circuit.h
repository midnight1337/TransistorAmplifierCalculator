#include <map>
#include "transistor.h"
#include "bjt.h"
#include "resistor.h"
#include "capacitor.h"
#include "filter.h"

#ifndef CIRCUIT_H
#define CIRCUIT_H


template <typename TransistorType = Transistor>
class Circuit
{
protected:
    TransistorType* m_transistor;
    Resistor* m_resistor;
    Capacitor* m_capacitor;

    const float m_vcc;
    float m_vc, m_vb, m_ve, m_vce;
    float m_ic, m_ib, m_ie, m_ic_sat;
    float m_re_ac, m_rpi_dc, m_rpi_ac;
    float m_av_ac, m_av_ac_db, m_av_dc, m_av_dc_db;
    float m_z_in, m_z_out;
    float m_fc_in, m_fc_out, m_fc_emitter;
    float m_gm;
    std::map<int, float> m_input_impedance_samples, m_output_impedance_samples, m_voltage_gain_samples;

    // DC analysis
    virtual void calculate_base_voltage() = 0;
    virtual void calculate_base_current() = 0;
    virtual void calculate_collector_voltage() = 0;
    virtual void calculate_collector_current() = 0;
    virtual void calculate_emitter_voltage() = 0;
    virtual void calculate_emitter_current() = 0;
    virtual void calculate_saturation_current() = 0;
    virtual void calculate_bias_voltage() = 0;
    virtual void calculate_transistor_internal_emitter_resistance() = 0;
    virtual void calculate_transistor_transconductance() = 0;
    virtual void calculate_cutoff_frequency_of_input_stage() = 0;
    virtual void calculate_cutoff_frequency_of_output_stage() = 0;
    virtual void calculate_cutoff_frequency_of_emitter_stage() = 0;

    // AC analysis
    virtual void calculate_transistor_impedance() = 0;
    virtual void calculate_input_impedance() = 0;
    virtual void calculate_output_impedance() = 0;
    virtual void calculate_voltage_gain() = 0;

    // Frequency analysis
    virtual float calculate_input_impedance(int frequency_sample) = 0;
    virtual float calculate_output_impedance(int frequency_sample) = 0;
    virtual float calculate_transistor_impedance(int frequency_sample) = 0;
    virtual float calculate_voltage_gain(int frequency_sample) = 0;
    virtual float calculate_loss_of_input_stage(int frequency_sample) = 0;
    virtual float calculate_loss_of_output_stage(int frequency_sample) = 0;

public:
    Circuit(TransistorType* transistor, Resistor* resistor, Capacitor* capacitor, float vcc);
    virtual ~Circuit() = default;
    void calculate_data();
    void show_data();
    void convert_data();
    void frequency_analysis(int frequency_start, int frequency_stop);
};

template <typename TransistorType>
Circuit<TransistorType>::Circuit(TransistorType* transistor, Resistor* resistor, Capacitor* capacitor, float vcc) : m_vcc(vcc)
{
    m_transistor = transistor;
    m_resistor = resistor;
    m_capacitor = capacitor;
}

template <typename TransistorType>
void Circuit<TransistorType>::frequency_analysis(int frequency_start, int frequency_stop)
{
    for (int frequency_sample = frequency_start; frequency_sample < frequency_stop; frequency_sample++)
    {
        float input_impedance_sample = calculate_input_impedance(frequency_sample);
        float output_impedance_sample = calculate_output_impedance(frequency_sample);
        float voltage_gain_sample = calculate_voltage_gain(frequency_sample);

        m_input_impedance_samples[frequency_sample] = input_impedance_sample;
        m_output_impedance_samples[frequency_sample] = output_impedance_sample;
        m_voltage_gain_samples[frequency_sample] = voltage_gain_sample;
    }
    // Access samples from hash map
//    for (auto sample : m_voltage_gain_samples)
//    {
//        std::cout << sample.first << "[Hz] : " << sample.second << "[dB]" << std::endl;
//    }
}

template <typename TransistorType>
void Circuit<TransistorType>::calculate_data()
{
    calculate_base_voltage();
    calculate_base_current();
    calculate_collector_current();
    calculate_emitter_current();
    calculate_collector_voltage();
    calculate_emitter_voltage();
    calculate_bias_voltage();
    calculate_transistor_internal_emitter_resistance();
    calculate_saturation_current();
    calculate_transistor_transconductance();
    calculate_transistor_impedance();
    calculate_input_impedance();
    calculate_output_impedance();
    calculate_voltage_gain();
    calculate_cutoff_frequency_of_input_stage();
    calculate_cutoff_frequency_of_output_stage();
    calculate_cutoff_frequency_of_emitter_stage();
}

template <typename TransistorType>
void Circuit<TransistorType>::show_data()
{
    convert_data();

    std::cout << "--Input data--" << std::endl;
    m_transistor->transistor_data();
    m_resistor->resistor_data();
    m_capacitor->capacitor_data();
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
    std::cout << "gm[S]: " << m_gm << std::endl;
    std::cout << "Z_in[KΩ]: " << m_z_in << std::endl;
    std::cout << "Z_out[KΩ]: " << m_z_out << std::endl;
    std::cout << "fc_in(HP)[Hz]: " << m_fc_in << std::endl;
    std::cout << "fc_out(HP)[Hz]: " << m_fc_out << std::endl;
    std::cout << "fc_emitter(HP)[Hz]: " << m_fc_emitter << std::endl;
    std::cout << "Q_point: " << m_ic_sat << "/" << m_vcc << "[Ic(sat)/Vcc] | " << m_ic << "/" << m_vce << "[Ic/Vce]" << std::endl;

    std::cout << "\n--Output data DC analysis--" << std::endl;
    std::cout << "Av_dc (Voltage gain): " << m_av_dc << std::endl;
    std::cout << "Av_dc[dB]: " << m_av_dc_db << std::endl;
    std::cout << "r_pi_dc[KΩ]: " << m_rpi_dc << std::endl;

    std::cout << "\n--Output data AC analysis--" << std::endl;
    std::cout << "Av_ac (Voltage gain): " << m_av_ac << std::endl;
    std::cout << "Av_ac[dB]: " << m_av_ac_db << std::endl;
    std::cout << "re_ac[Ω]: " << m_re_ac << std::endl;
    std::cout << "rpi_ac[KΩ]: " << m_rpi_ac << std::endl;
}

template <typename TransistorType>
void Circuit<TransistorType>::convert_data()
{
    const int KILO_MILLI = 1000;
    const int MEGA_MICRO = 1000000;
    const float TWO_DECIMALS = 100.0;
    const float FOUR_DECIMALS = 10000.0;

    float *data_to_milli[] = {&m_ic, &m_ie, &m_ic_sat};
    float *data_to_kilo[] = {&m_z_in, &m_z_out, &m_rpi_ac, &m_rpi_dc};
    float *data_to_two_decimals[] = {&m_vc, &m_vb, &m_ve, &m_ic, &m_ib, &m_ie, &m_ic_sat, &m_vce,
                             &m_z_in, &m_z_out, &m_rpi_ac, &m_rpi_dc, &m_re_ac, &m_av_ac,
                             &m_av_dc, &m_av_ac_db, &m_av_dc_db, &m_fc_in, &m_fc_out, &m_fc_emitter};

    m_ib = m_ib * MEGA_MICRO;
    m_gm = round(m_gm * FOUR_DECIMALS) / FOUR_DECIMALS;

    for (float *data : data_to_milli) { *data = *data * KILO_MILLI; }
    for (float *data: data_to_kilo) { *data = *data / KILO_MILLI; }
    for (float *data: data_to_two_decimals) { *data = round(*data * TWO_DECIMALS) / TWO_DECIMALS; }
}

#endif
