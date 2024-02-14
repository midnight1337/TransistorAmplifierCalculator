#include "../include/transistor.h"


int Transistor::m_transistor_id = 0;

Transistor::Transistor(const std::string& model, const std::string& type) : m_id(m_transistor_id++)
{
    m_model = model;
    m_type = type;
}

std::string Transistor::model()
{
    return m_model;
}
