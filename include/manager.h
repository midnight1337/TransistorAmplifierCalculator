#include <iostream>
#include <vector>
#include "transistor.h"
#include "bjt.h"
#include "common_emitter.h"

#ifndef MANAGER_H
#define MANAGER_H


class Manager
{
private:
    std::vector<Transistor*> m_transistors;
    CommonEmitter m_common_emitter;

public:
    Transistor* get_transistor(const std::string& model);
    void new_bjt_transistor(const std::string& model, const std::string& type, int hfe, float vbe);
    void show_transistors();
    void show_transistors(const std::string& model);
    void breadboard_common_emitter_circuit(const std::string& transistor_model, int vcc, int rc, int re, int rbc, int rbe);
    void calculate_common_emitter_circuit();
};

#endif
