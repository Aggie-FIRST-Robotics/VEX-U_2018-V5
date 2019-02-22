#ifndef VEX_U_2018_V5_DEADBAND_H
#define VEX_U_2018_V5_DEADBAND_H

#include <cassert>
#include "afr-vexu-lib/action.h"
#include "afr-vexu-lib/readable.h"
#include "afr-vexu-lib/base-action/targetable.h"

namespace AFR::VexU::BaseAction{
    template<typename Read_T, typename Write_T>
    class dead_band_action : public targetable<Read_T>{
        Read_T _bottom_threshold;
        Read_T _top_threshold;
        readable* const _value_pointer;
        const Write_T _below_value;
        const Write_T _above_value;

        void update_private(const double& delta_seconds) override;

        public:

        void set_target(Read_T target){
            Read_T diff = target - ((_top_threshold - _bottom_threshold) / 2 + _bottom_threshold);
            _bottom_threshold += diff;
            _top_threshold += diff;
        }

        bool is_in_range(Read_T tolerance){
            return abs(std::any_cast<Read_T>(_value_pointer->get_value()) - (_top_threshold - _bottom_threshold) / 2) <=
                   tolerance;
        }
        /**
         * Creates a deadband action
         * @param update_period passed to scheduled
         * @param commandable passed to action
         * @param bottom_threshold bottom bound of deadband
         * @param top_threshold top bound of deadband
         * @param value_ptr the pointer to the value to be copied every update
         * @param below_value output value while below deadband
         * @param above_value output value while above deadband
         * @param name error_t value if error encountered
         */
        dead_band_action(scheduled_update_t update_period, commandable* commandable, Read_T bottom_threshold,
                         Read_T top_threshold, readable* value_pointer, Write_T below_value, Write_T above_value, 
                         const std::string& name);
    };
    template<typename Read_T, typename Write_T>
    void dead_band_action<Read_T, Write_T>::update_private(const double& delta_seconds){
        auto result = std::any_cast<Read_T>(_value_pointer->get_value());
        if(result < _bottom_threshold){
            return action::commandable_->set_value(_below_value);
        }
        else if(result > _top_threshold){
            return action::commandable_->set_value(_above_value);
        }
        else {
//            assert(typeid(static_cast<Write_T>(result-_bottom_threshold) * (_above_value-_below_value)/static_cast<Write_T>(_top_threshold-_bottom_threshold) + _below_value) !=
//                           typeid(Write_T));
            return action::commandable_->set_value(static_cast<Write_T>((
                    static_cast<Write_T>(result - _bottom_threshold) * (_above_value - _below_value) /
                    (static_cast<Write_T>(_top_threshold - _bottom_threshold)) + _below_value)));
        }
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-non-const-parameter"
    template<typename Read_T, typename Write_T>
    dead_band_action<Read_T, Write_T>::dead_band_action(scheduled_update_t update_period, commandable* commandable,
                                                        Read_T bottom_threshold, Read_T top_threshold,
                                                        readable* value_pointer, Write_T below_value, 
                                                        Write_T above_value, const std::string& name)
            : targetable<Read_T>(update_period, commandable, (top_threshold - bottom_threshold) / 2 + bottom_threshold,
                                 name), _bottom_threshold(bottom_threshold),
              _top_threshold(top_threshold), _value_pointer(value_pointer),
              _below_value(below_value), _above_value(above_value){}

#pragma clang diagnostic pop

}

#endif 