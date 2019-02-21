#ifndef VEX_U_2018_V5_ROBOT_2_H
#define VEX_U_2018_V5_ROBOT_2_H

#include "afr-vexu-lib/defines.h"

namespace AFR::VexU::Robot2{
    const port_t RIGHT_RAIL_MOTOR_A_PORT    = 16;      // Not up to date
    const port_t RIGHT_RAIL_MOTOR_B_PORT    = 19;      // Not up to date
    const port_t LEFT_RAIL_MOTOR_A_PORT     = 14;      // Not up to date
    const port_t LEFT_RAIL_MOTOR_B_PORT     = 15;      // Not up to date

    const pros::motor_gearset_e_t RIGHT_RAIL_MOTOR_A_GEARSET    = pros::E_MOTOR_GEARSET_06;
    const pros::motor_gearset_e_t RIGHT_RAIL_MOTOR_B_GEARSET    = pros::E_MOTOR_GEARSET_06;
    const pros::motor_gearset_e_t LEFT_RAIL_MOTOR_A_GEARSET     = pros::E_MOTOR_GEARSET_06;
    const pros::motor_gearset_e_t LEFT_RAIL_MOTOR_B_GEARSET     = pros::E_MOTOR_GEARSET_06;

    const pros::motor_brake_mode_e_t RIGHT_RAIL_MOTOR_A_BRAKE_MODE = pros::E_MOTOR_BRAKE_COAST;
    const pros::motor_brake_mode_e_t RIGHT_RAIL_MOTOR_B_BRAKE_MODE = pros::E_MOTOR_BRAKE_COAST;
    const pros::motor_brake_mode_e_t LEFT_RAIL_MOTOR_A_BRAKE_MODE = pros::E_MOTOR_BRAKE_COAST;
    const pros::motor_brake_mode_e_t LEFT_RAIL_MOTOR_B_BRAKE_MODE = pros::E_MOTOR_BRAKE_COAST;

    const port_t ARM_LEFT_MOTOR_PORT    = 2;
    const port_t ARM_RIGHT_MOTOR_PORT   = 18;
    const port_t ELBOW_MOTOR_PORT       = 1;
    const port_t WRIST_MOTOR_PORT       = 19;

    const pros::motor_gearset_e_t ARM_LEFT_GEARSET      = pros::E_MOTOR_GEARSET_18;
    const pros::motor_gearset_e_t ARM_RIGHT_GEARSET     = pros::E_MOTOR_GEARSET_18;
    const pros::motor_gearset_e_t ELBOW_GEARSET         = pros::E_MOTOR_GEARSET_18;
    const pros::motor_gearset_e_t WRIST_GEARSET         = pros::E_MOTOR_GEARSET_18;

    const port_t ARM_LIMIT_SWITCH_PORT      = 8;
    const port_t ELBOW_LIMIT_SWITCH_PORT    = 7;
    const port_t WRIST_LIMIT_SWITCH_PORT    = 6;

    const port_t BALL_INTAKE_MOTOR_PORT    = 3;     //Not up to date
    const port_t BALL_LOADER_MOTOR_PORT    = 4;     //Not up to date

    const pros::motor_gearset_e_t BALL_INTAKE_GEARSET      = pros::E_MOTOR_GEARSET_18;
    const pros::motor_gearset_e_t BALL_LOADER_GEARSET      = pros::E_MOTOR_GEARSET_18;

    const pros::controller_digital_e_t  UP_BUTTON            = pros::E_CONTROLLER_DIGITAL_R1;
    const pros::controller_digital_e_t  DOWN_BUTTON          = pros::E_CONTROLLER_DIGITAL_R2;
    const pros::controller_digital_e_t  FLIP_BUTTON          = pros::E_CONTROLLER_DIGITAL_L2;
    const pros::controller_digital_e_t  SCORE_BUTTON         = pros::E_CONTROLLER_DIGITAL_L1;
    const pros::controller_digital_e_t  OUTTAKE_BUTTON       = pros::E_CONTROLLER_DIGITAL_Y;
    const pros::controller_digital_e_t  SHOOT_BUTTON         = pros::E_CONTROLLER_DIGITAL_X;
    const pros::controller_digital_e_t  BALL_INTAKE_BUTTON   = pros::E_CONTROLLER_DIGITAL_Z;
    const pros::controller_analog_e_t   LEFT_DRIVE_STICK     = pros::E_CONTROLLER_ANALOG_LEFT_Y;
    const pros::controller_analog_e_t   RIGHT_DRIVE_STICK    = pros::E_CONTROLLER_ANALOG_RIGHT_X;




    void init_robot();
    void competition_init();
    void auto_robot();
    void op_control();
    void disabled_robot();
    void destroy();
    void restart();
}

#endif //VEX_U_2018_V5_ROBOT_H
