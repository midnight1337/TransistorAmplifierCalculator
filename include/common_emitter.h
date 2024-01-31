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

    float calculate_input_impedance(int frequency_sample) override;
    float calculate_output_impedance(int frequency_sample) override;
    float calculate_transistor_impedance(int frequency_sample) override;
    float calculate_voltage_gain(int frequency_sample) override;
    float calculate_loss_of_input_stage(int frequency_sample) override;
    float calculate_loss_of_output_stage(int frequency_sample) override;
    void frequency_analysis(int frequency_start, int frequency_stop) override;

    float calculate_transistor_emitter_impedance(int frequency_sample);

public:
    CommonEmitter(Bjt* transistor, Resistor* resistor, Capacitor* capacitor, float vcc);
    ~CommonEmitter() override = default;
    void calculate_data() override;
    void circuit_data() override;
    void convert_data() override;
};

#endif
