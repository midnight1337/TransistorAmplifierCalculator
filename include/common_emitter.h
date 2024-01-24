#include "circuit.h"
#include "transistor.h"
#include "bjt.h"
#include "resistor.h"

#ifndef COMMON_EMITTER_H
#define COMMON_EMITTER_H


class CommonEmitter : public Circuit <Bjt>
{
private:
    float m_rbc{};
    float m_rbe{};
    float m_rc{};
    float m_re{};

    void calculate_base_voltage() override;
    void calculate_base_current() override;
    void calculate_collector_voltage() override;
    void calculate_collector_current() override;
    void calculate_emitter_voltage() override;
    void calculate_emitter_current() override;
    void calculate_saturation_current() override;
    void calculate_bias_voltage() override;
    void calculate_transistor_internal_emitter_resistance() override;
    void calculate_transistor_impedance() override;
    void calculate_transistor_transconductance() override;
    void calculate_input_impedance() override;
    void calculate_output_impedance() override;
    void calculate_voltage_gain() override;

public:
    CommonEmitter() = default;
    CommonEmitter(Bjt *transistor, float vcc, float rc, float re, float rbc, float rbe);
    ~CommonEmitter() override = default;
    void calculate_data() override;
    void circuit_data() override;
    void convert_data() override;
};

#endif
