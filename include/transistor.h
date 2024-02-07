#include <iostream>

#ifndef TRANSISTOR_H
#define TRANSISTOR_H


class Transistor
{
private:
    static int m_transistor_id;

protected:
    const int m_id;
    std::string m_model;
    std::string m_type;

public:
    Transistor(const std::string& model, const std::string& type);
    virtual ~Transistor() = default;
    virtual void transistor_data() = 0;
    std::string model();
};

#endif
