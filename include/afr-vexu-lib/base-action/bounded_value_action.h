#ifndef VEX_U_2018_V5_BOUNDED_SET_VALUE_ACTION_H
#define VEX_U_2018_V5_BOUNDED_SET_VALUE_ACTION_H

#include <functional>
#include "afr-lib/commandable.h"

namespace AFR::VexU::BaseAction{
    template<typename Sensor_Read_T, typename Input_Read_T, typename Write_T>
    class bounded_value_action : commandable<Input_Read_T> {
        Sensor_Read_T top_val_, bottom_val_;
        Write_T above_max_, below_min_;
        Input_Read_T set_input_value_
        std::function<Write_T(Input_Read_T)> conversion_func_;
        std::function<Input_Read_T()> input_;
        std::function<Sensor_Read_T()> sensor_;

        void set_value_private(Input_Read_T value, const double& delta_seconds) override {
            set_input_value_ = value;
        }

        Write_T check_bounds() {
            Write_T val = conversion_func_(input_());
            Sensor_Read_T sense_val = sensor_();
            if(sense_val > top_val_){
                return std::min(above_max_, val);
            }
            else if(sense_val < bottom_val_){
                return std::max(below_min_, val);
            }
            else{
                return val;
            }
        }

    public:
        bounded_value_action(const scheduled_update_t& update_period, Sensor_Read_T top_val,
                             Sensor_Read_T bottom_val, Write_T above_max, Write_T below_min,
                             const std::function<Write_T(Input_Read_T)>& conversion_func,
                             const std::function<Input_Read_T>& input,
                             const std::function<Sensor_Read_T>& sensor, const std::string& name) :
                commandable<Write_T>(update_period, name), top_val_(top_val), bottom_val_(bottom_val),
                above_max_(above_max), below_min_(below_min), conversion_func_(conversion_func), input_(input),
                sensor_(sensor) {}
    };
}

#endif //VEX_U_2018_V5_BOUNDED_SET_VALUE_ACTION_H
