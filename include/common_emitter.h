#include "circuit.h"
#include "transistor.h"
#include "bjt.h"
#include "resistor.h"

#ifndef COMMON_EMITTER_H
#define COMMON_EMITTER_H


class CommonEmitter : public Circuit
{
private:
    float m_rbc;
    float m_rbe;
    float m_rl;

    float m_vc;
    float m_vb;
    float m_ve;
    float m_vce;
    float m_ic;
    float m_ib;
    float m_ie;
    float m_gm;
    float m_rpi;
    float m_z_in;
    float m_z_out;
    float m_av;

    void calculate_base_voltage();
    void calculate_base_current();
    void calculate_collector_voltage();
    void calculate_collector_current();
    void calculate_emitter_voltage();
    void calculate_emitter_current();
    void calculate_bias_voltage();
    void calculate_internal_emitter_resistance();
    void determine_q_point();

    // AC frequency dependent calculations
    void calculate_transistor_impedance();
    void calculate_input_impedance();
    void calculate_output_impedance();
    void calculate_voltage_gain();

public:
    CommonEmitter();
    CommonEmitter(Transistor* transistor, int vcc, int rc, int re, int rbc, int rbe);
    void calculate() override;
};

#endif
