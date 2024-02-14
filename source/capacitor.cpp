#include "../include/capacitor.h"


int Capacitor::m_capacitor_id = 0;

Capacitor::Capacitor(float cc, float cb, float ce, const std::string& label) : m_label(label), m_id(m_capacitor_id++)
{
    m_cc = cc;
    m_cb = cb;
    m_ce = ce;
};

float Capacitor::calculate_capacitive_reactance(float capacitance, int frequency_sample)
{
    /* input: capacitance[uF], frequency_sample[Hz] */
    int FROM_UF_TO_F = 1000000;
    capacitance = capacitance / FROM_UF_TO_F;
    return 1 / (2 * M_PI * capacitance * frequency_sample);
}

std::string Capacitor::label() const
{
    return m_label;
}

float Capacitor::collector_capacitance() const
{
    return m_cc;
}

float Capacitor::base_capacitance() const
{
    return m_cb;
}

float Capacitor::emitter_capacitance() const
{
    return m_ce;
}

void Capacitor::capacitor_data()
{
    std::cout << "ID: " << m_id << std::endl;
    std::cout << "LABEL: " << m_label << std::endl;
    std::cout << "Cc[uF]: " << m_cc << std::endl;
    std::cout << "Ce[uF]: " << m_ce << std::endl;
    std::cout << "Cb[uF]: " << m_cb << std::endl;
}
