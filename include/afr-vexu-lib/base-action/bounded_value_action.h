#ifndef VEX_U_2018_V5_BOUNDED_SET_VALUE_ACTION_H
#define VEX_U_2018_V5_BOUNDED_SET_VALUE_ACTION_H

#include "afr-vexu-lib/action.h"

namespace AFR::VexU::BaseAction{
    template<typename Sensor_Read_T, typename Input_Read_T, typename Write_t>
    class bounded_value_action : public action{
        Sensor_Read_T top_val_, bottom_val_;
        Write_t above_max_, below_min_;
        std::function<Write_t(Input_Read_T)> conversion_func_;
        readable* input_, * sensor_;

        void update_private(const double& delta_seconds) override{
            Write_t val = conversion_func_(std::any_cast<Input_Read_T>(input_->get_value()));
            Sensor_Read_T sense_val = std::any_cast<Sensor_Read_T>(sensor_->get_value());
            if(sense_val > top_val_){
                commandable_->set_value(std::min(above_max_, val));
            }
            else if(sense_val < bottom_val_){
                commandable_->set_value(std::max(below_min_, val));
            }
            else{
                commandable_->set_value(val);
            }
        }

    public:
        bounded_value_action(scheduled_update_t update_period, commandable* commandable, Sensor_Read_T top_val,
                             Sensor_Read_T bottom_val, Write_t above_max, Write_t below_min,
                             const std::function<Write_t(Input_Read_T)>& conversion_func, readable* input,
                             readable* sensor, const std::string& name) :
                action(update_period, commandable, name), top_val_(top_val), bottom_val_(bottom_val),
                above_max_(above_max), below_min_(below_min), conversion_func_(conversion_func), input_(input),
                sensor_(sensor){}
    };
}

#endif //VEX_U_2018_V5_BOUNDED_SET_VALUE_ACTION_H
