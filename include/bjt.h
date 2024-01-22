#include <iostream>
#include "transistor.h"

#ifndef BJT_H
#define BJT_H


class Bjt : public Transistor
{
private:
    const float m_vbe;
    const int m_vt;

public:
    Bjt(const std::string& model, const std::string& type, int hfe, float vbe);
    ~Bjt() override = default;
    void transistor_parameters() override;
    float vbe();
    int vt();
};

#endif
