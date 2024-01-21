#include "../include/manager.h"


int main() {
    Manager manager;
    manager.new_transistor("BC237", "NPN", 200, 0.6);
    manager.show_transistors();
    manager.common_emitter_circuit("BC237", 9, 1, 1, 1, 1);

    return 0;
}
