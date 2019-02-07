#include "afr-vexu-lib/scheduled.h"

using steady_clock_n = std::chrono::steady_clock;

AFR::VexU::scheduled::scheduled(const AFR::VexU::scheduled_update_t& update_period, error_t* result) : update_period_(
        update_period),
                                                                                                       next_update_(0){
    if(result != nullptr){
        *result = SUCCESS;
    }
}

AFR::VexU::error_t AFR::VexU::scheduled::update(){
    if(pros::millis() >= next_update_){
        next_update_ = pros::millis() + update_period_;
        return update_private((pros::millis() - next_update_ + update_period_) / 1000.0);
    }
    return SUCCESS;
}

AFR::VexU::error_t AFR::VexU::scheduled::set_update_period(const AFR::VexU::scheduled_update_t& update_period){
    update_period_ = update_period;
    return SUCCESS;
}
