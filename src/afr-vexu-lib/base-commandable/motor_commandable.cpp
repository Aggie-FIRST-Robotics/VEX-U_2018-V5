#include <afr-vexu-lib/base-commandable/motor_commandable.h>

#include "afr-vexu-lib/defines.h"

AFR::VexU::error_t AFR::VexU::BaseCommandable::motor_commandable::set_value_private(const std::any& value){
    AFR_PROS_INTERNAL_CALL(motor.move_velocity(std::any_cast<int16_t>(value)), PROS_ERR);
    return SUCCESS;
}

AFR::VexU::error_t AFR::VexU::BaseCommandable::motor_commandable::check_value_private(const std::any& value){
    if(value.type() == typeid(int16_t)){
        auto real_value = std::any_cast<int16_t>(value);
        if(real_value < -12000 || real_value > 12000){
            return INVALID_VALUE;
        }
        return SUCCESS;
    }
    return INVALID_TYPE;
}

AFR::VexU::BaseCommandable::motor_commandable::motor_commandable(const std::uint8_t& port,
                                                                 const pros::motor_gearset_e_t& gearset,
                                                                 const bool& reverse,
                                                                 const pros::motor_brake_mode_e_t& brake_mode,
                                                                 AFR::VexU::error_t* result) : commandable(0, result),
                                                                                               motor(port, gearset,
                                                                                                     reverse){
    if(result != nullptr && *result == SUCCESS){
        *result = motor.set_brake_mode(brake_mode) == PROS_ERR ? PROS_ERROR : SUCCESS;
    }
    else if(result == nullptr){
        motor.set_brake_mode(brake_mode);
    }
}

AFR::VexU::error_t AFR::VexU::BaseCommandable::motor_commandable::get_type(std::type_index& result) const{
    result = typeid(int16_t);
    return SUCCESS;
}
