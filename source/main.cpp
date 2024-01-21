#include "../include/manager.h"


int main() {
    Manager manager;

    manager.new_bjt_transistor("BC237", "NPN", 200, 0.6);

    manager.show_transistors();
    manager.show_transistors("BC237");

    manager.breadboard_common_emitter_circuit("BC237", 9, 1, 1, 1, 1);
    manager.calculate_common_emitter_circuit();

    return 0;
}
