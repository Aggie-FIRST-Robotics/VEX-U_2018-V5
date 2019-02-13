#include "afr-vexu-lib/base-readable/motor_current_readable.h"

namespace AFR::VexU::BaseReadable {
    /**
     * Overrides scheduled, updates private variables and period
     * @param delta_seconds new update period
     * @return error_t value if error encountered
     */
    void motor_current_readable::update_private(const double& delta_seconds){}

    /**
     * Creates a motor current readable
     * @param port smart cable port
     * @param update_period the update period for the readable
     * @param name error_t value if error encountered
     */
    motor_current_readable::motor_current_readable(port_t port, const std::string& name)
            : readable(0, nullptr, name), port_(port){}

    /**
     * Returns motor current draw
     * @param result current
     * @return error_t value if error encountered
     */
    std::any motor_current_readable::get_value(){
        return get_current();
    }

    int32_t motor_current_readable::get_current() const{
        return pros::c::motor_get_current_draw(port_);
    }
}
