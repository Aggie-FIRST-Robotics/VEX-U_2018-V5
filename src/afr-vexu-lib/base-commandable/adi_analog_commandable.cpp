#include "afr-vexu-lib/base-commandable/adi_analog_commandable.h"
#include "afr-vexu-lib/ports_list.h"

namespace AFR::VexU::BaseCommandable{
    void adi_analog_commandable::set_value_private(int32_t value, double delta_seconds){
        pros::c::adi_port_set_value(port_, value);
    }

    adi_analog_commandable::adi_analog_commandable(port_t port, const std::string& name)
            : nameable(name), commandable(0, name), port_(port){
        claim_adi(port, name);
        pros::c::adi_port_set_config(port, pros::E_ADI_ANALOG_OUT);
    }
}
