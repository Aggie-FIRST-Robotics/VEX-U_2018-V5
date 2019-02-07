#include "robot/drive/arcade_drive_action.h"
#include "afr-vexu-lib/base-readable/controller_readable.h"

namespace AFR::VexU::Robot::Drive{
    arcade_drive_action::arcade_drive_action(const AFR::VexU::scheduled_update_t& update_period,
                                             AFR::VexU::commandable& commandable,
                                             pros::controller_analog_e_t left_stick,
                                             pros::controller_analog_e_t right_stick,
                                             bool is_right) :
            action(update_period, commandable), is_right(is_right){
        right_stick_=right_stick;
        left_stick_=left_stick;
    }

    error_t arcade_drive_action::update_private(const double& delta_seconds){
        int32_t right_val;
        int32_t left_val;
        AFR_VEXU_INTERNAL_CALL(BaseReadable::Controller::driver_controller->get_analog_value(right_stick_, right_val));
        AFR_VEXU_INTERNAL_CALL(BaseReadable::Controller::driver_controller->get_analog_value(left_stick_, left_val));
        if(is_right){

            AFR_VEXU_INTERNAL_CALL(commandable_.set_value(int16_t(left_val - right_val)));
        }
        else{
            AFR_VEXU_INTERNAL_CALL(commandable_.set_value(int16_t(right_val - left_val)));
        }
        return SUCCESS;
    }



}
