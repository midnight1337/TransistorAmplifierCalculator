#include "../include/capacitor.h"


Capacitor::Capacitor(float cc, float ce, float cb, const std::string& label) : m_label(label)
{
    m_cc = cc;
    m_ce = ce;
    m_cb = cb;
};

float Capacitor::calculate_reactance(float capacitance, int frequency_sample)
{
    return 1 / (2 * 3.14 * capacitance * frequency_sample);
}

std::string Capacitor::label() const
{
    return m_label;
}
