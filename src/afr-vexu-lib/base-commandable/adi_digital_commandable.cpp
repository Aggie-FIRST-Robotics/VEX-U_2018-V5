#include "afr-vexu-lib/base-commandable/adi_digital_commandable.h"
#include "afr-lib/ports_list.h"

namespace AFR::VexU::BaseCommandable {
    void adi_digital_commandable::set_value_private(const std::any& value){
        pros::c::adi_digital_write(port_, std::any_cast<bool>(value));
    }

    void adi_digital_commandable::check_value_private(const std::any& value){
        if(std::type_index{value.type()} != get_type()){
            throw std::runtime_error{"Bad type for adi_digital_commandable " + get_name() + ": " + value.type().name()};
        }
    }

    adi_digital_commandable::adi_digital_commandable(port_t port, const std::string& name)
            : commandable(0, name), port_(port){
        claim_adi(port, name);
        pros::c::adi_port_set_config(port, pros::E_ADI_DIGITAL_OUT);
    }

    std::type_index adi_digital_commandable::get_type() const{
        return typeid(bool);
    }
}
