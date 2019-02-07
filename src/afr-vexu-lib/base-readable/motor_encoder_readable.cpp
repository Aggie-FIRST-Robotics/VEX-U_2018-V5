#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"

namespace AFR::VexU::BaseReadable{
    void motor_encoder_readable::update_private(const double& delta_seconds){
        value = motor.get_position();
        double temp_velocity = motor.get_actual_velocity();
        AFR_PROS_INTERNAL_CALL(temp_velocity, PROS_ERR_F);
        velocity = temp_velocity;

        double temp_position = motor.get_position();
        AFR_PROS_INTERNAL_CALL(temp_position, PROS_ERR_F);
        position = temp_position;

        return SUCCESS;
    }

    motor_encoder_readable::motor_encoder_readable(const std::uint8_t& port, const pros::motor_gearset_e_t& gearset,
                                                   const bool& reverse, const double& scale_factor,
                                                   const scheduled_update_t& update_period,
                                                   AFR::VexU::error_t* result) : readable(update_period, 0,
                                                                                          <#initializer#>),
                                                                                 motor(port, gearset, reverse,
                                                                                       pros::E_MOTOR_ENCODER_COUNTS),
                                                                                 velocity(0), position(0),
                                                                                 scale_factor(scale_factor){}

    error_t motor_encoder_readable::set_scale_factor(const double& scale_factor){
        this->scale_factor = scale_factor;
        return SUCCESS;
    }

    error_t motor_encoder_readable::get_actual_velocity(double& result){
        result = velocity;
        return SUCCESS;
    }

    error_t motor_encoder_readable::get_scaled_velocity(double& result){
        result = velocity * scale_factor;
        return SUCCESS;
    }

    error_t motor_encoder_readable::get_position(double& result){
        result = position * scale_factor;
        return SUCCESS;
    }

    error_t motor_encoder_readable::get_scaled_position(double& result){
        result = position * scale_factor;
        return SUCCESS;
    }

    error_t motor_encoder_readable::tare_position(){
        AFR_PROS_INTERNAL_CALL(motor.tare_position(), PROS_ERR);
        return SUCCESS;
    }

    error_t motor_encoder_readable::tare_position(const double& position){
        AFR_PROS_INTERNAL_CALL(motor.set_zero_position(position), PROS_ERR);
        return SUCCESS;
    }

    error_t motor_encoder_readable::tare_position_scaled(const double& position){
        AFR_PROS_INTERNAL_CALL(motor.set_zero_position(position / scale_factor), PROS_ERR);
        return SUCCESS;
    }

    std::any motor_encoder_readable::get_value() const{
        throw std::runtime_error("Not Possible");
    }
}
