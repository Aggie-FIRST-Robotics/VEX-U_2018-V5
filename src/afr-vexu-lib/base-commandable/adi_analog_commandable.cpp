#include "afr-vexu-lib/base-commandable/adi_analog_commandable.h"

namespace AFR::VexU::BaseCommandable{
    error_t adi_analog_commandable::set_value_private(const std::any& value){
        AFR_PROS_INTERNAL_CALL(adi_analog_out.set_value(std::any_cast<int32_t>(value)), PROS_ERR);
        return SUCCESS;
    }

    error_t adi_analog_commandable::check_value_private(const std::any& value){
        if(std::type_index(value.type()) == std::type_index(typeid(int32_t))){
            auto real_value = std::any_cast<int32_t>(value);
            if(real_value < 0 || real_value > 4095){
                return INVALID_VALUE;
            }
            return SUCCESS;
        }
        return INVALID_TYPE;
    }

    adi_analog_commandable::adi_analog_commandable(const uint8_t& port, error_t* result) : commandable(0, result),
                                                                                           adi_analog_out(port){}

    error_t adi_analog_commandable::get_type(std::type_index& result) const{
        result = typeid(int32_t);
        return SUCCESS;
    }
}
