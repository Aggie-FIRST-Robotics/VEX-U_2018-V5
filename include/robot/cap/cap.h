#ifndef VEX_U_2018_V5_CAP_H
#define VEX_U_2018_V5_CAP_H

#include "afr-vexu-lib/subsystem_controller.h"
#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "afr-vexu-lib/base-action/set_value_action.h"
#include "afr-vexu-lib/base-readable/adi_digital_readable.h"
#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"

namespace AFR::VexU::Robot::Cap {
    const scheduled_update_t ARM_LIMIT_SWITCH_UPDATE_PERIOD = 10;
    const scheduled_update_t ELEVATOR_LIMIT_SWITCH_UPDATE_PERIOD = 10;
    const scheduled_update_t ARM_ENCODER_UPDATE_PERIOD = 10;
    const scheduled_update_t ELEVATOR_ENCODER_UPDATE_PERIOD = 10;

    const scheduled_update_t INTAKE_UPDATE_PERIOD = 10;
    const scheduled_update_t INTAKE_HOLD_UPDATE_PERIOD = 10;
    const scheduled_update_t OUTTAKE_UPDATE_PERIOD = 10;
    const scheduled_update_t INTAKE_OUTTAKE_UPDATE_PERIOD = 10;
    const scheduled_update_t ELEVATOR_DOWN_UPDATE_PERIOD = 10;
    const scheduled_update_t ELEVATOR_ZERO_UPDATE_PERIOD = 10;
    const scheduled_update_t ELEVATOR_HIGH_POS_UPDATE_PERIOD = 10;
    const scheduled_update_t ARM_DOWN_UPDATE_PERIOD = 10;
    const scheduled_update_t ARM_STOP_UPDATE_PERIOD = 10;
    const scheduled_update_t ARM_FLIP_POS_UPDATE_PERIOD = 10;
    const scheduled_update_t ARM_ANGLE_POS_UPDATE_PERIOD = 10;
    const scheduled_update_t ARM_LOW_PRIME_POS_UPDATE_PERIOD = 10;
    const scheduled_update_t ARM_LOW_SCORE_POS_UPDATE_PERIOD = 10;
    const scheduled_update_t ARM_HIGH_PRIME_POS_UPDATE_PERIOD = 10;
    const scheduled_update_t ARM_HIGH_SCORE_POS_UPDATE_PERIOD = 10;
    const scheduled_update_t ARM_PID_UPDATE_PERIOD = 10;
    const scheduled_update_t ELEVATOR_PID_UPDATE_PERIOD = 10;

    const scheduled_update_t CAP_SYSTEM_UPDATE_PERIOD = 100;

    const double ARM_FLIP_THRESHOLD = 10;
    const double ARM_ENCODER_LOW_SCORE_THRESHOLD = 50;
    const double ELEVATOR_ENCODER_LOW_SCORE_THRESHOLD = 180;
    const double ARM_ENCODER_HIGH_SCORE_THRESHOLD = 100;
    const double ELEVATOR_ENCODER_HIGH_SCORE_THRESHOLD = 360;
    const scheduled_update_t SCORE_TIME = 500;

    /* const order_t ARM_LIMIT_SWITCH_ORDER = 1;
     const order_t ELEVATOR_LIMIT_SWITCH_ORDER = 1;
     const order_t ARM_ENCODER_ORDER = 1;
     const order_t ELEVATOR_ENCODER_ORDER = 1;*/

    //Subsystem controller
    extern subsystem_controller *cap_subsystem;

    void init();

    void destroy();
}

#endif //VEX_U_2018_V5_CAP_H
