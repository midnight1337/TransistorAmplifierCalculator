#include "../include/high_pass.h"


HighPass::HighPass(float first_order_resistance, float first_order_capacitance) : Filter(first_order_resistance, first_order_capacitance)
{}

HighPass::HighPass(float first_order_resistance, float first_order_capacitance, float second_order_resistance, float second_order_capacitance) :
        Filter(first_order_resistance, first_order_capacitance, second_order_resistance, second_order_capacitance)
{}

void HighPass::calculate_first_order_filter()
{

}

void HighPass::calculate_second_order_filter()
{

}

void HighPass::calculate_magnitude_of_first_order_filter()
{

}

void HighPass::calculate_magnitude_of_second_order_filter()
{

}
