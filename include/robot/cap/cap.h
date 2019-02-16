#ifndef VEX_U_2018_V5_CAP_H
#define VEX_U_2018_V5_CAP_H

#include "afr-vexu-lib/subsystem_controller.h"
#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "afr-vexu-lib/base-action/set_value_action.h"
#include "afr-vexu-lib/base-readable/adi_digital_readable.h"
#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"

namespace AFR::VexU::Robot::Cap {
    const scheduled_update_t INTAKE_UPDATE_PERIOD = 10;
    const scheduled_update_t INTAKE_HOLD_UPDATE_PERIOD = 10;
    const scheduled_update_t OUTTAKE_UPDATE_PERIOD = 10;
    const scheduled_update_t INTAKE_OUTTAKE_UPDATE_PERIOD = 10;
    const scheduled_update_t ELEVATOR_DOWN_UPDATE_PERIOD = 10;
    const scheduled_update_t ARM_DOWN_UPDATE_PERIOD = 10;
    const scheduled_update_t ARM_STOP_UPDATE_PERIOD = 10;
    const scheduled_update_t ARM_PID_UPDATE_PERIOD = 10;
    const scheduled_update_t ELEVATOR_PID_UPDATE_PERIOD = 10;

    const scheduled_update_t CAP_SYSTEM_UPDATE_PERIOD = 100;

    const scheduled_update_t LEFT_DOWN_TIME = 100;

    const double ARM_FLIP_TARGET = 100;

    const double ARM_ANGLE_TARGET = 200;

    const double ELEVATOR_LOW_PRIME_TARGET = 0;
    const double ARM_LOW_PRIME_TARGET = 400;

    const double ELEVATOR_LOW_MOVE_TARGET = 0;
    const double ELEVATOR_LOW_SCORE_LOWER = -50;
    const double ELEVATOR_LOW_SCORE_UPPER = 50;
    const double ARM_LOW_MOVE_TARGET = 500;
    const double ARM_LOW_SCORE_LOWER = 450;
    const double ARM_LOW_SCORE_UPPER = 550;

    const double ELEVATOR_LOW_SCORE_TARGET = 0;
    const double ARM_LOW_SCORE_TARGET = 600;

    const double ELEVATOR_HIGH_PRIME_TARGET = 300;
    const double ARM_HIGH_PRIME_TARGET = 700;

    const double ELEVATOR_HIGH_MOVE_TARGET = 400;
    const double ELEVATOR_HIGH_SCORE_LOWER = 350;
    const double ELEVATOR_HIGH_SCORE_UPPER = 450;
    const double ARM_HIGH_MOVE_TARGET = 800;
    const double ARM_HIGH_SCORE_LOWER = 750;
    const double ARM_HIGH_SCORE_UPPER = 850;

    const double ELEVATOR_HIGH_SCORE_TARGET = 500;
    const double ARM_HIGH_SCORE_TARGET = 900;

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
