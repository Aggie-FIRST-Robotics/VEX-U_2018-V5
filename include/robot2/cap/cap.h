#ifndef VEX_U_2018_V5_CAP_2_H
#define VEX_U_2018_V5_CAP_2_H

#include "main.h"
#include "afr-vexu-lib/subsystem_controller.h"

namespace AFR::VexU::Robot2::Cap{
    const pros::motor_brake_mode_e_t ARM_LEFT_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;
    const pros::motor_brake_mode_e_t ARM_RIGHT_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;
    const pros::motor_brake_mode_e_t ELBOW_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;
    const pros::motor_brake_mode_e_t WRIST_BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;

    extern subsystem_controller* cap_subsystem;

    //Down
    const double DOWN_ARM_TARGET = 0;
    const double DOWN_ELBOW_TARGET = 300;

    //Straight Up
    const double STRAIGHT_UP_ARM_TARGET = DOWN_ARM_TARGET;
    const double STRAIGHT_UP_ELBOW_TARGET = 200;

    //Hold
    const double HOLD_ARM_TARGET = DOWN_ARM_TARGET;
    const double HOLD_ELBOW_TARGET = 100;

    //Score Prime
    const double SCORE_PRIME_ARM_TARGET = 200;
    const double SCORE_PRIME_ELBOW_TARGET = 100;

    //Score
    const double SCORE_ARM_TARGET = SCORE_PRIME_ARM_TARGET;
    const double SCORE_ARM_LOWER_BOUND = SCORE_ARM_TARGET - 50;
    const double SCORE_ARM_UPPER_BOUND = SCORE_ARM_TARGET + 50;

    const double SCORE_ELBOW_TARGET = 150;
    const double SCORE_ELBOW_LOWER_BOUND = SCORE_ELBOW_TARGET - 50;
    const double SCORE_ELBOW_UPPER_BOUND = SCORE_ELBOW_TARGET + 50;

    //Pull Back
    const double PULL_BACK_ARM_TARGET = 100;
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
