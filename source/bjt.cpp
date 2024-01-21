#include <iostream>
#include "../include/bjt.h"

Bjt::Bjt(const std::string& model, const std::string& type, int hfe, float vbe) : Transistor(model, type, hfe)
{
    m_vbe = vbe;
}

void Bjt::transistor_info()
{
    std::cout << m_id << std::endl;
    std::cout << m_model << std::endl;
    std::cout << m_type << std::endl;
    std::cout << m_current_gain << std::endl;
    std::cout << m_vbe << std::endl;
}
