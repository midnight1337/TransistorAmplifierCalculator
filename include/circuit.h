#include <iostream>
#include "transistor.h"


class Circuit
{
    protected:
        int m_vcc;
        Transistor* m_transistor;
    
    public:
        virtual ~Circuit() = 0;
};
