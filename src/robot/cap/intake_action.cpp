#include "robot/cap/intake_action.h"
#include "afr-vexu-lib/base-readable/controller_readable.h"


namespace AFR::VexU::Robot::Cap{
    intake_action::intake_action(const scheduled_update_t& update_period, commandable& commandable,
                                               pros::controller_digital_e_t left, pros::controller_digital_e_t right) :
            action(update_period, commandable){

left_=left;
right_=right;

    }


void intake_action::update_private(const double& delta_seconds){
        bool leftval;
        bool rightval;

        AFR_VEXU_INTERNAL_CALL(BaseReadable::Controller::driver_controller->digital_is_pressed(right_, rightval));
        AFR_VEXU_INTERNAL_CALL(BaseReadable::Controller::driver_controller->digital_is_pressed(left_, leftval));
        if(leftval){
            AFR_VEXU_INTERNAL_CALL(commandable_.set_value(-6000));

        }
        else if(rightval){
            AFR_VEXU_INTERNAL_CALL(commandable_.set_value(6000))
        }
        else{
            AFR_VEXU_INTERNAL_CALL(commandable_.set_value(0));
        }


    }
    return SUCCESS;



}