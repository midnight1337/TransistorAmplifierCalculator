#include <iostream>
#include "circuit.h"

#ifndef COMMON_EMITTER_H
#define COMMON_EMITTER_H


class CommonEmitter : public Circuit
{
    private:
        int m_rbc;
        int m_rbe;
        int m_rc;
        int m_re;

    public:
        CommonEmitter(Transistor* transistor, int vcc);
        int calcualte_base_voltage();
        int calculate_base_current();
        int calculate_collector_voltage();
        int calculate_collector_current();
        int calculate_emitter_voltage();
        int calculate_emitter_current();
        int calculate_input_impedance();
        int calculate_output_impedance();
        int calculate_voltage_gain();
        void determine_q_point();
};

#endif
