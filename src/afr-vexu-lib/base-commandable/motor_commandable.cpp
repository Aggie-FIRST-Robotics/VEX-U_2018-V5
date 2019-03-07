#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "afr-lib/ports_list.h"

void AFR::VexU::BaseCommandable::motor_commandable::set_value_private(const std::any& value){
    auto val = std::any_cast<int16_t>(value);
    if(val < -12000){
        val = -12000;
    }
    else if(val > 12000){
        val = 12000;
    }
    pros::c::motor_move_voltage(port_, val);
}

void AFR::VexU::BaseCommandable::motor_commandable::check_value_private(const std::any& value){
    if(std::type_index{value.type()} == get_type()){
//        auto real_value = std::any_cast<int16_t>(value);
//        if(real_value < -12000 || real_value > 12000){
//            throw std::runtime_error{
//                    "Bad value for motor_commandable " + get_name() + ": " + std::to_string(real_value)};
//        }
    }
    else{
        throw std::runtime_error{"Bad type for motor_commandable " + get_name() + ": " + value.type().name()};
    }
}

AFR::VexU::BaseCommandable::motor_commandable::motor_commandable(port_t port, pros::motor_gearset_e_t gearset,
                                                                 bool reverse, pros::motor_brake_mode_e_t brake_mode,
                                                                 const std::string& name)
        : commandable(static_cast<int16_t>(0), name), port_(port){
    claim_smart(port, name);
    pros::c::motor_set_gearing(port, gearset);
    pros::c::motor_set_reversed(port, reverse);
    pros::c::motor_set_brake_mode(port, brake_mode);
}

std::type_index AFR::VexU::BaseCommandable::motor_commandable::get_type() const{
    return typeid(int16_t);
}
