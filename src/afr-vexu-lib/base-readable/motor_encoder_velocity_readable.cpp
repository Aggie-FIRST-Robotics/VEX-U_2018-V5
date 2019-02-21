#include "afr-vexu-lib/base-readable/motor_encoder_velocity_readable.h"
#include <queue>

namespace AFR::VexU::BaseReadable{

    void motor_encoder_velocity_readable::update_private(const double& delta_seconds){
        current_distance = pros::c::motor_get_position(port_);
        temp_velocity = (current_distance - old_distance) / delta_seconds;
        old_distance = current_distance;

        velocities.push_back(temp_velocity);
        if(!velocities.empty()){
            while(velocities.size() > max){
                velocities.pop_front();
            }
            double tempsum = 0;
            for(double velocitie : velocities){
                tempsum += velocitie;

            }
            current_velocity = tempsum / velocities.size();
        }
    }

    std::any motor_encoder_velocity_readable::get_value(){
        return current_velocity;
    }

    double motor_encoder_velocity_readable::get_actual_velocity(){
        return current_velocity;
    }

    double motor_encoder_velocity_readable::get_scaled_velocity(){
        return current_velocity * scale_factor;
    }

    motor_encoder_velocity_readable::motor_encoder_velocity_readable(port_t port, double scale_factor,
                                                                     const std::string& name)
            : readable(10, nullptr, name), port_(port), scale_factor(scale_factor){
        current_distance = 0;
        old_distance = 0;
        current_velocity = 0;
        temp_velocity = 0;
    }

}
