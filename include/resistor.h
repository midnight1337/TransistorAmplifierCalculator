#include <iostream>
#include <vector>

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
    float m_rs;

public:
    Resistor(float rc, float rbc, float rl, float multiplier, const std::string& label);
    Resistor(float rc, float re, float rbc, float rl, float multiplier, const std::string& label);
    Resistor(float rc, float re, float rbc, float rbe, float rl, float multiplier, const std::string& label);
    Resistor(float rc, float re, float rbc, float rbe, float rl, float rs, float multiplier, const std::string& label);
    static float calculate_resistance_in_parallel(const std::vector<float>& resistors);
    static float calculate_resistance_in_series(const std::vector<float>& resistances);
    float collector_resistance() const;
    float emitter_resistance() const;
    float base_collector_resistance() const;
    float base_emitter_resistance() const;
    float load_resistance() const;
    float source_resistance() const;
    std::string label() const;
    void resistor_data();
};

#endif
