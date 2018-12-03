#include "afr-vexu-lib/base-readable/motor_temperature_readable.h"

namespace AFR::VexU::BaseReadable {
    /**
     * Overrides scheduled, updates private variables and period
     * @param delta_seconds new update period
     * @return error_t value if error encountered
     */
    error_t motor_temperature_readable::update_private(const double &delta_seconds) {
        double temp_temperature = prosmotor.get_temperature();
        AFR_PROS_INTERNAL_CALL(temp_temperature, PROS_ERR_F);
        temperature = temp_temperature;

        return SUCCESS;
    }

    /**
     * Creates a motor temperature readable
     * @param port smart cable port
     * @param update_period the update period for the readable
     * @param result error_t value if error encountered
     */
    motor_temperature_readable::motor_temperature_readable(const std::uint8_t &port,
                                                           const scheduled_update_t &update_period,
                                                           AFR::VexU::error_t *result)
            : readable(update_period, 0, result),
              prosmotor(port),
              temperature(prosmotor.get_temperature()) {}

    /**
     * Returns motor temperature
     * @param result temperature
     * @return error_t value if error encountered
     */
    error_t motor_temperature_readable::get_temperature(double &result) {
        result = temperature;
        return SUCCESS;
    }
}
