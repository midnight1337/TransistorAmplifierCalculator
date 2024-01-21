#include "../include/common_emitter.h"


CommonEmitter::CommonEmitter(Transistor *transistor, int vcc, int rc, int re, int rbc, int rbe) : Circuit(transistor, vcc, rc, re)
{
    m_rbc = rbc;
    m_rbe = rbe;
}

void CommonEmitter::calculate()
{
    calcualte_base_voltage();
    calculate_base_current();
    calculate_collector_voltage();
    calculate_collector_current();
    calculate_emitter_voltage();
    calculate_emitter_current();
    calculate_input_impedance();
    calculate_output_impedance();
    calculate_voltage_gain();
    determine_q_point();
}

void CommonEmitter::calcualte_base_voltage() {

}

void CommonEmitter::calculate_base_current() {

}

void CommonEmitter::calculate_collector_voltage() {

}

void CommonEmitter::calculate_collector_current() {

}

void CommonEmitter::calculate_emitter_voltage() {

}

void CommonEmitter::calculate_emitter_current() {

}

void CommonEmitter::calculate_input_impedance() {

}

void CommonEmitter::calculate_output_impedance() {

}

void CommonEmitter::calculate_voltage_gain() {

}

void CommonEmitter::determine_q_point() {

}
