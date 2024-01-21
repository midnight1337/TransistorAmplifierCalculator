#include <iostream>
#include "transistor.h"

#ifndef BJT_H
#define BJT_H


class Bjt : public Transistor
{
private:
    float m_vbe;
    const int m_vt;

public:
    Bjt(const std::string& model, const std::string& type, int hfe, float vbe);
    void transistor_info() override;
    float vbe();
    int vt();
};

#endif
