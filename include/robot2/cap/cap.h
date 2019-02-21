#ifndef VEX_U_2018_V5_CAP_2_H
#define VEX_U_2018_V5_CAP_2_H

#include "main.h"
#include "afr-vexu-lib/subsystem_controller.h"
#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"

namespace AFR::VexU::Robot2::Cap{
    const pros::motor_brake_mode_e_t ARM_LEFT_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;
    const pros::motor_brake_mode_e_t ARM_RIGHT_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;
    const pros::motor_brake_mode_e_t ELBOW_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;
    const pros::motor_brake_mode_e_t WRIST_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;

    extern BaseReadable::motor_encoder_readable* arm_encoder;
    extern BaseReadable::motor_encoder_readable* elbow_encoder;
    extern BaseReadable::motor_encoder_readable* wrist_encoder;

    extern state_controller* cap_state_machine;
    extern subsystem_controller* cap_subsystem;

    //Down
    const double DOWN_ARM_TARGET = 0;
    const double DOWN_ELBOW_TARGET = 3750;

    //Straight Up
    const double STRAIGHT_UP_ARM_TARGET = DOWN_ARM_TARGET;
    const double STRAIGHT_UP_ELBOW_TARGET = 1500;

    //Hold
    const double HOLD_ARM_TARGET = DOWN_ARM_TARGET;
    const double HOLD_ELBOW_TARGET = 700;

    //Score Prime
    const double SCORE_PRIME_ARM_TARGET = 2250;
    const double SCORE_PRIME_ELBOW_TARGET = HOLD_ELBOW_TARGET;

    //Score
    const double SCORE_ARM_TARGET = SCORE_PRIME_ARM_TARGET;
    const double SCORE_ARM_LOWER_BOUND = SCORE_ARM_TARGET - 50;
    const double SCORE_ARM_UPPER_BOUND = SCORE_ARM_TARGET + 50;

    const double SCORE_ELBOW_TARGET = -350;
    const double SCORE_ELBOW_LOWER_BOUND = SCORE_ELBOW_TARGET - 50;
    const double SCORE_ELBOW_UPPER_BOUND = SCORE_ELBOW_TARGET + 50;

    //Pull Back
    const double PULL_BACK_ARM_TARGET = 1250;
    const double PULL_BACK_ARM_LOWER_BOUND = PULL_BACK_ARM_TARGET - 50;
    const double PULL_BACK_ARM_UPPER_BOUND = PULL_BACK_ARM_TARGET + 50;

    const double PULL_BACK_ELBOW_TARGET = SCORE_ELBOW_TARGET;
    const double PULL_BACK_ELBOW_LOWER_BOUND = PULL_BACK_ELBOW_TARGET - 50;
    const double PULL_BACK_ELBOW_UPPER_BOUND = PULL_BACK_ELBOW_TARGET + 50;

    //Outtake
    const double OUTTAKE_ARM_TARGET = DOWN_ARM_TARGET;
    const double OUTTAKE_ELBOW_TARGET = DOWN_ELBOW_TARGET;

    void init();
}

#endif //VEX_U_2018_V5_CAP_H
