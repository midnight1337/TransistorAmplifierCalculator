#include "../include/manager.h"

void Manager::test()
{
    std::cout << "test" << std::endl;
}


void Manager::new_transistor(std::string model, std::string type, int hfe, float vbe)
{
    Transistor* transistor = new Bjt(model, type, hfe, vbe);
    
    m_transistors.push_back(transistor);
}

void Manager::common_emitter_circuit(std::string transistor_model, int vcc)
{
    Transistor* transistor = this->transistor(transistor_model);

    CommonEmitter circuit(transistor, vcc);
}

Transistor* Manager::transistor(std::string& model)
{
    for (Transistor* transistor : m_transistors)
    {
        if (transistor->model() == model) 
        { 
            return transistor; 
        }
    }

    // If the loop completes without finding the transistor, throw an exception
    throw std::runtime_error("Transistor not found with model: " + model);
}
