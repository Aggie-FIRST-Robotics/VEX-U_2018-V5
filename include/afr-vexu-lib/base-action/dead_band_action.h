#ifndef VEX_U_2018_V5_DEADBAND_H
#define VEX_U_2018_V5_DEADBAND_H

#include <cassert>
#include "afr-vexu-lib/base-action/targetable.h"

namespace AFR::VexU::BaseAction{
    template<typename Read_T, typename Write_T>
    class dead_band_action : public targetable<Read_T>{
        Read_T width_;
        Write_T deadband_value_;
        const Write_T _below_value;
        const Write_T _above_value;

        void set_value_private(Read_T value, const double& delta_seconds) override {
            
            if(value < _bottom_threshold){
                deadband_value_ = _below_value;
            }
            else if(value > _top_threshold){
                deadband_value_ = _above_value;
            }
            else {
                deadband_value_ = static_cast<Write_T>((
                        static_cast<Write_T>(value - get_target()+width_/2) * (_above_value - _below_value) /
                        (static_cast<Write_T>(width_)) + _below_value));
            }
        }

        public:
        
        void set_deadband_width(Read_T width){
            width_ = width;
        }

        bool is_in_range(Read_T tolerance){
            return abs(std::any_cast<Read_T>(_value_pointer->get_value()) - (_top_threshold - _bottom_threshold) / 2) <=
                   tolerance;
        }
        
        Write_T get_deadband_value() {
            return deadband_value_;
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
        dead_band_action(scheduled_update_t update_period, Read_T target, 
        Read_T deadband_width, Write_T below_value, 
        Write_T above_value, const std::string& name)
            : targetable<Read_T>(update_period, (top_threshold - bottom_threshold) / 2 + bottom_threshold, target, name), 
              width_(top_threshold), 
              _below_value(below_value),
              _above_value(above_value),
              deadband_value_((above_value-below_value)/2+below_value)
              {}
    };
}

#endif 