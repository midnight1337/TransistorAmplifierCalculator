#include <iostream>
#include "../include/bjt.h"

Bjt::Bjt(const std::string& model, const std::string& type, int hfe, float vbe) : Transistor(model, type, hfe), m_vbe(vbe), m_vt(25) {}

void Bjt::transistor_parameters()
{
    std::cout << "ID: " << m_id << std::endl;
    std::cout << "MODEL: " << m_model << std::endl;
    std::cout << "TYPE: " << m_type << std::endl;
    std::cout << "Hfe: " << m_current_gain << std::endl;
    std::cout << "Vbe: " << m_vbe << std::endl;
}

float Bjt::vbe()
{
    return m_vbe;
}

int Bjt::vt()
{
    return m_vt;
}
