#include "afr-vexu-lib/base-readable/battery_readable.h"

namespace AFR::VexU::BaseReadable {
    /**
     * Overrides scheduled, updates private variables and period
     * @param delta_seconds new update period
     * @return error_t value if error encountered
     */
    error_t battery_readable::update_private(const double &delta_seconds) {
        double temp_capacity = pros::battery::get_capacity();
        AFR_PROS_INTERNAL_CALL(temp_capacity, PROS_ERR_F);
        capacity = temp_capacity;

        double temp_current = pros::battery::get_current();
        AFR_PROS_INTERNAL_CALL(temp_current, PROS_ERR_F);
        current = temp_current;

        double temp_temperature = pros::battery::get_temperature();
        AFR_PROS_INTERNAL_CALL(temp_temperature, PROS_ERR_F);
        temperature = temp_temperature;

        double temp_voltage = pros::battery::get_voltage();
        AFR_PROS_INTERNAL_CALL(temp_voltage, PROS_ERR_F);
        voltage = temp_voltage;

        return SUCCESS;
    }

    /**
     * Creates a battery readable
     * @param update_period the update period for the readable
     * @param result error_t value if error encountered
     */
    battery_readable::battery_readable(const scheduled_update_t &update_period, AFR::VexU::error_t *result)
            : readable(update_period, 0, result),
              capacity(pros::battery::get_capacity()),
              current(pros::battery::get_current()),
              temperature(
                      pros::battery::get_temperature()),
              voltage(pros::battery::get_voltage()) {}

    /**
     * Returns battery capacity
     * @param result battery capacity
     * @return error_t value if error encountered
     */
    error_t battery_readable::get_capacity(double &result) {
        result = capacity;
        return SUCCESS;
    }

    /**
     * Returns battery current
     * @param result battery current
     * @return error_t value if error encountered
     */
    error_t battery_readable::get_current(double &result) {
        result = current;
        return SUCCESS;
    }

    /**
     * Returns battery temperature
     * @param result battery temperature
     * @return error_t value if error encountered
     */
    error_t battery_readable::get_temperature(double &result) {
        result = temperature;
        return SUCCESS;
    }

    /**
     * Returns battery voltage
     * @param result battery voltage
     * @return error_t value if error encountered
     */
    error_t battery_readable::get_voltage(double &result) {
        result = voltage;
        return SUCCESS;
    }
}
