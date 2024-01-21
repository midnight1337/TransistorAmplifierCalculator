#include "transistor.h"

#ifndef CIRCUIT_H
#define CIRCUIT_H

class Circuit
{
protected:
    Circuit(Transistor* transistor, int vcc, int rc, int re);
    Transistor* m_transistor;
    int m_vcc;
    int m_rc;
    int m_re;

public:
    virtual void calculate() = 0;
};

#endif
