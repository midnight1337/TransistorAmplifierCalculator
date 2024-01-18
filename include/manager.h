#include <iostream>
#include <vector>
#include "transistor.h"
#include "bjt.h"
#include "common_emitter.h"


#ifndef MANAGER_H
#define MANAGER_H

class Manager
{
    private:
        std::vector<Transistor*> m_transistors;
    
    public:
        Transistor* transistor(std::string& model);
        void new_transistor(std::string model, std::string type, int hfe, float vbe);
        void common_emitter_circuit(std::string transistor_model, int vcc);   
        void test();
};

#endif
