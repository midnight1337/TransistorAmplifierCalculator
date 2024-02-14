#include "../include/manager.h"

Manager::Manager()
{
    m_common_emitter = nullptr;
    m_collector_feedback = nullptr;
}

Manager::~Manager()
{
    for (std::unique_ptr<Transistor>& transistor : m_transistors) { transistor.reset(); }
    for (std::unique_ptr<Resistor>& resistor : m_resistors) { resistor.reset(); }
    for (std::unique_ptr<Capacitor>& capacitor : m_capacitors) { capacitor.reset(); }

    m_common_emitter.reset();
    m_collector_feedback.reset();
}

void Manager::run()
{
    float VCC = 9;

    new_transistor("OC44", "NPN", 100, 0.3);
    new_resistor(10, 3.9, 470, 68, 1000, 1000, "Rangemaster");
    new_capacitor(0.01, 0.005, 47, "Rangemaster");

    new_transistor("BC239", "NPN", 300, 0.7);
    new_resistor(10, 0.1, 470, 47, 101, 39, 1000, "BigMuff");
    new_capacitor(1, 0, 1, "BigMuff");

//    breadboard_common_emitter_circuit("OC44", "Rangemaster", "Rangemaster", VCC);
    breadboard_collector_feedback_circuit("BC239", "BigMuff", "BigMuff", VCC);
}

void Manager::breadboard_common_emitter_circuit(const std::string& transistor_model, const std::string& resistor_label, const std::string& capacitor_label, float vcc)
{
    Bjt* transistor = dynamic_cast<Bjt*>(get_transistor(transistor_model));
    Resistor* resistor = get_resistor(resistor_label);
    Capacitor* capacitor = get_capacitor(capacitor_label);

    m_common_emitter =  std::make_unique<CommonEmitter>(CommonEmitter(transistor, resistor, capacitor, vcc));

    m_common_emitter->calculate_data();
    m_common_emitter->frequency_analysis(0, 3000);
    m_common_emitter->show_data();
}

void Manager::breadboard_collector_feedback_circuit(const std::string& transistor_model, const std::string& resistor_label, const std::string& capacitor_label, float vcc)
{
    Bjt* transistor = dynamic_cast<Bjt*>(get_transistor(transistor_model));
    Resistor* resistor = get_resistor(resistor_label);
    Capacitor* capacitor = get_capacitor(capacitor_label);

    m_collector_feedback = std::make_unique<CollectorFeedback>(CollectorFeedback(transistor, resistor, capacitor, vcc));

    m_collector_feedback->test();
    m_collector_feedback->show_data();
}

void Manager::new_transistor(const std::string& model, const std::string& type, float hfe, float vbe)
{
    std::unique_ptr<Transistor> transistor;

    if (type == "NPN" || type == "PNP")
    {
        transistor = std::make_unique<Bjt>(Bjt(model, type, hfe, vbe));
    }
    else
    {
        // If the loop completes without recognizing a transistor type, throw an exception
        throw std::runtime_error("Transistor type not known: " + type);
    }

    m_transistors.push_back(std::move(transistor));
}

void Manager::new_resistor(float rc, float re, float rbc, float rbe, float rl, float multiplier, const std::string& label)
{
    /* Used in Common Emitter Circuit */
    std::unique_ptr<Resistor> resistor = std::make_unique<Resistor>(Resistor(rc, re, rbc, rbe, rl, multiplier, label));

    m_resistors.push_back(std::move(resistor));
}

void Manager::new_resistor(float rc, float re, float rbc, float rbe, float rl, float rs, float multiplier, const std::string& label)
{
    /* Used in (Common Emitter - Collector Feedback - Shunt emitter) Circuit */
    std::unique_ptr<Resistor> resistor = std::make_unique<Resistor>(Resistor(rc, re, rbc, rbe, rl, rs, multiplier, label));

    m_resistors.push_back(std::move(resistor));
}

void Manager::new_capacitor(float cc, float cb, float ce, const std::string &label)
{
    /* Used in Common Emitter Circuit */
    std::unique_ptr<Capacitor> capacitor = std::make_unique<Capacitor>(Capacitor(cc, cb, ce, label));

    m_capacitors.push_back(std::move(capacitor));
}

Transistor* Manager::get_transistor(const std::string& model)
{
    for (const std::unique_ptr<Transistor>& transistor : m_transistors)
    {
        if (transistor->model() == model)
        {
            return transistor.get();
        }
    }

    throw std::runtime_error("Transistor model not found: " + model);
}

Resistor* Manager::get_resistor(const std::string& label)
{
    for (const std::unique_ptr<Resistor>& resistor : m_resistors)
    {
        if (resistor->label() == label)
        {
            return resistor.get();
        }
    }

    throw std::runtime_error("Resistor label not found: " + label);
}

Capacitor* Manager::get_capacitor(const std::string& label)
{
    for (const std::unique_ptr<Capacitor>& capacitor : m_capacitors)
    {
        if (capacitor->label() == label)
        {
            return capacitor.get();
        }
    }

    throw std::runtime_error("Capacitor label not found: " + label);
}

void Manager::show_transistors()
{
    for (const std::unique_ptr<Transistor>& transistor : m_transistors)
    {
        transistor->transistor_data();
    }
}

void Manager::show_transistors(const std::string& model)
{
    for (const std::unique_ptr<Transistor>& transistor : m_transistors)
    {
        if (transistor->model() == model)
        {
            transistor->transistor_data();
            return;
        }
    }

    throw std::runtime_error("Transistor model not found: " + model);
}
