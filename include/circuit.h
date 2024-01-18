#include <iostream>
#include "transistor.h"

#ifndef CIRCUIT_H
#define CIRCUIT_H


class Circuit
{
    protected:
        int m_vcc;
        Transistor* m_transistor;
    
    public:
        virtual ~Circuit() = 0;
};

#endif
