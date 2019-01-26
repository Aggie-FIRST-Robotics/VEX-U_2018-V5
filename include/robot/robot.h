#ifndef VEX_U_2018_V5_ROBOT_H
#define VEX_U_2018_V5_ROBOT_H

#include "afr-vexu-lib/defines.h"

namespace AFR::VexU::Robot{
    const port_t RIGHT_RAIL_MOTOR_A_PORT = 11;
    const port_t RIGHT_RAIL_MOTOR_B_PROT = 20;
    const port_t LEFT_RAIL_MOTOR_A_PORT = 13;
    const port_t LEFT_RAIL_MOTOR_B_PORT = 12;
    const port_t NAUTILUS_MOTOR_PORT = 14;
    const port_t ARM_MOTOR_A_PORT = 17;
    const port_t ARM_MOTOR_B_PORT = 16;
    const port_t ELEVATOR_MOTOR_PORT = 8;
    const port_t INTAKE_MOTOR_PORT = 10;

    const port_t NAUTILUS_LIMIT_SWITCH_PORT = 1;
    const port_t ARM_LIMIT_SWITCH_TOP_PORT = 2;
    const port_t ARM_LIMIT_SWITCH_BOTTOM_PORT = 3;

    const pros::controller_digital_e_t FIRE_BUTTON = pros::E_CONTROLLER_DIGITAL_A;

    void init_robot();
    void competition_init();
    void auto_robot();
    void opcontrol_robot();
    void disabled_robot();
    void destroy();
    void restart();
}

#endif //VEX_U_2018_V5_ROBOT_H
