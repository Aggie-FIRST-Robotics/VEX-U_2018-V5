//
// Created by Buzzec on 10/26/2018.
//

#ifndef VEX_U_2018_V5_ORDERED_INPUT_H
#define VEX_U_2018_V5_ORDERED_INPUT_H

#include "readable.h"
#include <string>

namespace AFR::VexU{
    typedef unsigned int order_t;

    class ordered_input{
    public:
        ordered_input(order_t order, readable* input);
        order_t get_order();
        readable* get_input();

    private:
        order_t order;
        readable* input;
    };


}

#endif //VEX_U_2018_V5_ORDERED_INPUT_H
