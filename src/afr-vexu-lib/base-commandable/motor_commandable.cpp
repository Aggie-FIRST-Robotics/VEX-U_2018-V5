#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "afr-vexu-lib/ports_list.h"

namespace AFR::VexU::BaseCommandable{
    void AFR::VexU::BaseCommandable::motor_commandable::set_value_private(int16_t value, double delta_seconds){
        if(value < -12000){
            value = -12000;
        }
        else if(value > 12000){
            value = 12000;
        }
        pros::c::motor_move_voltage(port_, value);
    }

    AFR::VexU::BaseCommandable::motor_commandable::motor_commandable(port_t port, pros::motor_gearset_e_t gearset,
                                                                     bool reverse,
                                                                     pros::motor_brake_mode_e_t brake_mode,
                                                                     const std::string& name)
            : nameable(name), commandable(static_cast<int16_t>(0), name), port_(port){
        claim_smart(port, name);
        pros::c::motor_set_gearing(port, gearset);
        pros::c::motor_set_reversed(port, reverse);
        pros::c::motor_set_brake_mode(port, brake_mode);
    }
}
