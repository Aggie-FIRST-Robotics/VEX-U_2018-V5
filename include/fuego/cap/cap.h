#ifndef VEX_U_2018_V5_CAP_2_H
#define VEX_U_2018_V5_CAP_2_H

#include "main.h"
#include "afr-vexu-lib/subsystem_controller.h"
#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"
#include "afr-vexu-lib/base-action/pid_action.h"
#include "afr-vexu-lib/base-action/zero_encoder_action.h"
#include "afr-vexu-lib/base-action/set_value_action.h"
#include "wrist_flip_action.h"

namespace AFR::VexU::Robot2::Cap{
    const pros::motor_brake_mode_e_t ARM_LEFT_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;
    const pros::motor_brake_mode_e_t ARM_RIGHT_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;
    const pros::motor_brake_mode_e_t ELBOW_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;
    const pros::motor_brake_mode_e_t WRIST_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;
    const pros::motor_brake_mode_e_t INTAKE_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;

    extern BaseReadable::motor_encoder_readable* arm_encoder;
    extern BaseReadable::motor_encoder_readable* elbow_encoder;
    extern BaseReadable::motor_encoder_readable* wrist_encoder;

    extern BaseAction::zero_encoder_action<bool, double, int16_t>* arm_zero_action;
    extern BaseAction::zero_encoder_action<bool, double, int16_t>* elbow_zero_action;
    extern BaseAction::zero_encoder_action<bool, double, int16_t>* wrist_zero_action;

    extern BaseAction::pid_action<double, int16_t>* arm_pid_action;
    extern BaseAction::pid_action<double, int16_t>* elbow_pid_action;
    extern BaseAction::pid_action<double, int16_t>* wrist_pid_action;

    extern BaseAction::set_value_action<int16_t>* intake_suck_action;
    extern BaseAction::set_value_action<int16_t>* intake_hold_action;
    extern BaseAction::set_value_action<int16_t>* intake_spit_action;

    extern wrist_flip_action* wrist_flip;

    extern state_controller* cap_state_machine;
    extern subsystem_controller* cap_subsystem;

    //Down
    const double DOWN_ARM_TARGET = 0;
    const double DOWN_ELBOW_TARGET = 4000;

    //Flip Low Prime
    const double FLIP_LOW_PRIME_ARM_TARGET = 500;
    const double FLIP_LOW_PRIME_ELBOW_TARGET = DOWN_ELBOW_TARGET;

    //Flip Low
    const double FLIP_LOW_ARM_TARGET = FLIP_LOW_PRIME_ARM_TARGET;
    const double FLIP_LOW_ELBOW_TARGET = FLIP_LOW_PRIME_ELBOW_TARGET;

    //Hold
    const double HOLD_ARM_TARGET = DOWN_ARM_TARGET;
    const double HOLD_ELBOW_TARGET = 700;

    //Flip High Prime
    const double FLIP_HIGH_PRIME_ARM_TARGET = DOWN_ARM_TARGET;
    const double FLIP_HIGH_PRIME_ELBOW_TARGET = 1000;

    //Flip High
    const double FLIP_HIGH_ARM_TARGET = DOWN_ARM_TARGET;
    const double FLIP_HIGH_ELBOW_TARGET = 2000;

    //Descore Prime
    const double DESCORE_PRIME_ARM_TARGET = 1750;
    const double DESCORE_PRIME_ELBOW_TARGET = -300;

    //Descore Grab
    const double DESCORE_GRAB_ARM_TARGET = 2450;
    const double DESCORE_GRAB_ELBOW_TARGET = DESCORE_PRIME_ELBOW_TARGET;

    //Score Prime
    const double SCORE_PRIME_ARM_TARGET = DESCORE_GRAB_ARM_TARGET;
    const double SCORE_PRIME_ELBOW_TARGET = 900;

    //Score
    const double SCORE_ARM_TARGET = SCORE_PRIME_ARM_TARGET;
    const double SCORE_ELBOW_TARGET = DESCORE_PRIME_ELBOW_TARGET;

    //Pull Back
    const double PULL_BACK_ARM_TARGET = DESCORE_PRIME_ARM_TARGET;
    const double PULL_BACK_ARM_LOWER_BOUND = PULL_BACK_ARM_TARGET - 50;
    const double PULL_BACK_ARM_UPPER_BOUND = PULL_BACK_ARM_TARGET + 50;

    const double PULL_BACK_ELBOW_TARGET = SCORE_ELBOW_TARGET;
    const double PULL_BACK_ELBOW_LOWER_BOUND = PULL_BACK_ELBOW_TARGET - 50;
    const double PULL_BACK_ELBOW_UPPER_BOUND = PULL_BACK_ELBOW_TARGET + 50;

    //Outtake
    const double OUTTAKE_ARM_TARGET = DOWN_ARM_TARGET;
    const double OUTTAKE_ELBOW_TARGET = DOWN_ELBOW_TARGET;

    //Flip
    const double FLIP_TARGET = 750;

    const double ANGLE_ARM_TARGET = 850;
    const double ANGLE_ELBOW_TARGET = 5850;

    void init();
}

#endif //VEX_U_2018_V5_CAP_H
