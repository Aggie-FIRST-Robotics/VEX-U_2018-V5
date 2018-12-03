
#ifndef VEX_U_2018_V51_BATTERY_READABLE_H
#define VEX_U_2018_V51_BATTERY_READABLE_H

#include "main.h"

#include "afr-vexu-lib/readable.h"

namespace AFR::VexU::BaseReadable {
    /**
    * Represents a V5 Battery
    */
    class battery_readable : public readable {
        pros::battery prosbattery;
        double capacity;
        double current;
        double temperature;
        double voltage;

        error_t update_private(const double &delta_seconds) override;

    public:
        battery_readable(const scheduled_update_t &update_period, error_t *result);

        error_t get_capacity(double &result);

        error_t get_current(double &result);

        error_t get_temperature(double &result);

        error_t get_voltage(double &result);
    };

}
#endif //VEX_U_2018_V51_BATTERY_READABLE_H
