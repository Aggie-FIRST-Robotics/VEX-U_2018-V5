#include "robot/drive/arcade_drive_action.h"

namespace AFR::VexU::Robot::Drive{
    arcade_drive_action::arcade_drive_action(const AFR::VexU::scheduled_update_t& update_period,
                                             AFR::VexU::commandable& commandable,
                                             pros::controller_analog_e_t left_stick,
                                             pros::controller_analog_e_t right_stick,
                                             bool is_right) :
            action(update_period, commandable), is_right(is_right){}

    error_t arcade_drive_action::update_private(const double& delta_seconds){

    }
}
