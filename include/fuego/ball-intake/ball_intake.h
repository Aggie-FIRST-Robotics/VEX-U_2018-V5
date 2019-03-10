#ifndef VEX_U_2018_V5_BALL_INTAKE_H
#define VEX_U_2018_V5_BALL_INTAKE_H

#include "afr-lib/state_controller.h"
#include "fuego/fuego.h"

namespace AFR::VexU::Fuego::BallIntake{
    const pros::motor_brake_mode_e_t BALL_INTAKE_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;

    void init();
}

#endif //VEX_U_2018_V5_BALL_INTAKE_H
