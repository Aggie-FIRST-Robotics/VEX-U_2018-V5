#include "afr-vexu-lib/base-readable/adi_digital_readable.h"
#include "afr-vexu-lib/ports_list.h"

namespace AFR::VexU::BaseReadable{
    void adi_digital_readable::update_private(const double& delta_seconds){
        int32_t temp_val = pros::c::adi_digital_read(port_);
        if(temp_val == PROS_ERR){
            throw std::runtime_error{"Bad pros adi digital value!"};
        }
        readable::value = static_cast<bool>(temp_val);
    }

    adi_digital_readable::adi_digital_readable(port_t port, scheduled_update_t update_period, bool initial_value,
                                               const std::string& name)
            : readable(update_period, initial_value, name), port_(port){
        claim_adi(port_, name);
        pros::c::adi_port_set_config(port_, pros::E_ADI_DIGITAL_IN);
    }
}
