#ifndef VEX_U_2018_V5_DRIVE_H
#define VEX_U_2018_V5_DRIVE_H

#include "fuego/fuego.h"
#include "afr-lib/state_controller.h"
#include "afr-vexu-lib/base-commandable/motor_commandable.h"

namespace AFR::VexU::Fuego::Drive{
    const scheduled_update_t UPDATE_PERIOD = 10;

    const pros::motor_brake_mode_e_t LEFT_MOTOR_A_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;
    const pros::motor_brake_mode_e_t RIGHT_MOTOR_A_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;
    const pros::motor_brake_mode_e_t LEFT_MOTOR_B_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;
    const pros::motor_brake_mode_e_t RIGHT_MOTOR_B_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;

    const scheduled_update_t DRIVE_UPDATE_PERIOD = 10;



    void init();
    void destroy();
}

#endif //VEX_U_2018_V5_DRIVE_H
