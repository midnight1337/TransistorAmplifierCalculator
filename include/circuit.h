#include "transistor.h"

#ifndef CIRCUIT_H
#define CIRCUIT_H

class Circuit
{
protected:
    Transistor* m_transistor;
    float m_vcc;
    float m_vc;
    float m_vb;
    float m_ve;
    float m_vce;
    float m_ic;
    float m_ib;
    float m_ie;
    float m_ic_sat;
    float m_gm;
    float m_r_pi;
    float m_z_in;
    float m_z_out;
    float m_av;
    int m_av_db;
    float m_re_ac;

    virtual void calculate_data() = 0;
    virtual void circuit_data() = 0;
    virtual void convert_data() = 0;

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

    // AC frequency dependent calculations
    virtual void calculate_transistor_impedance() = 0;
    virtual void calculate_input_impedance() = 0;
    virtual void calculate_output_impedance() = 0;
    virtual void calculate_voltage_gain() = 0;

public:
    Circuit();
    Circuit(Transistor* transistor, float vcc);
    virtual ~Circuit() = default;
};

#endif
