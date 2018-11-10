#include <afr-vexu-lib/scheduled.h>

using steady_clock_n = std::chrono::steady_clock;

AFR::VexU::scheduled::scheduled(const unsigned int& update_period, error_t* result) : update_period_(update_period),
                                                                                      next_update_(
                                                                                              steady_clock_n::now()){
    if(result != nullptr){
        *result = SUCCESS;
    }
}

AFR::VexU::error_t AFR::VexU::scheduled::update(){
    if(steady_clock_n::now() >= next_update_){
        update_private(std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1>>>(
                steady_clock_n::now() - next_update_ + update_period_).count());
        next_update_ = steady_clock_n::now() + update_period_;
    }
    return SUCCESS;
}
