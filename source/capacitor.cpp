#include "../include/capacitor.h"


Capacitor::Capacitor(float cc, float cb, const std::string &label) : m_label(label)
{
    m_cc = cc;
    m_cb = cb;
    m_ce = 0;
}

Capacitor::Capacitor(float cc, float cb, float ce, const std::string& label) : m_label(label)
{
    m_cc = cc;
    m_cb = cb;
    m_ce = ce;
};

float Capacitor::calculate_reactance(float capacitance, int frequency_sample)
{
    return 1 / (2 * 3.14 * capacitance * frequency_sample);
}

std::string Capacitor::label() const
{
    return m_label;
}

float Capacitor::collector_capacitor() const
{
    return m_cc;
}

float Capacitor::base_capacitor() const
{
    return m_cb;
}

float Capacitor::emitter_capacitor() const
{
    return m_ce;
}
