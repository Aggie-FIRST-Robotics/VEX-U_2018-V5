#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"

namespace AFR::VexU::BaseReadable{

    void motor_encoder_readable::set_scale_factor(double scale_factor){
        this->scale_factor = scale_factor;
    }

    double motor_encoder_readable::get_actual_velocity(){
        return pros::c::motor_get_actual_velocity(port_);
    }

    double motor_encoder_readable::get_scaled_velocity(){
        return get_actual_velocity() * scale_factor;
    }

    double motor_encoder_readable::get_position(){
        return pros::c::motor_get_position(port_);
    }

    double motor_encoder_readable::get_scaled_position(){
        return get_position() * scale_factor;
    }

    void motor_encoder_readable::tare_position(){
        pros::c::motor_tare_position(port_);
    }

    void motor_encoder_readable::tare_position(double position){
        pros::c::motor_set_zero_position(port_, position);
    }

    void motor_encoder_readable::tare_position_scaled(double position){
        tare_position(position / scale_factor);
    }

    motor_encoder_readable::motor_encoder_readable(port_t port, double scale_factor, const std::string& name)
            : nameable(name), port_(port), scale_factor(scale_factor){}

}
