#include "../include/manager.h"
/*
TODO:
    1.In common_emitter.cpp call m_resistor->any_resistor() instead of doubling code in CE class
    2.Same as above for Capacitor
    3.Plot frequency analysis
    4.Collector Feedback amplifier
    5.Voltage gain freq analysis doesn't work as it should
    Calculate gain of transistor stage, then subtract by attenuation from Base HP filter
 */


int main() {
    Manager manager;
    manager.run();

    return 0;
}
