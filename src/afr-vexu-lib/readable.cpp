#include <afr-vexu-lib/readable.h>

AFR::VexU::readable::readable(const scheduled_update_t& update_period, const std::any& initial_value, error_t* result)
        : scheduled(update_period), value(initial_value){
    if(result != nullptr){
        *result = SUCCESS;
    }
}

AFR::VexU::error_t AFR::VexU::readable::get_value(std::any& result) const{
    result = value;
    return SUCCESS;
}
