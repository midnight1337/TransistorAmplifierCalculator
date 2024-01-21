#include "../include/circuit.h"


Circuit::Circuit(Transistor* transistor, int vcc, int rc, int re)
{
    m_transistor = transistor;
    m_vcc = vcc;
    m_rc = rc;
    m_re = re;
}
