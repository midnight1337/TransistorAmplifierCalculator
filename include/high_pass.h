#include "filter.h"

#ifndef HIGH_PASS_H
#define HIGH_PASS_H


class HighPass : public Filter
{
public:
    HighPass(float first_order_resistance, float first_order_capacitance);
    HighPass(float first_order_resistance, float first_order_capacitance, float second_order_resistance, float second_order_capacitance);
    void calculate_first_order_filter() override;
    void calculate_second_order_filter() override;
    void calculate_magnitude_of_first_order_filter() override;
    void calculate_magnitude_of_second_order_filter() override;
};


#endif
