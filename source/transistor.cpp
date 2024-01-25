#include "../include/transistor.h"


Transistor::Transistor(const std::string& model, const std::string& type, int current_gain) : m_id(m_transistor_id++)
{
    m_model = model;
    m_type = type;
    m_current_gain = current_gain;
}

std::string Transistor::model()
{
    return m_model;
}

int Transistor::current_gain() const
{
    return m_current_gain;
}


int Transistor::m_transistor_id = 0;
