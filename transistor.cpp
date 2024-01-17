#include "transistor.h"

std::string Transistor::model() { return m_model; }

std::string Transistor::type() { return m_type; }

int Transistor::current_gain() { return m_current_gain; }

void Transistor::initialise(std::string& model, std::string& type, int& current_gain)
{
    m_model = model;
    m_type = type;
    m_current_gain = current_gain;
}
