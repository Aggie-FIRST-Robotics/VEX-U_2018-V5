#ifndef VEX_U_2018_V5_ORDERED_INPUT_H
#define VEX_U_2018_V5_ORDERED_INPUT_H

#include <string>

#include "readable.h"

namespace AFR::VexU{
    typedef unsigned int order_t;

    class ordered_input{
        order_t order;
        readable* input;

    public:
        ordered_input(const order_t& order, readable* input, error_t* result = nullptr);
        error_t get_order(order_t& result) const;
        error_t get_input(readable*& result) const;
    };
}

#endif //VEX_U_2018_V5_ORDERED_INPUT_H
