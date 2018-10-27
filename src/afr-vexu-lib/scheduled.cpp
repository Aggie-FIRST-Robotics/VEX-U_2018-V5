#include <afr-vexu-lib/scheduled.h>

using steady_clock_n = std::chrono::steady_clock;

AFR::VexU::scheduled::scheduled(const unsigned int& update_period) : update_period_ms_(update_period),
                                                                     next_update_(steady_clock_n::now()){}

void AFR::VexU::scheduled::update(){
    if(steady_clock_n::now() >= next_update_){
        update_private(std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1>>>(
                steady_clock_n::now() - next_update_ + update_period_ms_).count());
        next_update_ = steady_clock_n::now() + update_period_ms_;
    }
}
