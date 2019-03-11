#include "afr-vexu-lib/base-commandable/adi_digital_commandable.h"
#include "afr-vexu-lib/ports_list.h"

namespace AFR::VexU::BaseCommandable {
    void adi_digital_commandable::set_value_private(bool value, double delta_seconds){
        pros::c::adi_digital_write(port_, value);
    }

    adi_digital_commandable::adi_digital_commandable(const scheduled_update_t period, port_t port, const std::string& name)
            : nameable(name), commandable(period, name), port_(port){
        claim_adi(port, name);
        pros::c::adi_port_set_config(port, pros::E_ADI_DIGITAL_OUT);
    }
}
