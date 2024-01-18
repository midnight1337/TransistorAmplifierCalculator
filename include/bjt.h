#include <iostream>
#include "transistor.h"

#ifndef BJT_H
#define BJT_H


class Bjt : public Transistor
{
    private:
        float m_vbe;

    public:
        Bjt(std::string model, std::string type, int hfe, float vbe);
        float vbe();
};

#endif
