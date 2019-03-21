#ifndef VEX_U_2018_V5_BALL_INTAKE_H
#define VEX_U_2018_V5_BALL_INTAKE_H

#include "afr-lib/state_controller.h"
#include "fuego/fuego.h"

#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "afr-vexu-lib/base-action/pid_action.h"

namespace AFR::VexU::Fuego::BallIntake{
    const scheduled_update_t BALL_INTAKE_UPDATE_PERIOD = 10;

    const pros::motor_brake_mode_e_t BALL_INTAKE_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;

    void init();

    extern state_controller<void>* ball_intake_controller;
}

#endif //VEX_U_2018_V5_BALL_INTAKE_H
