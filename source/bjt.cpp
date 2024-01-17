#include <iostream>
#include "../include/bjt.h"

Bjt::Bjt(std::string model, std::string type, int hfe, float vbe) : m_id(m_transistor_id++)
{
    m_model = model;
    m_type = type;
    m_current_gain = hfe;
    m_vbe = vbe;
}

float Bjt::vbe() { return m_vbe; }


