#include "robot/cap/intake_action.h"
#include "afr-vexu-lib/base-readable/controller_readable.h"


namespace AFR::VexU::Robot::Cap{
    intake_action::intake_action(const scheduled_update_t& update_period, commandable& commandable,
                                               pros::controller_digital_e_t left, pros::controller_digital_e_t right :
            action(update_period, commandable), is_right(is_right){




}