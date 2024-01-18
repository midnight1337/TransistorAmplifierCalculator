#include "../include/common_emitter.h"


CommonEmitter::CommonEmitter(Transistor *transistor, int vcc)
{
    m_transistor = transistor;
    m_vcc = vcc;
}

int CommonEmitter::calcualte_base_voltage()
{
    return 0;
}

int CommonEmitter::calculate_base_current()
{
    return 0;
}

int CommonEmitter::calculate_collector_voltage()
{
    return 0;
}

int CommonEmitter::calculate_collector_current()
{
    return 0;
}

int CommonEmitter::calculate_emitter_voltage()
{
    return 0;
}

int CommonEmitter::calculate_emitter_current()
{
    return 0;
}

int CommonEmitter::calculate_input_impedance()
{
    return 0;
}

int CommonEmitter::calculate_output_impedance()
{
    return 0;
}

int CommonEmitter::calculate_voltage_gain()
{
    return 0;
}

void CommonEmitter::determine_q_point()
{
    
}
