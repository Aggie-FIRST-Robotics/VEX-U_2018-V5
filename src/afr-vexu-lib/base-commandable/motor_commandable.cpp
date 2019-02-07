#include "afr-vexu-lib/base-commandable/motor_commandable.h"

void AFR::VexU::BaseCommandable::motor_commandable::set_value_private(const std::any& value){
    try{
        AFR_PROS_INTERNAL_CALL(motor.move_velocity(std::any_cast<int16_t>(value)), PROS_ERR);
    }
    catch(std::bad_any_cast& e){
        std::cerr << "1" << std::endl;
        std::cerr << e.what() << std::endl;

        return GENERIC_FAILURE;
    }
    return SUCCESS;
}

void AFR::VexU::BaseCommandable::motor_commandable::check_value_private(const std::any& value){
    if(std::type_index(value.type()) == std::type_index(typeid(int16_t))){
        int16_t real_value = 0;
        try{
            real_value = std::any_cast<int16_t>(value);
        }
        catch(std::bad_any_cast& e){
            std::cerr << "2" << std::endl;
            std::cerr << e.what() << std::endl;

            return GENERIC_FAILURE;
        }
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
                                                                 AFR::VexU::error_t* result) : commandable(0,
                                                                                                           <#initializer#>),
                                                                                               motor(port, gearset,
                                                                                                     reverse){
    if(result != nullptr && *result == SUCCESS){
        *result = motor.set_brake_mode(brake_mode) == PROS_ERR ? PROS_ERROR : SUCCESS;
    }
    else if(result == nullptr){
        motor.set_brake_mode(brake_mode);
    }
}

std::type_index AFR::VexU::BaseCommandable::motor_commandable::get_type() const{
    result = typeid(int16_t);
    return SUCCESS;
}
