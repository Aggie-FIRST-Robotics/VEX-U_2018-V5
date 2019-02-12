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
    const port_t ARM_LIMIT_SWITCH_PORT = 1;         // 2/8/19
    const port_t VEE_LIMIT_SWITCH_PORT = 2;         // 2/6/19
    const port_t ELEVATOR_LIMIT_SWITCH_PORT = 3;     // 2/8/19

    const pros::motor_gearset_e_t RIGHT_RAIL_MOTOR_A_GEARSET = pros::E_MOTOR_GEARSET_06;
    const pros::motor_gearset_e_t RIGHT_RAIL_MOTOR_B_GEARSET = pros::E_MOTOR_GEARSET_06;
    const pros::motor_gearset_e_t LEFT_RAIL_MOTOR_A_GEARSET = pros::E_MOTOR_GEARSET_06;
    const pros::motor_gearset_e_t LEFT_RAIL_MOTOR_B_GEARSET = pros::E_MOTOR_GEARSET_06;
    const pros::motor_gearset_e_t NAUTILUS_MOTOR_GEARSET = pros::E_MOTOR_GEARSET_18;
    const pros::motor_gearset_e_t ARM_MOTOR_RIGHT_GEARSET = pros::E_MOTOR_GEARSET_36;
    const pros::motor_gearset_e_t ARM_MOTOR_LEFT_GEARSET = pros::E_MOTOR_GEARSET_36;
    const pros::motor_gearset_e_t ELEVATOR_MOTOR_GEARSET = pros::E_MOTOR_GEARSET_36;
    const pros::motor_gearset_e_t INTAKE_MOTOR_GEARSET = pros::E_MOTOR_GEARSET_18;

    const pros::motor_brake_mode_e_t RIGHT_RAIL_MOTOR_A_BRAKE_MODE = pros::E_MOTOR_BRAKE_COAST;
    const pros::motor_brake_mode_e_t RIGHT_RAIL_MOTOR_B_BRAKE_MODE = pros::E_MOTOR_BRAKE_COAST;
    const pros::motor_brake_mode_e_t LEFT_RAIL_MOTOR_A_BRAKE_MODE = pros::E_MOTOR_BRAKE_COAST;
    const pros::motor_brake_mode_e_t LEFT_RAIL_MOTOR_B_BRAKE_MODE = pros::E_MOTOR_BRAKE_COAST;
    const pros::motor_brake_mode_e_t NAUTILUS_MOTOR_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;


    const pros::controller_digital_e_t FIRE_BUTTON = pros::E_CONTROLLER_DIGITAL_A;
    const pros::controller_digital_e_t INTAKE_BUTTON = pros::E_CONTROLLER_DIGITAL_R1;
    const pros::controller_digital_e_t OUTTAKE_BUTTON = pros::E_CONTROLLER_DIGITAL_R2;
    const pros::controller_digital_e_t FLIP_BUTTON = pros::E_CONTROLLER_DIGITAL_B;
    const pros::controller_digital_e_t ANGLE_BUTTON = pros::E_CONTROLLER_DIGITAL_X;
    const pros::controller_digital_e_t LOW_BUTTON = pros::E_CONTROLLER_DIGITAL_L1;
    const pros::controller_digital_e_t HIGH_BUTTON = pros::E_CONTROLLER_DIGITAL_L2;
    const pros::controller_digital_e_t SCORE_BUTTON = pros::E_CONTROLLER_DIGITAL_Y;
    const pros::controller_analog_e_t LEFT_DRIVE_STICK = pros::E_CONTROLLER_ANALOG_LEFT_Y;
    const pros::controller_analog_e_t RIGHT_DRIVE_STICK = pros::E_CONTROLLER_ANALOG_LEFT_X;

    void init_robot();
    void competition_init();
    void auto_robot();
    void opcontrol_robot();
    void disabled_robot();
    void destroy();
    void restart();
}

#endif //VEX_U_2018_V5_ROBOT_H
