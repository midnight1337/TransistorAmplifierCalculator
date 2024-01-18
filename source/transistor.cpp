#include "../include/transistor.h"


Transistor::Transistor(std::string model, std::string type, int current_gain) : m_id(m_transistor_id++)
{
    m_model = model;
    m_type = type;
    m_current_gain = current_gain;
}

std::string Transistor::model() { return m_model; }

std::string Transistor::type() { return m_type; }

int Transistor::current_gain() { return m_current_gain; }

int Transistor::id() { return m_id; }

int Transistor::m_transistor_id = 0;
