#include <iostream>
#include <cmath>

#ifndef CAPACITOR_H
#define CAPACITOR_H


class Capacitor
{
private:
    static int m_capacitor_id;
    const int m_id;
    const std::string m_label;
    float m_cc;
    float m_cb;
    float m_ce;

public:
    Capacitor(float cc, float cb, float ce, const std::string& label);
    static float calculate_capacitive_reactance(float capacitance, int frequency_sample);
    [[nodiscard]] float collector_capacitance() const;
    [[nodiscard]] float base_capacitance() const;
    [[nodiscard]] float emitter_capacitance() const;
    [[nodiscard]] std::string label() const;
    void capacitor_data();
};

#endif