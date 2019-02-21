#ifndef VEX_U_2018_V5_BALL_INTAKE_H
#define VEX_U_2018_V5_BALL_INTAKE_H

#include "afr-vexu-lib/subsystem_controller.h"

namespace AFR::VexU::Robot2::BallIntake{
    const pros::motor_brake_mode_e_t BALL_INTAKE_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;

    extern subsystem_controller* ball_intake_subsystem;

    void init();
}

#endif //VEX_U_2018_V5_BALL_INTAKE_H
