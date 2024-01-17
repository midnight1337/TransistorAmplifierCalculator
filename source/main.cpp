#include <iostream>
#include "../include/manager.h"


int main()
{
    std::string model = "BC237";
    std::string type = "NPN";
    int hfe = 200;
    float vbe = 0.6;

    Manager manager;
    manager.new_transistor(model, type, hfe, vbe);

    return 0;
}
