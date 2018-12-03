#ifndef VEX_U_2018_V5_MOTOR_CURRENT_READABLE_H
#define VEX_U_2018_V5_MOTOR_CURRENT_READABLE_H

#include "main.h"

#include "afr-vexu-lib/readable.h"

namespace AFR::VexU::BaseReadable {
    /**
    * Represents motor current
    */
    class motor_current_readable : public readable {
        pros::Motor prosmotor;
        std::int32_t current;

        /**
         * Overrides scheduled, updates private period
         * @param delta_seconds new update period
         * @return error_t value if error encountered
         */
        error_t update_private(const double &delta_seconds) override;

    public:
        /**
         * Creates a motor current readable
         * @param port smart cable port
         * @param update_period the update period for the readable
         * @param result error_t value if error encountered
         */
        motor_current_readable(const std::uint8_t &port, const scheduled_update_t &update_period, error_t *result);

        /**
         * Returns motor current draw
         * @param result current
         * @return error_t value if error encountered
         */
        error_t get_current(std::int32_t &result);
    };

}
#endif //VEX_U_2018_V5_MOTOR_CURRENT_READABLE_H
