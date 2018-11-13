#ifndef VEX_U_2018_V5_MOTOR_COMMANDABLE_H
#define VEX_U_2018_V5_MOTOR_COMMANDABLE_H

#include "main.h"

#include "afr-vexu-lib/commandable.h"

namespace AFR::VexU::BaseCommandable{
    class motor_commandable : public commandable{
        pros::Motor motor;

        error_t set_value_private(const std::any& value) override;
        error_t check_value_private(const std::any& value) override;

    public:
        motor_commandable(const std::uint8_t& port, const pros::motor_gearset_e_t& gearset, const bool& reverse,
                          const pros::motor_brake_mode_e_t& brake_mode, error_t* result);

        error_t get_type(std::type_index& result) const override;
    };
}

#endif //VEX_U_2018_V5_MOTOR_COMMANDABLE_H
