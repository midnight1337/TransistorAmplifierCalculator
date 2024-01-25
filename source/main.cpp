#include "../include/manager.h"


int main() {
    Manager manager;
    const float vcc = 9;

    manager.new_bjt_transistor("CE0", "NPN", 156, 0.6);
    manager.new_bjt_transistor("OC44", "PNP", 100, 0.3);
    manager.new_resistor(10, 3.9, 470, 68, 1000, "Rangemaster");
    manager.new_resistor(9.96, 3.96, 480, 73.2, 1000, "test");
    manager.new_capacitor(1, 1, 1, "CE0");

    manager.breadboard_common_emitter_circuit("OC44", "Rangemaster", "CE0", vcc);
    manager.calculate_common_emitter_circuit();
    manager.show_data_from_common_emitter_circuit();

    return 0;
}
