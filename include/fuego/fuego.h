#ifndef VEX_U_2018_V5_FUEGO_H
#define VEX_U_2018_V5_FUEGO_H

#include "afr-lib/defines.h"
#include "afr-vexu-lib/base-readable/battery_readable.h"
#include "afr-vexu-lib/base-readable/competition_readable.h"
#include "afr-vexu-lib/base-readable/controller_readable.h"
#include "afr-vexu-lib/ports_list.h"

#include "main.h"

namespace AFR::VexU::Fuego{
#define FUEGO

    /////DRIVETRAIN
    const port_t RIGHT_RAIL_MOTOR_A_PORT = 17;
    const port_t RIGHT_RAIL_MOTOR_B_PORT = 5;
    const port_t LEFT_RAIL_MOTOR_A_PORT = 4;
    const port_t LEFT_RAIL_MOTOR_B_PORT = 3;
    const pros::motor_gearset_e_t DRIVETRAIN_GEARSET = pros::E_MOTOR_GEARSET_06;
    const pros::motor_brake_mode_e_t DRIVETRAIN_BRAKE_MODE = pros::E_MOTOR_BRAKE_COAST;

    /////LOADER
    const port_t LOADER_MOTOR_PORT = 8;
    const pros::motor_gearset_e_t LOADER_GEARSET = pros::E_MOTOR_GEARSET_06;
    const pros::motor_brake_mode_e_t LOADER_BRAKE_MODE = pros::E_MOTOR_BRAKE_COAST;

    /////HOOD
    const port_t HOOD_MOTOR_PORT = 16;
    const pros::motor_gearset_e_t HOOD_GEARSET = pros::E_MOTOR_GEARSET_18;
    const pros::motor_brake_mode_e_t HOOD_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;

    /////TURRET
    const port_t TURRET_MOTOR_PORT = 15;
    const pros::motor_gearset_e_t TURRET_GEARSET = pros::E_MOTOR_GEARSET_36;
    const pros::motor_brake_mode_e_t TURRET_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;

    /////FLYWHEEL
    const port_t FLYWHEEL_LEFT_PORT = 12;
    const port_t FLYWHEEL_RIGHT_PORT = 11;
    const pros::motor_gearset_e_t FLYWHEEL_GEARSET = pros::E_MOTOR_GEARSET_06;
    const pros::motor_brake_mode_e_t FLYWHEEL_BRAKE_MODE = pros::E_MOTOR_BRAKE_COAST;

    /////ARM
    const port_t ARM_LEFT_MOTOR_PORT = 2;
    const port_t ARM_RIGHT_MOTOR_PORT = 13;
    const pros::motor_gearset_e_t ARM_GEARSET = pros::E_MOTOR_GEARSET_18;
    const pros::motor_brake_mode_e_t ARM_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;

    /////ELBOW
    const port_t ELBOW_MOTOR_PORT = 1;
    const pros::motor_gearset_e_t ELBOW_GEARSET = pros::E_MOTOR_GEARSET_18;
    const pros::motor_brake_mode_e_t ELBOW_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;

    /////WRIST
    const port_t WRIST_MOTOR_PORT = 19;
    const pros::motor_gearset_e_t WRIST_GEARSET = pros::E_MOTOR_GEARSET_18;
    const pros::motor_brake_mode_e_t WRIST_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;

    /////CAP INTAKE
    const port_t CAP_INTAKE_MOTOR_PORT = 20;
    const pros::motor_gearset_e_t CAP_INTAKE_GEARSET = pros::E_MOTOR_GEARSET_18;
    const pros::motor_brake_mode_e_t CAP_INTAKE_BRAKE_MODE = pros::E_MOTOR_BRAKE_COAST;

    /////BALL INTAKE
    const port_t BALL_INTAKE_MOTOR_PORT = 18;
    const pros::motor_gearset_e_t BALL_INTAKE_GEARSET = pros::E_MOTOR_GEARSET_06;
    const pros::motor_brake_mode_e_t BALL_INTAKE_BRAKE_MODE = pros::E_MOTOR_BRAKE_COAST;

    /////LIMIT SWITCHES
    const port_t ARM_LIMIT_SWITCH_PORT = 8;
    const port_t ELBOW_LIMIT_SWITCH_PORT = 7;
    const port_t WRIST_LIMIT_SWITCH_PORT = 6;



    const pros::controller_digital_e_t UP_BUTTON = pros::E_CONTROLLER_DIGITAL_L1;
    const pros::controller_digital_e_t DOWN_BUTTON = pros::E_CONTROLLER_DIGITAL_L2;
    const pros::controller_digital_e_t FLIP_BUTTON = pros::E_CONTROLLER_DIGITAL_R2;
    const pros::controller_digital_e_t FLIP_PARTNER_BUTTON = pros::E_CONTROLLER_DIGITAL_B;
    const pros::controller_digital_e_t SCORE_BUTTON = pros::E_CONTROLLER_DIGITAL_L1;
    const pros::controller_digital_e_t INTAKE_BUTTON = pros::E_CONTROLLER_DIGITAL_LEFT;
    const pros::controller_digital_e_t OUTTAKE_BUTTON = pros::E_CONTROLLER_DIGITAL_UP;
    const pros::controller_digital_e_t RESET_BUTTON = pros::E_CONTROLLER_DIGITAL_RIGHT;
    const pros::controller_digital_e_t DESCORE_BUTTON = pros::E_CONTROLLER_DIGITAL_R1;
    const pros::controller_digital_e_t BALL_SPIT_BUTTON = pros::E_CONTROLLER_DIGITAL_X;
    const pros::controller_digital_e_t BALL_SWALLOW_BUTTON = pros::E_CONTROLLER_DIGITAL_A;

    const pros::controller_analog_e_t LEFT_DRIVE_STICK = pros::E_CONTROLLER_ANALOG_LEFT_Y;
    const pros::controller_analog_e_t RIGHT_DRIVE_STICK = pros::E_CONTROLLER_ANALOG_RIGHT_X;

    void init_robot();
    void competition_init();
    void auto_robot();
    void op_control();
    void disabled_robot();
    void destroy();
    void restart();
}

#endif //VEX_U_2018_V5_FUEGO_H
