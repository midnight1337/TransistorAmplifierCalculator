#include "manager.h"


void Manager::new_transistor(std::string& model, std::string& type, int hfe, float vbe)
{
    Transistor* transistor = new Transistor(model, type, hfe, vbe);
    
    m_transistors[m_transistor_counter] = tranistor;

    m_transistor_counter++;
}

Transistor* Manager::transistor(std::string& model)
{
    for (int i = 0; i < m_transistor_count; i++)
    {
        if m_transistors[i]->model() == model { return m_transistors[i]; }
    }

    // If the loop completes without finding the transistor, throw an exception
    throw std::runtime_error("Transistor not found with model: " + model);
}

