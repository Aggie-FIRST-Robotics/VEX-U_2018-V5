#ifndef VEX_U_2018_V5_CAP_H
#define VEX_U_2018_V5_CAP_H

#include "afr-vexu-lib/subsystem_controller.h"
#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "afr-vexu-lib/base-action/set_value_action.h"
#include "afr-vexu-lib/base-readable/adi_digital_readable.h"
#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"
#include "afr-vexu-lib/base-commandable/multi_motor_commandable.h"

namespace AFR::VexU::Robot::Cap {
//    const scheduled_update_t INTAKE_UPDATE_PERIOD = 10;
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

    const double ARM_FLIP_TARGET = 950;

    const double ARM_ANGLE_TARGET = 0;
    const double ELEVATOR_ANGLE_TARGET = 1750;

    const double ELEVATOR_LOW_PRIME_TARGET = 0;
    const double ARM_LOW_PRIME_TARGET = 4000;

    const double ELEVATOR_LOW_MOVE_TARGET = ELEVATOR_LOW_PRIME_TARGET;
    const double ELEVATOR_LOW_SCORE_LOWER = ELEVATOR_LOW_MOVE_TARGET - 50;
    const double ELEVATOR_LOW_SCORE_UPPER = ELEVATOR_LOW_MOVE_TARGET + 50;
    const double ARM_LOW_MOVE_TARGET = 4350;
    const double ARM_LOW_SCORE_LOWER = ARM_LOW_MOVE_TARGET - 50;
    const double ARM_LOW_SCORE_UPPER = ARM_LOW_MOVE_TARGET + 50;

    const double ELEVATOR_LOW_SCORE_TARGET = 0;
    const double ARM_LOW_SCORE_TARGET = ARM_LOW_MOVE_TARGET;

    const double ELEVATOR_HIGH_PRIME_TARGET = 3750;
    const double ARM_HIGH_PRIME_TARGET = 3800;

    const double ELEVATOR_HIGH_MOVE_TARGET = ELEVATOR_HIGH_PRIME_TARGET;
    const double ELEVATOR_HIGH_SCORE_LOWER = ELEVATOR_HIGH_MOVE_TARGET - 50;
    const double ELEVATOR_HIGH_SCORE_UPPER = ELEVATOR_HIGH_MOVE_TARGET + 50;
    const double ARM_HIGH_MOVE_TARGET = 4150;
    const double ARM_HIGH_SCORE_LOWER = ARM_HIGH_MOVE_TARGET - 50;
    const double ARM_HIGH_SCORE_UPPER = ARM_HIGH_MOVE_TARGET + 50;

    const double ELEVATOR_HIGH_SCORE_TARGET = ELEVATOR_HIGH_PRIME_TARGET;
    const double ARM_HIGH_SCORE_TARGET = ARM_HIGH_MOVE_TARGET;

    const scheduled_update_t SCORE_TIME = 500;

    /* const order_t ARM_LIMIT_SWITCH_ORDER = 1;
     const order_t ELEVATOR_LIMIT_SWITCH_ORDER = 1;
     const order_t ARM_ENCODER_ORDER = 1;
     const order_t ELEVATOR_ENCODER_ORDER = 1;*/

    //Subsystem controller
    extern subsystem_controller *cap_subsystem;

    extern BaseReadable::adi_digital_readable* arm_limit_switch_right;
    extern BaseReadable::adi_digital_readable* elevator_limit_switch;
    extern BaseReadable::motor_encoder_readable* arm_encoder;
    extern BaseReadable::motor_encoder_readable* elevator_encoder;
    extern BaseCommandable::multi_motor_commandable* arm_motors;

    void init();

    void destroy();
}

#endif //VEX_U_2018_V5_CAP_H
