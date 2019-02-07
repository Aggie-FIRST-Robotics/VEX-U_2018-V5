#ifndef VEX_U_2018_V51_BATTERY_READABLE_H
#define VEX_U_2018_V51_BATTERY_READABLE_H

#include "main.h"

#include "afr-vexu-lib/readable.h"

namespace AFR::VexU::BaseReadable {
    /**
    * Represents a V5 Battery
    */
    class battery_readable : public readable {
        double capacity;
        double current;
        double temperature;
        double voltage;

        /**
         * Overrides scheduled, updates private period
         * @param delta_seconds new update period
         * @return error_t value if error encountered
         */
        void update_private(const double& delta_seconds) override;

    public:
        /**
         * Creates a battery readable
         * @param update_period the update period for the readable
         * @param result error_t value if error encountered
         */
        battery_readable(const scheduled_update_t &update_period, error_t *result);

        /**
         * Returns battery capacity
         * @param result battery capacity
         * @return error_t value if error encountered
         */
        error_t get_capacity(double &result);

        /**
         * Returns battery current
         * @param result battery current
         * @return error_t value if error encountered
         */
        error_t get_current(double &result);

        /**
         * Returns battery temperature
         * @param result battery temperature
         * @return error_t value if error encountered
         */
        error_t get_temperature(double &result);

        /**
         * Returns battery voltage
         * @param result battery voltage
         * @return error_t value if error encountered
         */
        error_t get_voltage(double &result);
    };

}
#endif //VEX_U_2018_V51_BATTERY_READABLE_H
