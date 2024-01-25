#include "../include/resistor.h"


int Resistor::m_resistor_id = 0;

Resistor::Resistor(float rc, float rbc, float multiplier, const std::string& label) : m_label(label), m_id(m_resistor_id++)
{
    m_rc = rc * multiplier;
    m_rbc = rbc * multiplier;
    m_re = 0;
    m_rbe = 0;
}

Resistor::Resistor(float rc, float re, float rbc, float multiplier, const std::string& label) : m_label(label), m_id(m_resistor_id++)
{
    m_rc = rc * multiplier;
    m_re = re * multiplier;
    m_rbc = rbc * multiplier;
    m_rbe = 0;
};

Resistor::Resistor(float rc, float re, float rbc, float rbe, float multiplier, const std::string& label) : m_label(label), m_id(m_resistor_id++)
{
    m_rc = rc * multiplier;
    m_re = re * multiplier;
    m_rbc = rbc * multiplier;
    m_rbe = rbe * multiplier;
};

float Resistor::calculate_in_parallel(int arg_count, const float *resistors)
{
    float resistance = 0.0;

    for (int i = 0; i < arg_count; i++)
    {
        resistance += 1 / resistors[i];
    }

    resistance = 1 / resistance;

    return resistance;
}

float Resistor::calculate_in_series(int arg_count, const float *resistors)
{
    float resistance = 0.0;

    for (int i = 0; i < arg_count; i++)
    {
        resistance += resistors[i];
    }

    return resistance;
}

float Resistor::collecotr_resistor() const
{
    return m_rc;
}

float Resistor::emitter_resistor() const
{
    return m_re;
}

float Resistor::base_collector_resistor() const
{
    return m_rbc;
}

float Resistor::base_emitter_resistor() const
{
    return m_rbe;
}

std::string Resistor::label() const
{
    return m_label;
}
