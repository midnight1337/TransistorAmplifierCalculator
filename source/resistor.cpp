#include "../include/resistor.h"


Resistor::Resistor(float rc, float re, float rbc, float multiplier, const std::string& label) : m_label(label)
{
    m_rc = rc * multiplier;
    m_re = re * multiplier;
    m_rbc = rbc * multiplier;
};

Resistor::Resistor(float rc, float re, float rbc, float rbe, float multiplier, const std::string& label) : m_label(label)
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

std::string Resistor::label() const
{
    return m_label;
}
