#include "../include/manager.h"


int main() {
    Manager manager;
    float multiplier = 1000;
    float rbc = 480 * multiplier;
    float rbe = 73.2 * multiplier;
    float rc = 9.96 * multiplier;
    float re = 3.96 * multiplier;
    float vcc = 9.3;

    manager.new_bjt_transistor("Q0", "None", 156, 0.6);

    manager.breadboard_common_emitter_circuit("Q0", vcc, rc, re, rbc, rbe);
    manager.calculate_common_emitter_circuit();
    manager.show_data_from_common_emitter_circuit();

    return 0;
}
