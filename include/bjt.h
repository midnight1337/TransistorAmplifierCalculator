#include <iostream>
#include "transistor.h"

#ifndef BJT_H
#define BJT_H


class Bjt : public Transistor
{
private:
    const float m_hfe;
    const float m_vbe;
    const float m_vt;

public:
    Bjt(const std::string& model, const std::string& type, float hfe, float vbe);
    ~Bjt() override = default;
    void transistor_parameters() override;
    float hfe() const;
    float vbe() const;
    float vt() const;
};

#endif
