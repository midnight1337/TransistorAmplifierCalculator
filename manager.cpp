#include "manager.h"


void Manager::new_transistor(std::string model, std::string type, int hfe, float vbe)
{
    Transistor* transistor = new Bjt(model, type, hfe, vbe);
    
    m_transistors.push_back(transistor);
}

Transistor* Manager::transistor(std::string& model)
{
    for (int i = 0; i < m_transistors.size(); i++)
    {
        if (m_transistors[i]->model() == model) { return m_transistors[i]; }
    }

    // If the loop completes without finding the transistor, throw an exception
    throw std::runtime_error("Transistor not found with model: " + model);
}
