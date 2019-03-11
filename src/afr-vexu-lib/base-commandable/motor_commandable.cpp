#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "afr-vexu-lib/ports_list.h"

namespace AFR::VexU::BaseCommandable{
    void motor_commandable::set_value_private(int16_t value, double delta_seconds){
        if(value < -12000){
            value = -12000;
        }
        else if(value > 12000){
            value = 12000;
        }
        pros::c::motor_move_voltage(port_, value);
    }

    motor_commandable::motor_commandable(const scheduled_update_t update_period, port_t port, pros::motor_gearset_e_t gearset,
                                                                     bool reverse,
                                                                     pros::motor_brake_mode_e_t brake_mode,
                                                                     const std::string& name)
            : commandable<int16_t>(update_period, name), nameable(name), port_(port){
        claim_smart(port, name);
        pros::c::motor_set_gearing(port, gearset);
        pros::c::motor_set_reversed(port, reverse);
        pros::c::motor_set_brake_mode(port, brake_mode);
    }
    
    int32_t motor_commandable::get_current() {
        return pros::c::motor_get_current_draw(port_);
    }
    
    double motor_commandable::get_temperature() {
        return pros::c::motor_get_temperature(port_);
    }
}
