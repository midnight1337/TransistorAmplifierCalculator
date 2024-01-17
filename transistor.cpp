#include "transistor.h"

Transistor::m_transistor_id = 0;

std::string Transistor::model() { return m_model; }

std::string Transistor::type() { return m_type; }

int Transistor::current_gain() { return m_current_gain; }

int Transistor::id() { return m_id; }

Transistor::~Transistor() {}
