#ifndef VEX_U_2018_V5_ROBOT_2_H
#define VEX_U_2018_V5_ROBOT_2_H

#include "afr-vexu-lib/subsystem_controller.h"

namespace AFR::VexU::Robot2{
    const port_t ARM_LEFT_MOTOR_PORT = 2;
    const port_t ARM_RIGHT_MOTOR_PORT = 18;
    const port_t ELBOW_MOTOR_PORT = 1;
    const port_t WRIST_MOTOR_PORT = 19;

    const pros::motor_gearset_e_t ARM_LEFT_GEARSET = pros::E_MOTOR_GEARSET_18;
    const pros::motor_gearset_e_t ARM_RIGHT_GEARSET = pros::E_MOTOR_GEARSET_18;
    const pros::motor_gearset_e_t ELBOW_GEARSET = pros::E_MOTOR_GEARSET_18;
    const pros::motor_gearset_e_t WRIST_GEARSET = pros::E_MOTOR_GEARSET_18;

    const port_t ARM_LIMIT_SWITCH_PORT = 8;
    const port_t ELBOW_LIMIT_SWITCH_PORT = 7;
    const port_t WRIST_LIMIT_SWITCH_PORT = 6;

    const pros::controller_digital_e_t UP_BUTTON = pros::E_CONTROLLER_DIGITAL_R1;
    const pros::controller_digital_e_t DOWN_BUTTON = pros::E_CONTROLLER_DIGITAL_R2;
    const pros::controller_digital_e_t FLIP_BUTTON = pros::E_CONTROLLER_DIGITAL_L2;
    const pros::controller_digital_e_t SCORE_BUTTON = pros::E_CONTROLLER_DIGITAL_L1;
    const pros::controller_digital_e_t OUTTAKE_BUTTON = pros::E_CONTROLLER_DIGITAL_Y;

    void init_robot();
    void op_control();
}

#endif //VEX_U_2018_V5_ROBOT_H
