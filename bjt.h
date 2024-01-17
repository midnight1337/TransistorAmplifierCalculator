#include <iostream>
#include "transistor.h"


class Bjt : public Transistor
{
private:
    float m_vbe;

public:
    Bjt(std::string model, std::string type, int hfe, float vbe);
    ~Bjt() = default;

    float vbe();
};
