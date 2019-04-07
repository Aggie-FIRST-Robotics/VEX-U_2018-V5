#ifndef VEX_U_2018_V5_BALL_INTAKE_H
#define VEX_U_2018_V5_BALL_INTAKE_H

#include "afr-lib/state_controller.h"
#include "rev/rev.h"

#include "rev/ball-intake/rollers/rollers.h"

#include "afr-vexu-lib/base-readable/digital_edge_detector.h"

namespace AFR::VexU::Rev::BallIntake{
    const scheduled_update_t UPDATE_PERIOD = 10;

    const bool DIRECTION = false;
    const int16_t SWALLOW_VOLTAGE = 12000;
    const int16_t SPIT_VOLTAGE = -12000;

    void init();
    void destroy();
}

#endif //VEX_U_2018_V5_BALL_INTAKE_H
