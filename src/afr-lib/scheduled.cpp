#include "afr-lib/scheduled.h"

namespace AFR::VexU{
    scheduled::scheduled(const scheduled_update_t& update_period, const std::string& name)
            : nameable(name), update_period_(update_period), next_update_(0), enabled_(true) {
                scheduled_list.emplace(name, this);
            }

    scheduled::~scheduled() {
        scheduled_list.erase(get_name());
    }

    void scheduled::update_all() {
        for(auto itr : scheduled_list) {
            if(itr->second->update_period_ != 0){
                if(pros::millis() >= itr->second->next_update_ && itr->second->enabled_){
                    itr->second->update_private((pros::millis() - itr->second->next_update_ + itr->second->update_period_) / 1000.0);
                    itr->second->next_update_ = pros::millis() + itr->second->update_period_;
                }
            }
        }
    }
    
    void scheduled::set_enabled(bool enabled) {
        enabled_ = enabled;
    }
    
    bool scheduled::is_enabled() {
        return enabled_;
    }

    void scheduled::set_update_period(scheduled_update_t update_period){
        update_period_ = update_period;
    }

    scheduled_update_t scheduled::get_update_period() const{
        return update_period_;
    }
    
    
}
