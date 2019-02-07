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

        error_t update_private(const double& delta_seconds) override;

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
         * @param result error_t value if error encountered
         */         
            deadband_action(const scheduled_update_t& update_period, commandable& commandable, const Read_T& bottom_threshold,
                            const Read_T& top_threshold, readable* value_pointer, const Write_T& center_value,
                            const Write_T& below_value, const Write_T& above_value, error_t* result = nullptr);                       
    };
    template<typename Read_T, typename Write_T>
    error_t deadband_action<Read_T, Write_T>::update_private(const double& delta_seconds){
        std::any result{};
        AFR_VEXU_INTERNAL_CALL(_value_pointer->get_value(result))
        if(std::any_cast<Read_T>(result) < _bottom_threshold){
            return commandable_.set_value(_below_value);
        }
        else if(std::any_cast<Read_T>(result) > _top_threshold){
            return commandable_.set_value(_above_value);
        }
        else {
            return commandable_.set_value(_center_value);
        }
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-non-const-parameter"
    template<typename Read_T, typename Write_T>
    deadband_action<Read_T, Write_T>::deadband_action(const scheduled_update_t& update_period, commandable& commandable, const Read_T& bottom_threshold,
                                                      const Read_T& top_threshold, readable* const value_pointer,
                                                      const Write_T& center_value,
                                                      const Write_T& below_value, const Write_T& above_value,
                                                      error_t* result) :
                                          action(update_period, commandable, result),
                                          _bottom_threshold(bottom_threshold),
                                          _top_threshold(top_threshold),
                                          _value_pointer(value_pointer),
                                          _center_value(center_value),
                                          _below_value(below_value),
                                          _above_value(above_value){}

#pragma clang diagnostic pop

}

#endif 