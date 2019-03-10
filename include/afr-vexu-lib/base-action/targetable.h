#ifndef VEX_U_2018_V5_TARGETABLE_H
#define VEX_U_2018_V5_TARGETABLE_H

#include "afr-lib/commandable.h"
#include "afr-lib/operation.h"

namespace AFR::VexU::BaseAction{


    template<typename Read_T>
    class targetable : public commandable<Read_T>, public operation<Read_T> {
        
        Read_T target_;
        Read_T initial_value_;
        
        Read_T value_function() {
            return target_;
        }
        
    public:
        targetable(scheduled_update_t update_period, Read_T initial_value,
                   Read_T initial_target, const std::string& name)
                : nameable(name),
                commandable<Read_T>(update_period, name), 
                initial_value_(initial_value),
                target_(initial_target),
                operation<Read_T>(this->value_function, name){}

        virtual bool is_in_range(Read_T tolerance) = 0;
        
        void set_target(const std::function<Read_T()>& target_function){
            operation<Read_T>::set_function(target_function);
        }
        
        void set_target(const Read_T& target) {
            target_ = target;
            operation<Read_T>::set_function(this->value_function);
        }
        
        Read_T get_target() {
            return operation<Read_T>::get_function()();
        }
        
    };
}

#endif //VEX_U_2018_V5_TARGETABLE_H
