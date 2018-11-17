//
// Created by Kyle on 11/16/2018.
//

#include "afr-vexu-lib/base-readable/adi_digital_readable.h"
#include "afr-vexu-lib/defines.h"

AFR::VexU::error_t AFR::VexU::BaseReadable::adi_digital_readable::update_private(const double& delta_seconds){
    int32_t temp_val = digital.get_value();
    AFR_PROS_INTERNAL_CALL(temp_val, PROS_ERR);
    if(temp_val == 1) readable::value = true;
    else if(temp_val == 0) readable::value = false;
    return SUCCESS;
}

AFR::VexU::BaseReadable::adi_digital_readable::adi_digital_readable(const scheduled_update_t& update_period,
                                                                    const std::uint8_t& port,
                                                                    AFR::VexU::error_t* result)
                                                                    : readable(update_period, 0, result),
                                                                      digital(port) {}