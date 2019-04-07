#ifndef VEX_U_2018_V5_CAP_2_H
#define VEX_U_2018_V5_CAP_2_H

#include "rev/rev.h"
#include "afr-lib/state_controller.h"

#include "rev/cap/arm/arm.h"
#include "rev/cap/wrist/wrist.h"

#include "afr-vexu-lib/base-readable/digital_edge_detector.h"

namespace AFR::VexU::Rev::Cap{

    const scheduled_update_t UPDATE_PERIOD = 10;

    //Down
    const double ARM_GROUND_POSITION = 0;
    const double ELBOW_GROUND_POSITION = 3800;

    //Flip Low
    const double ARM_FLIP_LOW_POSITION = 500;

    //Hold
    const double ELBOW_STORE_POSITION = 700;

    //Flip High
    const double ELBOW_FLIP_HIGH_POSITION = 2000;

    //Descore Prime
    const double ARM_DESCORE_PRIME_POSITION = 1750;
    const double ELBOW_DESCORE_PRIME_POSITION = -800;

    //Score
    const double ARM_SCORE_POSITION = 2450;
    const double ELBOW_SCORE_POSITION = -800;

    //Score Prime
    const double ARM_SCORE_PRIME_POSITION = 2450;
    const double ELBOW_SCORE_PRIME_POSITION = 900;

    //Wrist
    const double WRIST_FLIP_POSITION = 750;

    const double PID_TOLERANCE = 100;
    const int16_t INTAKE_VOLTAGE = 12000;
    const int16_t IDLE_VOLTAGE = 3000;

    const double ANGLE_ARM_TARGET = 850;
    const double ANGLE_ELBOW_TARGET = 5850;

    void init();
}

#endif //VEX_U_2018_V5_CAP_H
