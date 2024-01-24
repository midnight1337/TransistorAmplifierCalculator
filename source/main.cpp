#include "../include/manager.h"


int main() {
    Manager manager;
    float multiplier = 1000;
//    float rbc = 480 * multiplier;
//    float rbe = 73.2 * multiplier;
//    float rc = 9.96 * multiplier;
//    float re = 3.96 * multiplier;
//    float vcc = 9.3;
    float rbc = 470 * multiplier;
    float rbe = 68 * multiplier;
    float rc = 10 * multiplier;
    float re = 3.9 * multiplier;
    float vcc = 9;

    manager.new_bjt_transistor("Q0", "None", 156, 0.6);
    manager.new_bjt_transistor("OC44", "None", 100, 0.3);

    manager.breadboard_common_emitter_circuit("OC44", vcc, rc, re, rbc, rbe);
    manager.calculate_common_emitter_circuit();
    manager.show_data_from_common_emitter_circuit();

    return 0;
}
