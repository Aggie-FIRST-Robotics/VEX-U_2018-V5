#include "afr-vexu-lib/base-readable/adi_analog_readable.h"

namespace AFR::VexU::BaseReadable{
    adi_analog_readable::adi_analog_readable(port_t port, scheduled_update_t update_period,
                                             const std::any& initial_value, const std::string& name)
            : readable(update_period, initial_value, name), port_(port){
        claim_adi(port_, name);
        pros::c::adi_port_set_config(port_, pros::E_ADI_DIGITAL_IN);
    }

    void adi_analog_readable::update_private(const double& delta_seconds){
        int32_t temp_val = pros::c::adi_analog_read(port_);
        if(temp_val == PROS_ERR){
            throw std::runtime_error{"Bad pros adi analog value!"};
        }
        readable::value = temp_val;
    }
}
