#include "afr-vexu-lib/ordered_input.h"

AFR::VexU::ordered_input::ordered_input(const order_t& order, readable* input, error_t* result)
        : order(order), input(input){
    if(result != nullptr){
        *result = SUCCESS;
    }
}

AFR::VexU::error_t AFR::VexU::ordered_input::get_order(order_t& result) const{
    result = order;
    return SUCCESS;
}

AFR::VexU::error_t AFR::VexU::ordered_input::get_input(readable*& result) const{
    result = input;
    return SUCCESS;
}