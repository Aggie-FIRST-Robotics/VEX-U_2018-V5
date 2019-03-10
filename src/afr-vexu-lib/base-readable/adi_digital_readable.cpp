#include "afr-vexu-lib/base-readable/adi_digital_readable.h"
#include "afr-lib/ports_list.h"

namespace AFR::VexU::BaseReadable{
    adi_digital_readable::adi_digital_readable(port_t port, const std::string& name)
            : nameable(name), port_(port){
        claim_adi(port_, name);
        pros::c::adi_port_set_config(port_, pros::E_ADI_DIGITAL_IN);
    }

    std::any adi_digital_readable::get_value(){
        return is_pressed();
    }

    bool adi_digital_readable::is_pressed(){
        return pros::c::adi_digital_read(port_) == 1;
    }
}
