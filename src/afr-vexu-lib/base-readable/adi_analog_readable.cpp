

#include "afr-vexu-lib/base-readable/adi_analog_readable.h"


AFR::VexU::BaseReadable::adi_analog_readable::adi_analog_readable(const std::uint8_t &port,
                                                                  const scheduled_update_t &update_period,
                                                                  const std::any &initial_value, error_t *result)
        : readable(update_period, initial_value, result), prosanalog(port) {}

AFR::VexU::error_t AFR::VexU::BaseReadable::adi_analog_readable::update_private(const double &delta_seconds) {
    int32_t temp_val = prosanalog.get_value();
    AFR_PROS_INTERNAL_CALL(temp_val, PROS_ERR);
    readable::value = temp_val;
    return SUCCESS;
}

