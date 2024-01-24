#include "transistor.h"
#include "bjt.h"

#ifndef CIRCUIT_H
#define CIRCUIT_H


template <typename TransistorType = Transistor>
class Circuit
{
protected:
    TransistorType* m_transistor;
    // dc analysis
    float m_vcc{};
    float m_vc{};
    float m_vb{};
    float m_ve{};
    float m_vce{};
    float m_ic{};
    float m_ib{};
    float m_ie{};
    float m_ic_sat{};
    float m_gm{};

    // ac analysis
    float m_re_ac{};
    float m_rpi_dc{};
    float m_rpi_ac{};
    float m_av_ac{};
    float m_av_ac_db{};
    float m_av_dc{};
    float m_av_dc_db{};

    //frequency dependent analysis (above as well?)
    float m_z_in{};
    float m_z_out{};

    virtual void calculate_data() = 0;
    virtual void circuit_data() = 0;
    virtual void convert_data() = 0;

    virtual void calculate_base_voltage() = 0;
    virtual void calculate_base_current() = 0;
    virtual void calculate_collector_voltage() = 0;
    virtual void calculate_collector_current() = 0;
    virtual void calculate_emitter_voltage() = 0;
    virtual void calculate_emitter_current() = 0;
    virtual void calculate_saturation_current() = 0;
    virtual void calculate_bias_voltage() = 0;
    virtual void calculate_transistor_internal_emitter_resistance() = 0;
    virtual void calculate_transistor_transconductance() = 0;

    // AC frequency dependent calculations
    virtual void calculate_transistor_impedance() = 0;
    virtual void calculate_input_impedance() = 0;
    virtual void calculate_output_impedance() = 0;
    virtual void calculate_voltage_gain() = 0;

public:
    Circuit();
    Circuit(TransistorType* transistor, float vcc);
    virtual ~Circuit() = default;
};

template <typename TransistorType>
Circuit<TransistorType>::Circuit() = default;

template <typename TransistorType>
Circuit<TransistorType>::Circuit(TransistorType* transistor, float vcc)
{
    m_transistor = transistor;
    m_vcc = vcc;
}

#endif
