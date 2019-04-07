#ifndef VEX_U_2018_V5_SHOOTER_H
#define VEX_U_2018_V5_SHOOTER_H

#include "afr-lib/state_controller.h"
#include "afr-vexu-lib/base-readable/digital_edge_detector.h"
#include "afr-vexu-lib/base-commandable/controller_commandable.h"
#include "afr-vexu-lib/vision/vision_targeting.h"

#include "rev/shooter/altitude/altitude.h"
#include "rev/shooter/puncher/puncher.h"

namespace AFR::VexU::Rev::Shooter{

    const scheduled_update_t UPDATE_PERIOD = 10;

    const double HOOD_TOLERANCE = 100;
    const double TURRET_TOLERANCE = 100;

    const int32_t STICK_CANCEL_VALUE = 64;

    /////PUNCHER
    const double FIRE_TARGET         = 0;
    const double COCK_TARGET         = 1600;
    const double PUNCHER_TOLERANCE   = 100;

    /////SET POINTS
    const double ALTITUDE_HIGH_TARGET   = 200;
    const double ALTITUDE_MID_TARGET    = 600;
    const double ALTITUDE_LOW_TARGET    = 1200;
    const double ALTITUDE_TOLERANCE     = 100;

    /////AUTO AIM
    const double AUTO_TOLERANCE = 50;

    void init();
    void destroy();
}

#endif //VEX_U_2018_V5_SHOOTER_H
