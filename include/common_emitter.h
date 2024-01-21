#include "circuit.h"
#include "transistor.h"

#ifndef COMMON_EMITTER_H
#define COMMON_EMITTER_H


class CommonEmitter : public Circuit
{
private:
    int m_rbc;
    int m_rbe;

    void calcualte_base_voltage();
    void calculate_base_current();
    void calculate_collector_voltage();
    void  calculate_collector_current();
    void calculate_emitter_voltage();
    void calculate_emitter_current();
    void calculate_input_impedance();
    void calculate_output_impedance();
    void calculate_voltage_gain();
    void determine_q_point();

public:
    CommonEmitter(Transistor* transistor, int vcc, int rc, int re, int rbc, int rbe);
    void calculate() override;
};

#endif
