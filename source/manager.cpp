#include "../include/manager.h"

Manager::Manager()
{
    m_common_emitter = nullptr;
}

Manager::~Manager()
{
    for (Transistor* transistor : m_transistors) { delete transistor; }
    for (Resistor* resistor : m_resistors) { delete resistor; }
    for (Capacitor* capacitor : m_capacitors) { delete capacitor; }

    delete m_common_emitter;
}

void Manager::run()
{
    const float VCC = 9;

    new_transistor("OC44", "NPN", 100, 0.3);
    new_resistor(10, 3.9, 470, 68, 1000, 1000, "Rangemaster");
    new_capacitor(0.01, 0.005, 47, "Rangemaster");

    breadboard_common_emitter_circuit("OC44", "Rangemaster", "Rangemaster", VCC);
}

void Manager::breadboard_common_emitter_circuit(const std::string& transistor_model, const std::string& resistor_label, const std::string& capacitor_label, float vcc)
{
    Bjt* transistor = dynamic_cast<Bjt*>(get_transistor(transistor_model));
    Resistor* resistor = get_resistor(resistor_label);
    Capacitor* capacitor = get_capacitor(capacitor_label);

    m_common_emitter =  new CommonEmitter(transistor, resistor, capacitor, vcc);

    m_common_emitter->calculate_data();
    m_common_emitter->convert_data();
    m_common_emitter->circuit_data();
}

void Manager::new_transistor(const std::string& model, const std::string& type, int hfe, float vbe)
{
    Transistor* transistor;
    if (type == "NPN" || type == "PNP") { transistor = new Bjt(model, type, hfe, vbe); }
    else
    {
        // If the loop completes without recognizing a transistor type, throw an exception
        throw std::runtime_error("Transistor type not known: " + type);
    }

    m_transistors.push_back(transistor);
}

void Manager::new_resistor(float rc, float re, float rbc, float rl, float multiplier, const std::string &label)
{
    /* Used in Collector Feedback Circuit?? */
    Resistor* resistor = new Resistor(rc, re, rbc, rl, multiplier, label);

    m_resistors.push_back(resistor);
}

void Manager::new_resistor(float rc, float re, float rbc, float rbe, float rl, float multiplier, const std::string &label)
{
    /* Used in Common Emitter Circuit */
    Resistor* resistor = new Resistor(rc, re, rbc, rbe, rl, multiplier, label);

    m_resistors.push_back(resistor);
}

void Manager::new_capacitor(float cc, float ce, float cb, const std::string &label)
{
    /* Used in Common Emitter Circuit */
    Capacitor* capacitor = new Capacitor(cc, ce, cb, label);

    m_capacitors.push_back(capacitor);
}

Transistor* Manager::get_transistor(const std::string& model)
{
    for (Transistor* transistor : m_transistors)
    {
        if (transistor->model() == model) { return transistor; }
    }

    // If the loop completes without finding the transistor, throw an exception
    throw std::runtime_error("Transistor model not found: " + model);
}

Resistor* Manager::get_resistor(const std::string &label)
{
    for (Resistor* resistor : m_resistors)
    {
        if (resistor->label() == label) { return resistor; }
    }

    // If the loop completes without finding the resistor, throw an exception
    throw std::runtime_error("Resistor label not found: " + label);
}

Capacitor* Manager::get_capacitor(const std::string &label)
{
    for (Capacitor* capacitor : m_capacitors)
    {
        if (capacitor->label() == label) { return capacitor; }
    }

    // If the loop completes without finding the capacitor, throw an exception
    throw std::runtime_error("Capacitor label not found: " + label);
}

void Manager::show_transistors()
{
    for (Transistor* transistor : m_transistors) { transistor->transistor_parameters(); }
}

void Manager::show_transistors(const std::string& model)
{
    for (Transistor* transistor : m_transistors)
    {
        if (transistor->model() == model)
        {
            transistor->transistor_parameters();
            return;
        }
    }

    // If the loop completes without finding the transistor, throw an exception
    throw std::runtime_error("Transistor model not found: " + model);
}
