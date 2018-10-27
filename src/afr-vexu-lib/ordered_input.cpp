//
// Created by Buzzec on 10/26/2018.
//

#include <afr-vexu-lib/ordered_input.h>

AFR::VexU::ordered_input::ordered_input(unsigned int order, readable* input)
        : order(order), input(input){}

unsigned int AFR::VexU::ordered_input::get_order(){
    return order;
}

AFR::VexU::readable* AFR::VexU::ordered_input::get_input(){
    return input;
}