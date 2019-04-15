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

    //Flip Low
    const double ARM_FLIP_LOW_POSITION = 500;

    //Descore Prime
    const double ARM_DESCORE_PRIME_POSITION = 4600;

    //Score
    const double ARM_SCORE_POSITION = 4600;

    //Score Prime
    const double ARM_SCORE_PRIME_POSITION = 4050;

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
