#include "afr-vexu-lib/scheduled.h"

namespace AFR::VexU{
    scheduled::scheduled(const scheduled_update_t& update_period)
            : update_period_(update_period), next_update_(0){}

    void scheduled::update(){
        if(update_period_ != 0){
            if(pros::millis() >= next_update_){
                next_update_ = pros::millis() + update_period_;
                update_private((pros::millis() - next_update_ + update_period_) / 1000.0);
            }
        }
    }

    void scheduled::set_update_period(scheduled_update_t update_period){
        update_period_ = update_period;
    }

    scheduled_update_t scheduled::get_update_period() const{
        return update_period_;
    }

    void scheduled::force_update(){
        update_private(-1);
    }
}
