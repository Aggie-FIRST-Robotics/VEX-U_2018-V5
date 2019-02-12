
#include <afr-vexu-lib/base-readable/motor_temperature_readable.h>

#include "afr-vexu-lib/base-readable/motor_temperature_readable.h"

namespace AFR::VexU::BaseReadable {
    void motor_temperature_readable::update_private(const double& delta_seconds){}

    motor_temperature_readable::motor_temperature_readable(port_t port, const std::string& name)
            : readable(0, nullptr, name),
              port_(port){}

    std::any motor_temperature_readable::get_value(){
        return get_temperature();
    }

    double motor_temperature_readable::get_temperature() const{
        return pros::c::motor_get_temperature(port_);
    }
}
