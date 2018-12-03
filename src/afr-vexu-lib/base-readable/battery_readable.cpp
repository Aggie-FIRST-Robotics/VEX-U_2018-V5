#include "afr-vexu-lib/base-readable/battery_readable.h"

namespace AFR::VexU::BaseReadable {
    error_t battery_readable::update_private(const double &delta_seconds) {
        double temp_capacity = prosbattery.get_capacity();
        AFR_PROS_INTERNAL_CALL(temp_capacity, PROS_ERR_F);
        capacity = temp_capacity;

        double temp_current = prosbattery.get_current();
        AFR_PROS_INTERNAL_CALL(temp_current, PROS_ERR_F);
        current = temp_current;

        double temp_temperature = prosbattery.get_temperature();
        AFR_PROS_INTERNAL_CALL(temp_temperature, PROS_ERR_F);
        temperature = temp_temperature;

        double temp_voltage = prosbattery.get_voltage();
        AFR_PROS_INTERNAL_CALL(temp_voltage, PROS_ERR_F);
        voltage = temp_voltage;

        return SUCCESS;
    }

    battery_readable::battery_readable(const scheduled_update_t &update_period, AFR::VexU::error_t *result)
            : readable(update_period, 0, result),
              capacity(prosbattery.get_capacity()),
              current(prosbattery.get_current()),
              temperature(
                      prosbattery.get_temperature()),
              voltage(prosbattery.get_voltage()) {}


    error_t battery_readable::get_capacity(double &result) {
        result = capacity;
        return SUCCESS;
    }

    error_t battery_readable::get_current(double &result) {
        result = current;
        return SUCCESS;
    }

    error_t battery_readable::get_temperature(double &result) {
        result = temperature;
        return SUCCESS;
    }

    error_t battery_readable::get_voltage(double &result) {
        result = voltage;
        return SUCCESS;
    }
}
