#include "afr-vexu-lib/base-readable/adi_analog_readable.h"

namespace AFR::VexU::BaseReadable{
    adi_analog_readable::adi_analog_readable(port_t port, const std::string& name)
            : readable(0, nullptr, name), port_(port){
        claim_adi(port_, name);
        pros::c::adi_port_set_config(port_, pros::E_ADI_DIGITAL_IN);
    }

    void adi_analog_readable::update_private(const double& delta_seconds){}

    std::any adi_analog_readable::get_value(){
        return pros::c::adi_analog_read(port_);
    }
}
