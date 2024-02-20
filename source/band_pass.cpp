#include "../include/band_pass.h"


BandPass::BandPass(float first_order_resistance, float first_order_capacitance) : Filter(first_order_resistance, first_order_capacitance)
{}

BandPass::BandPass(float first_order_resistance, float first_order_capacitance, float second_order_resistance, float second_order_capacitance) :
        Filter(first_order_resistance, first_order_capacitance, second_order_resistance, second_order_capacitance)
{}

void BandPass::calculate_first_order_filter()
{

}

void BandPass::calculate_second_order_filter()
{

}

void BandPass::calculate_magnitude_of_first_order_filter()
{

}

void BandPass::calculate_magnitude_of_second_order_filter()
{

}
