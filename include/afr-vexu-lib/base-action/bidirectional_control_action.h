#ifndef VEX_U_2018_V5_INTAKE_CONTROL_ACTION_H
#define VEX_U_2018_V5_INTAKE_CONTROL_ACTION_H

#include "afr-lib/scheduled.h"
#include "afr-vexu-lib/base-readable/controller_readable.h"

namespace AFR::VexU::BaseAction{
    template<typename T>
    class bidirectional_control_action : public nameable{
        T second_val_, first_val_, no_val_;
        AFR::VexU::BaseReadable::controller_digital_readable* first_button_;
        AFR::VexU::BaseReadable::controller_digital_readable* second_button_;

    public:
        T get_value(double delta_seconds) override{
            if(second_button_ != nullptr && second_button_->is_pressed()){
                return second_val_;
            }
            else if(first_button_ != nullptr && first_button_->is_pressed()){
                return first_val_;
            }
            else{
                return no_val_;
            }
        }

        /**
         * Creates a set value action
         * @param update_period passed to scheduled
         * @param commandable the commandable to set
         * @param readable to be used
         * @param second readable to be used
         * @param name error_t value if error encountered
         */
        bidirectional_control_action(BaseReadable::controller_digital_readable* second_button,
                                     BaseReadable::controller_digital_readable* first_button, int16_t second_val,
                                     T first_val, T no_val,
                                     const std::string& name) :
                nameable(name), first_button_(first_button), second_button_(second_button), second_val_(second_val),
                first_val_(first_val), no_val_(no_val){}
    };
}

#endif //VEX_U_2018_V5_INTAKE_CONTROL_ACTION_H