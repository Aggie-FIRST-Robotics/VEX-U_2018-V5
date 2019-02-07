#ifndef VEX_U_2018_V5_ARCADE_DRIVE_ACTION_H
#define VEX_U_2018_V5_ARCADE_DRIVE_ACTION_H

#include "afr-vexu-lib/action.h"

namespace AFR::VexU::Robot::Drive{
    class arcade_drive_action : public action{
        bool is_right;
        pros::controller_analog_e_t right_stick_;
        pros::controller_analog_e_t left_stick_;


        void update_private(const double& delta_seconds) override;

    public:
        arcade_drive_action(const scheduled_update_t& update_period, commandable& commandable,
                            pros::controller_analog_e_t left_stick, pros::controller_analog_e_t right_stick,
                            bool is_right);
    };
}

#endif //VEX_U_2018_V5_ARCADE_DRIVE_ACTION_H
