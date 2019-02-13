#include "afr-vexu-lib/base-commandable/adi_analog_commandable.h"
#include "afr-vexu-lib/ports_list.h"

namespace AFR::VexU::BaseCommandable{
    void adi_analog_commandable::set_value_private(const std::any& value){
        pros::c::adi_port_set_value(port_, std::any_cast<int32_t>(value));
    }

    void adi_analog_commandable::check_value_private(const std::any& value){
        if(std::type_index(value.type()) == get_type()){
            auto real_value = std::any_cast<int32_t>(value);
            if(real_value < 0 || real_value > 4095){
                throw std::runtime_error{
                        "Bad value for adi_analog_commandable " + get_name() + ": " + std::to_string(real_value)};
            }
        }
        else{
            throw std::runtime_error{"Bad type for adi_analog_commandable " + get_name() + ": " + value.type().name()};
        }
    }

    adi_analog_commandable::adi_analog_commandable(port_t port, const std::string& name) : commandable(0, name),
                                                                                           port_(port){
        claim_adi(port, name);
        pros::c::adi_port_set_config(port, pros::E_ADI_ANALOG_OUT);
    }

    std::type_index adi_analog_commandable::get_type() const{
        return typeid(int32_t);
    }
}
