#include <afr-vexu-lib/readable.h>

AFR::VexU::readable::readable(const scheduled_update_t& update_period, const std::any& initial_value)
        : scheduled(update_period), value(initial_value){}

std::any AFR::VexU::readable::get_value() const{
    return value;
}

