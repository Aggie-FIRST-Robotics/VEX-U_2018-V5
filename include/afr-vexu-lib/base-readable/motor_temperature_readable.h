#ifndef VEX_U_2018_V5_MOTOR_TEMPERATURE_READABLE_H
#define VEX_U_2018_V5_MOTOR_TEMPERATURE_READABLE_H

#include "main.h"

#include "afr-vexu-lib/readable.h"

namespace AFR::VexU::BaseReadable {
    /**
    * Represents motor temperature
    */
    class motor_temperature_readable : public readable {
        pros::Motor prosmotor;
        double current;

        /**
         * Overrides scheduled, updates private period
         * @param delta_seconds new update period
         * @return error_t value if error encountered
         */
        error_t update_private(const double &delta_seconds) override;

    public:
        /**
         * Creates a motor temperature readable
         * @param port smart cable port
         * @param update_period the update period for the readable
         * @param result error_t value if error encountered
         */
        motor_temperature_readable(const std::uint8_t &port, const scheduled_update_t &update_period, error_t *result)
                : temperature(prosmotor.get_temperature()) {}

        /**
         * Returns motor temperature
         * @param result temperature
         * @return error_t value if error encountered
         */
        error_t get_temperature(double &result);
    };

}
#endif //VEX_U_2018_V5_MOTOR_TEMPERATURE_READABLE_H
