#ifndef VEX_U_2018_V5_BOUNDED_SET_VALUE_ACTION_H
#define VEX_U_2018_V5_BOUNDED_SET_VALUE_ACTION_H

#include <functional>
#include "afr-lib/commandable.h"
#include "afr-lib/operation.h"

namespace AFR::VexU::BaseAction{
    template<typename Sensor_Read_T, typename Input_Read_T, typename Write_T>
    class bounded_value_action : public commandable<Input_Read_T>, public operation<Sensor_Read_T> {
        Sensor_Read_T top_val_, bottom_val_;
        Write_T above_max_, below_min_;
        Input_Read_T set_input_value_;
        std::function<Write_T(Input_Read_T)> conversion_func_;

        void set_value_private(Input_Read_T value, double delta_seconds) override {
            set_input_value_ = value;
        }

    public:
        bounded_value_action(const scheduled_update_t update_period,
                                Sensor_Read_T top_val, Sensor_Read_T bottom_val,
                                Write_T above_max, Write_T below_min,
                                const std::function<Write_T(Input_Read_T)>& conversion_func,
                                const std::function<Input_Read_T()>& input,
                                const std::function<Sensor_Read_T()>& sensor,
                                const std::string& name) :
                                nameable(name),
                                commandable<Input_Read_T>(update_period, name),
                                operation<Sensor_Read_T>(sensor, name),
                                top_val_(top_val), bottom_val_(bottom_val),
                                above_max_(above_max), below_min_(below_min),
                                conversion_func_(conversion_func) {
            commandable<Input_Read_T>::set_operation(input, "");
        }

        Write_T get_bounded_value() {
            Write_T val = conversion_func_(set_input_value_);
            Sensor_Read_T sense_val = operation<Sensor_Read_T>::get_function()();
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
    };
}

#endif //VEX_U_2018_V5_BOUNDED_SET_VALUE_ACTION_H
