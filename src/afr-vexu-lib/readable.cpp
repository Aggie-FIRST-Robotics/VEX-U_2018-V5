#include "afr-vexu-lib/readable.h"

namespace AFR::VexU{
    readable::readable(scheduled_update_t update_period, const std::any& initial_value, const std::string& name)
            : scheduled(update_period), nameable(name), value(initial_value){}

    std::any readable::get_value(){
        if(get_update_period() == 0){
            force_update();
        }
        return value;
    }
}
