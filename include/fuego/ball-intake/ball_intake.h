#ifndef VEX_U_2018_V5_BALL_INTAKE_H
#define VEX_U_2018_V5_BALL_INTAKE_H

#include "afr-lib/state_controller.h"
#include "fuego/fuego.h"

#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "afr-vexu-lib/base-readable/digital_edge_detector.h"
#include "afr-vexu-lib/base-readable/controller_readable.h"

namespace AFR::VexU::Fuego::BallIntake{
    const scheduled_update_t UPDATE_PERIOD = 10;

    const bool DIRECTION = false;
    const int16_t SWALLOW_VOLTAGE = 12000;
    const int16_t SPIT_VOLTAGE = -12000;

    void init();
    void destroy();
}

#endif //VEX_U_2018_V5_BALL_INTAKE_H
