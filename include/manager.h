#include <iostream>
#include <vector>
#include <memory.h>
#include "transistor.h"
#include "bjt.h"
#include "circuit.h"
#include "common_emitter.h"
#include "collector_feedback.h"
#include "resistor.h"
#include "capacitor.h"

#ifndef MANAGER_H
#define MANAGER_H


class Manager
{
private:
    std::vector<std::unique_ptr<Transistor>> m_transistors;
    std::vector<std::unique_ptr<Resistor>> m_resistors;
    std::vector<std::unique_ptr<Capacitor>> m_capacitors;
    std::unique_ptr<CommonEmitter> m_common_emitter;
    std::unique_ptr<CollectorFeedback> m_collector_feedback;

    Transistor* get_transistor(const std::string& model);
    Resistor* get_resistor(const std::string& label);
    Capacitor* get_capacitor(const std::string& label);

    void new_transistor(const std::string &model, const std::string &type, float hfe, float vbe);
    void new_resistor(float rc, float re, float rbc, float rbe, float rl, float multiplier, const std::string& label);
    void new_resistor(float rc, float re, float rbc, float rbe, float rl, float rs, float multiplier, const std::string &label);
    void new_capacitor(float cc, float cb, float ce, const std::string& label);
    void breadboard_common_emitter_circuit(const std::string &transistor_model, const std::string &resistor_label, const std::string &capacitor_label, float vcc);
    void breadboard_collector_feedback_circuit(const std::string &transistor_model, const std::string &resistor_label, const std::string &capacitor_label, float vcc);
    void show_transistors();
    void show_transistors(const std::string& model);

public:
    Manager();
    ~Manager();
    void run();
};

#endif
