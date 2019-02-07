#ifndef VEX_U_2018_V51_BATTERY_READABLE_H
#define VEX_U_2018_V51_BATTERY_READABLE_H

#include "main.h"

#include "afr-vexu-lib/readable.h"

namespace AFR::VexU::BaseReadable {
    class battery_capacity_readable : public readable{
        void update_private(const double& delta_seconds) override;

    public:
        battery_capacity_readable();

        std::any get_value() override;
    };

    class battery_current_readable : public readable{
        void update_private(const double& delta_seconds) override;

    public:
        battery_current_readable();

        std::any get_value() override;
    };

    class battery_temperature_readable : public readable{
        void update_private(const double& delta_seconds) override;

    public:
        battery_temperature_readable();

        std::any get_value() override;
    };

    class battery_voltage_readable : public readable{
        void update_private(const double& delta_seconds) override;

    public:
        battery_voltage_readable();

        std::any get_value() override;
    };

    extern battery_capacity_readable* battery_capacity;
    extern battery_current_readable* battery_current;
    extern battery_temperature_readable* battery_temperature;
    extern battery_voltage_readable* battery_voltage;

    void init_battery();
    void destroy_battery();
}
#endif //VEX_U_2018_V51_BATTERY_READABLE_H
