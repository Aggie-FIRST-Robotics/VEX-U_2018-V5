#include "afr-vexu-lib/base-readable/motor_encoder_velocity_readable.h"
#include <queue>

namespace AFR::VexU::BaseReadable {
    double current_distance = 0;
    double old_distance = 0;
    double current_velocity = 0;
    double temp_velocity = 0;
    std::queue<int> velocities;
    constexpr int max = 0;

    void motor_encoder_velocity_readable::update_private(const double &delta_seconds) {
        //   std::cout<<"HELLO IS ANYONE HOME"<< temp_velocity<<std::endl;


        current_distance = pros::c::motor_get_position(port_);
        //  std::cout<<"new"<<current_distance<<"old"<<old_distance<<std::endl;
        temp_velocity = (static_cast<double>(current_distance - old_distance) / static_cast<double>(delta_seconds));
        old_distance = pros::c::motor_get_position(port_);
        std::cout << "Temp Velocity" << temp_velocity << std::endl;

        if (velocities.size() > 0) {
            velocities.push(temp_velocity);
            if (velocities.size() > max) {
                velocities.pop();
            }
            double tempsum = 0;
            for (int x = 0; x < velocities.size(); x++) {
                tempsum += temp_velocity;
                //std::cout<<"haha"<<tempsum<<std::endl;

            }
            current_velocity = tempsum / velocities.size();

        } else {
            velocities.push(temp_velocity);
            current_velocity = 0;
        }

    }

    std::any motor_encoder_velocity_readable::get_value() {
        return current_velocity;


    }

    double motor_encoder_velocity_readable::get_actual_velocity() {
        return current_velocity;
    }

    double motor_encoder_velocity_readable::get_scaled_velocity() {
        return current_velocity * scale_factor;
    }

    motor_encoder_velocity_readable::motor_encoder_velocity_readable(port_t port, double scale_factor,
                                                                     const std::string &name)
            : readable(100, nullptr, name), port_(port), scale_factor(scale_factor) {}

}
