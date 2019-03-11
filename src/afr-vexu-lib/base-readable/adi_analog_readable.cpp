#include "afr-vexu-lib/base-readable/adi_analog_readable.h"

namespace AFR::VexU::BaseReadable{
    adi_analog_readable::adi_analog_readable(port_t port, const std::string& name)
            : nameable(name), port_(port){
        claim_adi(port_, name);
        pros::c::adi_port_set_config(port_, pros::E_ADI_DIGITAL_IN);
    }

    int32_t adi_analog_readable::get_analog_value(){
        return pros::c::adi_analog_read(port_);
    }
}
