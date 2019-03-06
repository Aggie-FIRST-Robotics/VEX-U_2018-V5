#include "afr-vexu-lib/cached_operation.h"

namespace AFR::VexU{
    cached_operation::cached_operation(scheduled_update_t update_period, const T& initial_value, const std::string& name)
            : scheduled(update_period), nameable(name), cached_value(initial_value){}

    T cached_operation::get_value(){
        if(get_update_period() == 0){
            force_update();
        }
        return cached_value;
    }
}
