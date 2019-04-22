#ifndef VEX_U_2018_V5_SHOOTER_H
#define VEX_U_2018_V5_SHOOTER_H

#include "afr-lib/state_controller.h"
#include "afr-vexu-lib/base-readable/digital_edge_detector.h"
#include "afr-vexu-lib/base-readable/digital_debounce.h"
#include "afr-vexu-lib/base-commandable/controller_commandable.h"
#include "afr-vexu-lib/vision/vision_targeting.h"

#include "rev/shooter/altitude/altitude.h"
#include "rev/shooter/puncher/puncher.h"
#include "rev/shooter/rollers/rollers.h"

namespace AFR::VexU::Rev::Shooter{

    const scheduled_update_t UPDATE_PERIOD = 10;

    const double HOOD_TOLERANCE = 100;
    const double TURRET_TOLERANCE = 100;

    const int32_t STICK_CANCEL_VALUE = 64;
    const uint8_t BUTTON_DELAY = 15;

    /////PUNCHER
    const double FIRE_TARGET         = 0;
    const double COCK_TARGET         = 3450;
    const double PUNCHER_TOLERANCE   = 100;

    /////SET POINTS
    const double ALTITUDE_STOW_TARGET   = 0;
    const double ALTITUDE_HIGH_TARGET   = 30;
    const double ALTITUDE_LOW_TARGET    = 230;
    const double ALTITUDE_TOLERANCE     = 100;

    /////AUTO AIM
    const double AUTO_TOLERANCE = 50;

    /////ROLLERS
    const double ROLLER_LIMIT = 50;

    void init();
    void destroy();

    struct shooter_meta {
        double altitude_set_point;
        bool is_double;
        unsigned long timeout;
        uint8_t ball_count;
        bool is_past_thresh;
    };

    extern state_controller<shooter_meta>* shooter_state_controller;

    extern state* set_point;
    extern state* auto_aim;
    extern state* ready;
    extern state* cock;
    extern state* double_shot;
}

#endif //VEX_U_2018_V5_SHOOTER_H
