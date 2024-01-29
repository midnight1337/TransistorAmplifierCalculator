#include "circuit.h"

#ifndef COMMON_EMITTER_H
#define COMMON_EMITTER_H


class CommonEmitter : public Circuit <Bjt>
{
private:
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
    void calculate_cutoff_frequency_of_input_stage() override;
    void calculate_cutoff_frequency_of_output_stage() override;
    void calculate_cutoff_frequency_of_emitter_stage() override;

    void input_impedance_frequency_analysis(int frequency_range) override;
    void output_impedance_frequency_analysis(int frequency_range) override;
    float transistor_impedance_frequency_analysis(int frequency_sample) override;
    void voltage_gain_frequency_analysis(int frequency_range) override;
    void cutoff_frequency_input_stage_frequency_analysis(int frequency_range) override;

public:
    CommonEmitter(Bjt* transistor, Resistor* resistor, Capacitor* capacitor, float vcc);
    ~CommonEmitter() override = default;
    void calculate_data() override;
    void circuit_data() override;
    void convert_data() override;
};

#endif
