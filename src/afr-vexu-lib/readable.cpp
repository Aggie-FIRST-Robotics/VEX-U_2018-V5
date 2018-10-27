//
// Created by Buzzec on 10/26/2018.
//

#include <afr-vexu-lib/readable.h>

AFR::VexU::readable::readable(const unsigned int& update_period_ms, const std::any& initial_value)
        : scheduled(update_period_ms), value(initial_value){}

std::any AFR::VexU::readable::get_value() const{
    return value;
}

