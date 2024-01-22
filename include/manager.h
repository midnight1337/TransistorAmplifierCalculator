#include <iostream>
#include <vector>
#include "transistor.h"
#include "bjt.h"
#include "circuit.h"
#include "common_emitter.h"

#ifndef MANAGER_H
#define MANAGER_H


class Manager
{
private:
    std::vector<Transistor*> m_transistors;
    std::vector<Circuit*> m_circuits;
    CommonEmitter* m_common_emitter;

public:
    Manager();
    ~Manager();
    Transistor* get_transistor(const std::string& model);
    void new_bjt_transistor(const std::string& model, const std::string& type, int hfe, float vbe);
    void show_transistors();
    void show_transistors(const std::string& model);
    void breadboard_common_emitter_circuit(const std::string& transistor_model, float vcc, float rc, float re, float rbc, float rbe);
    void calculate_common_emitter_circuit();
    void show_data_from_common_emitter_circuit();
};

#endif
