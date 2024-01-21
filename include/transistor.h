#include <iostream>

#ifndef TRANSISTOR_H
#define TRANSISTOR_H


class Transistor
{
private:
    static int m_transistor_id;

protected:
    Transistor(const std::string& model, const std::string& type, int current_gain);
    std::string m_model;
    std::string m_type;
    int m_current_gain;
    const int m_id;

public:
    std::string model();
    virtual void transistor_info() = 0;
};

#endif
