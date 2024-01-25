#include <iostream>
#include <vector>
#include "transistor.h"
#include "bjt.h"
#include "circuit.h"
#include "common_emitter.h"
#include "resistor.h"
#include "capacitor.h"

#ifndef MANAGER_H
#define MANAGER_H


class Manager
{
private:
    std::vector<Transistor*> m_transistors;
    std::vector<Resistor*> m_resistors;
    std::vector<Capacitor*> m_capacitors;
    CommonEmitter* m_common_emitter;

public:
    Manager();
    ~Manager();
    Transistor* get_transistor(const std::string& model);
    Resistor* get_resistor(const std::string& label);
    Capacitor* get_capacitor(const std::string& label);
    void new_bjt_transistor(const std::string& model, const std::string& type, int hfe, float vbe);
    void new_resistor(float rc, float rbc, float re, float multiplier, const std::string& label);
    void new_resistor(float rc, float re, float rbc, float rbe, float multiplier, const std::string& label);
    void new_capacitor(float cc, float cb, float ce, const std::string& label);
    void show_transistors();
    void show_transistors(const std::string& model);
    void breadboard_common_emitter_circuit(const std::string& transistor_model, float vcc, float rc, float re, float rbc, float rbe);
    void calculate_common_emitter_circuit();
    void show_data_from_common_emitter_circuit();
};

#endif
