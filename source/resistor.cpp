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

Resistor::Resistor(float rc, float re, float rbc, float rbe, float rl, float rs, float multiplier, const std::string& label) : m_label(label), m_id(m_resistor_id++)
{
    m_rc = rc * multiplier;
    m_re = re * multiplier;
    m_rbc = rbc * multiplier;
    m_rbe = rbe * multiplier;
    m_rl = rl * multiplier;
    m_rs = rs * multiplier;
}

float Resistor::calculate_resistance_in_parallel(const std::vector<float>& resistors)
{
    float resistance_in_parallel = 0.0;

    for (float resistance : resistors)
    {
        resistance_in_parallel += 1 / resistance;
    }

    return 1 / resistance_in_parallel;
}

float Resistor::calculate_resistance_in_series(const std::vector<float>& resistances)
{
    float resistance_in_series = 0.0;

    for (float resistance : resistances)
    {
        resistance_in_series += resistance;
    }

    return resistance_in_series;
}

float Resistor::collector_resistance() const
{
    return m_rc;
}

float Resistor::emitter_resistance() const
{
    return m_re;
}

float Resistor::base_collector_resistance() const
{
    return m_rbc;
}

float Resistor::base_emitter_resistance() const
{
    return m_rbe;
}

float Resistor::load_resistance() const
{
    return m_rl;
}

float Resistor::source_resistance() const
{
    return m_rs;
}

std::string Resistor::label() const
{
    return m_label;
}

void Resistor::resistor_data()
{
    const int KILOHM = 1000;

    std::cout << "ID: " << m_id << std::endl;
    std::cout << "LABEL: " << m_label << std::endl;
    std::cout << "Rc[KΩ]: " << m_rc / KILOHM << std::endl;
    std::cout << "Re[KΩ]: " << m_re / KILOHM << std::endl;
    std::cout << "Rbc[KΩ]: " << m_rbc / KILOHM << std::endl;
    std::cout << "Rbe[KΩ]: " << m_rbe / KILOHM << std::endl;
    std::cout << "RL[KΩ]: " << m_rl / KILOHM << std::endl;
}
