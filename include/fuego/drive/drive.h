#ifndef VEX_U_2018_V5_DRIVE_H
#define VEX_U_2018_V5_DRIVE_H

#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "robot2/robot.h"
#include "afr-vexu-lib/subsystem_controller.h"
#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "afr-vexu-lib/base-action/set_value_action.h"
#include "afr-vexu-lib/base-readable/adi_digital_readable.h"
#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"

namespace AFR::VexU::Robot2::Drive {
    const scheduled_update_t START_UPDATE_PERIOD = 1000;

    const scheduled_update_t START_FRONT_LEFT_MOTOR_UPDATE_PERIOD = 10;
    const scheduled_update_t START_FRONT_RIGHT_MOTOR_UPDATE_PERIOD = 10;
    const scheduled_update_t START_BACK_LEFT_MOTOR_UPDATE_PERIOD = 10;
    const scheduled_update_t START_BACK_RIGHT_MOTOR_UPDATE_PERIOD = 10;

    extern BaseCommandable::motor_commandable* front_left_motor;
    extern BaseCommandable::motor_commandable* front_right_motor;
    extern BaseCommandable::motor_commandable* back_left_motor;
    extern BaseCommandable::motor_commandable* back_right_motor;

    extern subsystem_controller *drive_subsystem;

    void init();
    void destroy();
}

#endif //VEX_U_2018_V5_DRIVE_H
