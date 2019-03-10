#ifndef VEX_U_2018_V5_MOTOR_COMMANDABLE_H
#define VEX_U_2018_V5_MOTOR_COMMANDABLE_H

#include "main.h"

#include "afr-lib/commandable.h"

namespace AFR::VexU::BaseCommandable{
    /**
     * Represents a basic motor.
     * <p>
     * Value must be [-12000, 12000] and is in mV.
     * </p>
     */
    class motor_commandable : public commandable<int16_t>{
        port_t port_;

        void set_value_private(int16_t value, double delta_seconds);

    public:
        /**
         * Creates a basic motor commandable
         * @param port v5 port to use
         * @param gearset gearset attached to motor
         * @param reverse should be reversed
         * @param brake_mode what to do when power is 0
         * @param name error_t value if error encountered
         */
        motor_commandable(port_t port, pros::motor_gearset_e_t gearset, bool reverse,
                          pros::motor_brake_mode_e_t brake_mode, const std::string& name);
    };
}

#endif //VEX_U_2018_V5_MOTOR_COMMANDABLE_H
