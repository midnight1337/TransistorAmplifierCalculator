#include <iostream>

#ifndef CAPACITOR_H
#define CAPACITOR_H


class Capacitor
{
private:
    const std::string m_label;
    float m_cc;
    float m_ce;
    float m_cb;

public:
    Capacitor(float cc, float ce, float cb, const std::string& label);
    static float calculate_reactance(float capacitance, int frequency_sample);
    std::string label() const;
};

#endif