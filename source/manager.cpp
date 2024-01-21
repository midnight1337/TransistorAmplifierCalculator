#include "../include/manager.h"


void Manager::new_bjt_transistor(const std::string& model, const std::string& type, int hfe, float vbe)
{
    Bjt* transistor = new Bjt(model, type, hfe, vbe);
    m_transistors.push_back(transistor);
}

void Manager::show_transistors()
{
    for (Transistor* transistor : m_transistors)
    {
        transistor->transistor_info();
    }
}

void Manager::show_transistors(const std::string& model)
{
    for (Transistor* transistor : m_transistors)
    {
        if (transistor->model() == model) {
            transistor->transistor_info();
            return;
        }
    }

    // If the loop completes without finding the transistor, throw an exception
    throw std::runtime_error("Transistor model not found: " + model);
}

void Manager::breadboard_common_emitter_circuit(const std::string& transistor_model, int vcc, int rc, int re, int rbc, int rbe)
{
    Transistor* transistor = get_transistor(transistor_model);

    m_common_emitter =  CommonEmitter(transistor, vcc, rc, re, rbc, rbe);
}

void Manager::calculate_common_emitter_circuit()
{
    m_common_emitter.calculate();
}

Transistor* Manager::get_transistor(const std::string& model)
{
    for (Transistor* transistor : m_transistors)
    {
        if (transistor->model() == model)
        {
            return transistor;
        }
    }

    // If the loop completes without finding the transistor, throw an exception
    throw std::runtime_error("Transistor model not found: " + model);
}
