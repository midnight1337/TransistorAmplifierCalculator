#include "../include/manager.h"

Manager::Manager()
{
    m_common_emitter = nullptr;
}

Manager::~Manager()
{
    for (Transistor* transistor : m_transistors)
    {
        delete transistor;
    }
//    for (Circuit* circuit : m_circuits)
//    {
//        delete circuit;
//    }
    delete m_common_emitter;
}

void Manager::new_bjt_transistor(const std::string& model, const std::string& type, int hfe, float vbe)
{
    Bjt* transistor = new Bjt(model, type, hfe, vbe);
    m_transistors.push_back(transistor);
}

void Manager::breadboard_common_emitter_circuit(const std::string& transistor_model, float vcc, float rc, float re, float rbc, float rbe)
{
    Bjt* transistor = dynamic_cast<Bjt*>(get_transistor(transistor_model));

    m_common_emitter =  new CommonEmitter(transistor, vcc, rc, re, rbc, rbe);
}

void Manager::calculate_common_emitter_circuit()
{
    m_common_emitter->calculate_data();
}

void Manager::show_data_from_common_emitter_circuit()
{
    m_common_emitter->convert_data();
    m_common_emitter->circuit_data();
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

void Manager::show_transistors()
{
    for (Transistor* transistor : m_transistors)
    {
        transistor->transistor_parameters();
    }
}

void Manager::show_transistors(const std::string& model)
{
    for (Transistor* transistor : m_transistors)
    {
        if (transistor->model() == model) {
            transistor->transistor_parameters();
            return;
        }
    }

    // If the loop completes without finding the transistor, throw an exception
    throw std::runtime_error("Transistor model not found: " + model);
}
