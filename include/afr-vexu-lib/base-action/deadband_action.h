#ifndef VEX_U_2018_V5_DEADBAND_H
#define VEX_U_2018_V5_DEADBAND_H

#include "afr-vexu-lib/action.h"

namespace AFR::VexU::BaseAction{
    template<typename Read_T, typename Write_T>
    class deadband_action : public action{
        const Read_T _bottom_threshold;
        const Read_T _top_threshold;
        readable* const _value_pointer;
        const Write_T _center_value;
        const Write_T _below_value;
        const Write_T _above_value;

        void update_private(const double& delta_seconds) override;

        public:

        /**
         * Creates a deadband action
         * @param update_period passed to scheduled
         * @param commandable passed to action
         * @param bottom_threshold bottom bound of deadband
         * @param top_threshold top bound of deadband
         * @param value_ptr the pointer to the value to be copied every update
         * @param center_value output value while in deadband
         * @param below_value output value while below deadband
         * @param above_value output value while above deadband
         * @param name error_t value if error encountered
         */
        deadband_action(scheduled_update_t update_period, commandable* commandable, Read_T bottom_threshold,
                        Read_T top_threshold, readable* value_pointer, Write_T center_value,
                        Write_T below_value, Write_T above_value, const std::string& name = nullptr);
    };
    template<typename Read_T, typename Write_T>
    void deadband_action<Read_T, Write_T>::update_private(const double& delta_seconds){
        auto result = std::any_cast<Read_T>(_value_pointer->get_value());
        if(result < _bottom_threshold){
            return commandable_->set_value(_below_value);
        }
        else if(result > _top_threshold){
            return commandable_->set_value(_above_value);
        }
        else {
            return commandable_->set_value(_center_value);
        }
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-non-const-parameter"
    template<typename Read_T, typename Write_T>
    deadband_action<Read_T, Write_T>::deadband_action(scheduled_update_t update_period, commandable* commandable,
                                                      Read_T bottom_threshold, Read_T top_threshold,
                                                      readable* value_pointer, Write_T center_value,
                                                      Write_T below_value, Write_T above_value, const std::string& name)
            : action(update_period, commandable, name), _bottom_threshold(bottom_threshold),
              _top_threshold(top_threshold), _value_pointer(value_pointer), _center_value(center_value),
              _below_value(below_value), _above_value(above_value){}

#pragma clang diagnostic pop

}

#endif 