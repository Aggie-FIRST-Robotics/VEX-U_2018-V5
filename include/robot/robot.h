#ifndef VEX_U_2018_V5_ROBOT_H
#define VEX_U_2018_V5_ROBOT_H

#include <afr-vexu-lib/defines.h>

namespace AFR::VexU::Robot{
    const port_t RIGHT_RAIL_MOTOR_A_PORT = 11;
    const port_t RIGHT_RAIL_MOTOR_B_PROT = 20;
    const port_t LEFT_RAIL_MOTOR_A_PORT = 13;
    const port_t LEFT_RAIL_MOTOR_B_PORT = 12;
    const port_t CATAPULT_MOTOR_PORT = 14;
    const port_t ARM_MOTOR_A_PORT = 17;
    const port_t ARM_MOTOR_B_PORT = 16;
    const port_t ELEVATOR_MOTOR_PORT = 8;
    const port_t INTAKE_MOTOR_PORT = 10;

    void init_robot();
    void competition_init();
    void auto_robot();
    void opcontrol_robot();
    void disabled_robot();
}

#endif //VEX_U_2018_V5_ROBOT_H
