#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "afr-vexu-lib/ports_list.h"

void AFR::VexU::BaseCommandable::motor_commandable::set_value_private(const std::any& value){
    if(pros::c::motor_move_voltage(port_, std::any_cast<int16_t>(value)) == PROS_ERR){
        throw std::runtime_error{
                "Error moving motor " + get_name() + " for voltage: " + std::to_string(std::any_cast<int16_t>(value))};
    }
}

void AFR::VexU::BaseCommandable::motor_commandable::check_value_private(const std::any& value){
    if(std::type_index{value.type()} == get_type()){
        auto real_value = std::any_cast<int16_t>(value);
        if(real_value < -12000 || real_value > 12000){
            throw std::runtime_error{
                    "Bad value for motor_commandable " + get_name() + ": " + std::to_string(real_value)};
        }
    }
    else{
        throw std::runtime_error{"Bad type for motor_commandable " + get_name() + ": " + value.type().name()};
    }
}

AFR::VexU::BaseCommandable::motor_commandable::motor_commandable(port_t port, pros::motor_gearset_e_t gearset,
                                                                 bool reverse, pros::motor_brake_mode_e_t brake_mode,
                                                                 const std::string& name)
        : commandable(static_cast<int16_t>(0), name), port_(port){
    std::cout << "COMMANDABLE!" << std::endl;
    claim_smart(port, name);
    pros::c::motor_set_gearing(port, gearset);
    pros::c::motor_set_reversed(port, reverse);
    pros::c::motor_set_brake_mode(port, brake_mode);
}

std::type_index AFR::VexU::BaseCommandable::motor_commandable::get_type() const{
    std::cout << "fshfiah" << std::endl;
    return typeid(int16_t);
}
