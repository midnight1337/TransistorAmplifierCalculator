#include <iostream>

#ifndef RESISTOR_H
#define RESISTOR_H


class Resistor
{
private:
    static int m_resistor_id;
    const int m_id;
    const std::string m_label;
    float m_rc;
    float m_re;
    float m_rbc;
    float m_rbe;
    float m_rl;

public:
    Resistor(float rc, float rbc, float rl, float multiplier, const std::string& label);
    Resistor(float rc, float re, float rbc, float rl, float multiplier, const std::string& label);
    Resistor(float rc, float re, float rbc, float rbe, float rl, float multiplier, const std::string& label);
    static float voltage_divider(float resistance_source, float resistance_ground, float source_voltage);
    static float calculate_in_parallel(int arg_count, const float *resistors);
    static float calculate_in_series(int arg_count, const float* resistors);
    float collector_resistor() const;
    float emitter_resistor() const;
    float base_collector_resistor() const;
    float base_emitter_resistor() const;
    float load_resistor() const;
    std::string label() const;
    void resistors_values();
};

#endif
