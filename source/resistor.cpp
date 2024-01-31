#include "../include/resistor.h"


int Resistor::m_resistor_id = 0;

Resistor::Resistor(float rc, float rbc, float rl, float multiplier, const std::string& label) : m_label(label), m_id(m_resistor_id++)
{
    m_rc = rc * multiplier;
    m_rbc = rbc * multiplier;
    m_re = 0;
    m_rbe = 0;
    m_rl = rl * multiplier;
}

Resistor::Resistor(float rc, float re, float rbc, float rl, float multiplier, const std::string& label) : m_label(label), m_id(m_resistor_id++)
{
    m_rc = rc * multiplier;
    m_re = re * multiplier;
    m_rbc = rbc * multiplier;
    m_rbe = 0;
    m_rl = rl * multiplier;
}

Resistor::Resistor(float rc, float re, float rbc, float rbe, float rl, float multiplier, const std::string& label) : m_label(label), m_id(m_resistor_id++)
{
    m_rc = rc * multiplier;
    m_re = re * multiplier;
    m_rbc = rbc * multiplier;
    m_rbe = rbe * multiplier;
    m_rl = rl * multiplier;
}

float Resistor::voltage_divider(float resistance_source, float resistance_ground, float source_voltage)
{
    /* Returns a output voltage */
    return (source_voltage * resistance_ground) / (resistance_source + resistance_ground);
}

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

float Resistor::collector_resistor() const
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

float Resistor::load_resistor() const
{
    return m_rl;
}

std::string Resistor::label() const
{
    return m_label;
}

void Resistor::resistors_values()
{
    std::cout << "ID: " << m_id << std::endl;
    std::cout << "LABEL: " << m_label << std::endl;
    std::cout << "Rc[KΩ]: " << m_rc / 1000 << std::endl;
    std::cout << "Re[KΩ]: " << m_re / 1000 << std::endl;
    std::cout << "Rbc[KΩ]: " << m_rbc / 1000 << std::endl;
    std::cout << "Rbe[KΩ]: " << m_rbe / 1000 << std::endl;
    std::cout << "RL[KΩ]: " << m_rl / 1000 << std::endl;
}
