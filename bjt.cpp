#include <iostream>
#include "bjt.h"

Bjt::Bjt(std::string model, std::string type, int hfe, float vbe)
{
    initialise(model, type, hfe);
    m_vbe = vbe;
}

float Bjt::vbe() { return m_vbe; }


