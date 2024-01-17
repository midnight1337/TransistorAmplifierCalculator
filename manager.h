#include <iostream>
#include "transistor.h"


class Manager
{
    private:
        int m_transistor_count = 10;
        int m_transistor_counter = 0;
        Transistor* m_transistors[m_transistor_count];
    
    public:
        Manager() = default;
        void new_transistor(std::string& model, std::string& type, int hfe, float vbe);

        Transistor* transistor(std::string& model);
};
