#include <iostream>
#include <vector>
#include "transistor.h"
#include "common_emitter.h"


class Manager
{
    private:
        std::vector<Transistor*> m_transistors;
    
    public:
        Manager() = default;
        Transistor* transistor(std::string& model);
        void new_transistor(std::string model, std::string type, int hfe, float vbe);
        void common_emitter_circuit(std::string transistor_model, int vcc);   
};
