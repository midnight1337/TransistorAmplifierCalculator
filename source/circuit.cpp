#include "../include/circuit.h"

Circuit::Circuit() {}

Circuit::Circuit(Transistor* transistor, float vcc)
{
    m_transistor = transistor;
    m_vcc = vcc;
}
