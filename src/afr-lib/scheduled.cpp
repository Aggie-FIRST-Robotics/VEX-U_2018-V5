#include <cmath>
#include <chrono>

#include "afr-lib/scheduled.h"

namespace AFR::VexU{
    std::unordered_map<std::string, scheduled*> scheduled::scheduled_list_{};
    std::function<scheduled_update_t()> scheduled::time_function_{};
    double scheduled::scaling_factor_to_seconds_{1.0};

    scheduled::scheduled(const scheduled_update_t& update_period, const std::string& name) :
            nameable(name), update_period_(update_period), next_update_(INT64_MAX), enabled_(true){
        if(!scheduled_list_.emplace(get_name(), this).second) {
            throw std::runtime_error{"Cannot insert scheduled for name: " + get_name()};
        }
    }

    scheduled::~scheduled(){
        scheduled_list_.erase(get_name());
    }

    void scheduled::update_all() {
        for(auto& itr : scheduled_list_){
            auto scheduled = itr.second;
            if(scheduled->next_update_ == INT64_MAX){
                scheduled->update_private(-1);
                scheduled->next_update_ = time_function_() + scheduled->update_period_;
            }
            else if(scheduled->update_period_ != 0){
                if(time_function_() >= scheduled->next_update_ && scheduled->enabled_){
                    scheduled->update_private((time_function_() - scheduled->next_update_ + scheduled->update_period_) *
                                              scaling_factor_to_seconds_);
                    scheduled->next_update_ = time_function_() + scheduled->update_period_;
                }
            }
            else{
                scheduled->update_private((time_function_() - scheduled->next_update_) * scaling_factor_to_seconds_);
                scheduled->next_update_ = time_function_();
            }
        }
    }

    void scheduled::set_enabled(bool enabled) {
        if(enabled_ != enabled){
            if(enabled_){
                on_disable();
                enabled_ = false;
            }
            else{
                on_enable();
                enabled_ = true;
            }
        }
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

    void scheduled::set_time_function(const std::function<scheduled_update_t()>& time_function){
        time_function_ = time_function;
    }

    void scheduled::set_scaling_factor(double scaling_factor_to_seconds){
        scaling_factor_to_seconds_ = scaling_factor_to_seconds;
    }

    void scheduled::init(){
        time_function_ = []() -> scheduled_update_t{
            throw std::runtime_error{"No time function set!"};
        };
    }


}
