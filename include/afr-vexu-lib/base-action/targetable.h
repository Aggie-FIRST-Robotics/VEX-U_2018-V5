#ifndef VEX_U_2018_V5_TARGETABLE_H
#define VEX_U_2018_V5_TARGETABLE_H

#include <functional>
#include "afr-lib/nameable.h"
#include "commandable.h"

namespace AFR::VexU::BaseAction{


    template<typename Read_T>
    class targetable : public commandable<Read_T> {
        
        std::function<Read_T()> target_function_;
        Read_T target_;
        Read_T initial_value_;
        
        Read_T value_function() {
            return target_;
        }
        
    public:
        targetable(scheduled_update_t update_period, Read_T initial_value,
                   Read_T initial_target, const std::string& name)
                : commandable<Read_T>(update_period, name), 
                initial_value_(initial_value),
                target_(initial_target),
                target_function_(this->value_function){}

        virtual bool is_in_range(Read_T tolerance) = 0;
        
        void set_target(const std::function<Read_T()>& target_function){
            target_function_ = target_function;
        }
        
        void set_target(const Read_T& target) {
            target_ = target;
            target_function_ = this->value_function;
        }
        
        Read_T get_target() {
            return target_function_();
        }
        
    };
}

#endif //VEX_U_2018_V5_TARGETABLE_H
