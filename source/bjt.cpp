#include "../include/bjt.h"

Bjt::Bjt(const std::string& model, const std::string& type, float hfe, float vbe) :
Transistor(model, type), m_hfe(hfe), m_vbe(vbe), m_vt(0.025)
{}

float Bjt::hfe() const
{
    return m_hfe;
}

float Bjt::vbe() const
{
    return m_vbe;
}

float Bjt::vt() const
{
    return m_vt;
}

void Bjt::transistor_parameters()
{
    std::cout << "ID: " << m_id << std::endl;
    std::cout << "MODEL: " << m_model << std::endl;
    std::cout << "TYPE: " << m_type << std::endl;
    std::cout << "Hfe: " << m_hfe << std::endl;
    std::cout << "Vbe: " << m_vbe << std::endl;
}
