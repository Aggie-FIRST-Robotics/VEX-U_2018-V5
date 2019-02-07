#ifndef VEX_U_2018_V5_ROBOT_H
#define VEX_U_2018_V5_ROBOT_H

#include "afr-vexu-lib/defines.h"

namespace AFR::VexU::Robot{
    const port_t RIGHT_RAIL_MOTOR_A_PORT = 16;      // 2/6/19
    const port_t RIGHT_RAIL_MOTOR_B_PORT = 19;      // 2/6/19
    const port_t LEFT_RAIL_MOTOR_A_PORT = 14;       // 2/6/19
    const port_t LEFT_RAIL_MOTOR_B_PORT = 15;       // 2/6/19
    const port_t NAUTILUS_MOTOR_PORT = 12;          // 2/6/19
    const port_t ARM_MOTOR_RIGHT_PORT = 17;         // 2/6/19
    const port_t ARM_MOTOR_LEFT_PORT = 13;          // 2/6/19
    const port_t ELEVATOR_MOTOR_PORT = 18;          // 2/6/19
    const port_t INTAKE_MOTOR_PORT = 10;            // 2/6/19

    const port_t NAUTILUS_LIMIT_SWITCH_PORT = 7;    // 2/6/19
    const port_t ARM_LIMIT_SWITCH_BOTTOM_PORT = 1;  // 2/6/19
    const port_t VEE_LIMIT_SWITCH_PORT = 2;         // 2/6/19

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
