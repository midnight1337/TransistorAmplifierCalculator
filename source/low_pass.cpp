#include "../include/low_pass.h"


LowPass::LowPass(float first_order_resistance, float first_order_capacitance) : Filter(first_order_resistance, first_order_capacitance)
{}

LowPass::LowPass(float first_order_resistance, float first_order_capacitance, float second_order_resistance, float second_order_capacitance) :
        Filter(first_order_resistance, first_order_capacitance, second_order_resistance, second_order_capacitance)
{}

void LowPass::calculate_first_order_filter()
{

}

void LowPass::calculate_second_order_filter()
{

}

void LowPass::calculate_magnitude_of_first_order_filter()
{

}

void LowPass::calculate_magnitude_of_second_order_filter()
{

}
