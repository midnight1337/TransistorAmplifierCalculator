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

public:
    Transistor(const std::string& model, const std::string& type, int current_gain);
    virtual ~Transistor() = default;
    std::string model();
    int current_gain() const;
    virtual void transistor_parameters() = 0;
};

#endif
