#include "transistor.h"

#ifndef CIRCUIT_H
#define CIRCUIT_H

class Circuit
{
protected:
    Transistor* m_transistor;
    float m_vcc;
    float m_rc;
    float m_re;
    float m_re_ac;
    std::string q_point;

public:
    Circuit();
    Circuit(Transistor* transistor, int vcc, int rc, int re);
    virtual void calculate() = 0;
};

#endif
