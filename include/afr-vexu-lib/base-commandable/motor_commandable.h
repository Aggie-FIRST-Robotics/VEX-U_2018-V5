#ifndef VEX_U_2018_V5_MOTOR_COMMANDABLE_H
#define VEX_U_2018_V5_MOTOR_COMMANDABLE_H

#include "main.h"

#include "afr-vexu-lib/commandable.h"

namespace AFR::VexU::BaseCommandable{
    /**
     * Represents a basic motor.
     * <p>
     * Value must be [-12000, 12000] and is in mV.
     * </p>
     */
    class motor_commandable : public commandable{
        pros::Motor motor;

        error_t set_value_private(const std::any& value) override;
        error_t check_value_private(const std::any& value) override;

    public:
        /**
         * Creates a basic motor commandable
         * @param port v5 port to use
         * @param gearset gearset attached to motor
         * @param reverse should be reversed
         * @param brake_mode what to do when power is 0
         * @param result error_t value if error encountered
         */
        motor_commandable(const port_t& port, const pros::motor_gearset_e_t& gearset, const bool& reverse,
                          const pros::motor_brake_mode_e_t& brake_mode, error_t* result = nullptr);

        /**
         * Type is int16_t
         * @param result int16_t
         * @return error_t value if error encountered
         */
        error_t get_type(std::type_index& result) const override;
    };
}

#endif //VEX_U_2018_V5_MOTOR_COMMANDABLE_H
