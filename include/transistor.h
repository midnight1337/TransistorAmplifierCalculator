#include <iostream>


class Transistor
{
    private:
        static int m_transistor_id;

    protected:
        std::string m_model;
        std::string m_type;
        int m_current_gain;
        const int m_id;

        std::string model();
        std::string type();
        int current_gain();
        int id();

        virtual ~Transistor() = 0;
};
