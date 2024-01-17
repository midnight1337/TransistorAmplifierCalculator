#include <iostream>
#include <vector>
#include "transistor.h"


class Manager
{
    private:
        std::vector<Transistor*> m_transistors;
    
    public:
        Manager() = default;
        void new_transistor(std::string model, std::string type, int hfe, float vbe);

        Transistor* transistor(std::string& model);
};
