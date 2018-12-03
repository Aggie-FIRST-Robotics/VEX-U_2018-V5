#include "afr-vexu-lib/base-readable/motor_current_readable.h"

namespace AFR::VexU::BaseReadable {
    /**
     * Overrides scheduled, updates private variables and period
     * @param delta_seconds new update period
     * @return error_t value if error encountered
     */
    error_t motor_current_readable::update_private(const double &delta_seconds) {
        double temp_current = prosmotor.get_current_draw();
        AFR_PROS_INTERNAL_CALL(temp_current, PROS_ERR_F);
        current = temp_current;

        return SUCCESS;
    }

    /**
     * Creates a motor current readable
     * @param port smart cable port
     * @param update_period the update period for the readable
     * @param result error_t value if error encountered
     */
    motor_current_readable::motor_current_readable(const std::uint8_t &port, const scheduled_update_t &update_period,
                                                   AFR::VexU::error_t *result)
            : readable(update_period, result),
              prosmotor(port),
              current(prosmotor.get_current_draw()) {}

    /**
     * Returns motor current draw
     * @param result current
     * @return error_t value if error encountered
     */
    error_t motor_current_readable::get_current(std::int32_t &result) {
        result = current;
        return SUCCESS;
    }
}
