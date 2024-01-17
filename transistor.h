#include <iostream>


class Transistor
{
    protected:
        std::string m_model;
        std::string m_type;
        int m_current_gain;

        std::string model();
        std::string type();
        int current_gain();
        void initialise(std::string& model, std::string& type, int& current_gain);
        
        virtual ~Transistor() = default;
};
