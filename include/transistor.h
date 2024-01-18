#include <iostream>

#ifndef TRANSISTOR_H
#define TRANSISTOR_H


class Transistor
{
    private:
        static int m_transistor_id;

    protected:
        std::string m_model;
        std::string m_type;
        int m_current_gain;
        const int m_id;

        Transistor(std::string model, std::string type, int current_gain);
        std::string model();
        std::string type();
        int current_gain();
        int id();

        friend class Manager;
};

#endif
