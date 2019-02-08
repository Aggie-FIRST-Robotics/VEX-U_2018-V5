#include "afr-vexu-lib/base-readable/battery_readable.h"

namespace AFR::VexU::BaseReadable {
    battery_readable* battery_capacity = nullptr;
    battery_current_readable* battery_current = nullptr;
    battery_temperature_readable* battery_temperature = nullptr;
    battery_voltage_readable* battery_voltage = nullptr;

    void battery_readable::update_private(const double& delta_seconds){}

    battery_readable::battery_readable()
            : readable(0, nullptr, "battery_capacity"){}

    std::any battery_readable::get_value(){
        return pros::c::battery_get_capacity();
    }

    void battery_current_readable::update_private(const double& delta_seconds){}

    battery_current_readable::battery_current_readable() : readable(0, nullptr, "battery_current"){}

    std::any battery_current_readable::get_value(){
        return pros::c::battery_get_current();
    }

    void battery_temperature_readable::update_private(const double& delta_seconds){}

    battery_temperature_readable::battery_temperature_readable() : readable(0, nullptr, "battery_temperature"){}

    std::any battery_temperature_readable::get_value(){
        return pros::c::battery_get_temperature();
    }

    void battery_voltage_readable::update_private(const double& delta_seconds){}

    battery_voltage_readable::battery_voltage_readable() : readable(0, nullptr, "battery_voltage"){}

    std::any battery_voltage_readable::get_value(){
        return pros::c::battery_get_voltage();
    }

    void init_battery(){
        battery_capacity = new battery_readable{};
        battery_current = new battery_current_readable{};
        battery_temperature = new battery_temperature_readable{};
        battery_voltage = new battery_voltage_readable{};
    }

    void destroy_battery(){
        delete (battery_capacity);
        delete (battery_current);
        delete (battery_temperature);
        delete (battery_voltage);
    }
}
