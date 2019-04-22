//
// Created by aamhi on 2/12/2019.
//

#ifndef VEX_U_2018_V5_SHOOTER_H
#define VEX_U_2018_V5_SHOOTER_H

#include "afr-lib/state_controller.h"
#include "afr-vexu-lib/base-readable/digital_edge_detector.h"
#include "afr-vexu-lib/base-commandable/controller_commandable.h"
#include "afr-vexu-lib/vision/vision_targeting.h"

#include "fuego/shooter/flywheel/flywheel.h"
#include "fuego/shooter/turret/turret.h"
#include "fuego/shooter/hood/hood.h"
#include "fuego/shooter/loader/loader.h"

namespace AFR::VexU::Fuego::Shooter{

    const scheduled_update_t UPDATE_PERIOD = 10;

    const double HOOD_TOLERANCE = 100;
    const double TURRET_TOLERANCE = 100;

    const int32_t STICK_CANCEL_VALUE = 64;

    /////FLYWHEEL
    const unsigned int FLYWHEEL_SPEED 		 = 560;
    const unsigned int FLYWHEEL_TOLERANCE   = 800;

    /////LOADER
    const double IDLE_TARGET         = 1000;
    const double FIRE_TARGET         = 0;
    const double WALK_TARGET         = 1600;
    const double LOADER_TOLERANCE    = 50;

    /////SET POINTS
    const double TURRET_LEFT_TARGET     = 500;
    const double TURRET_MID_TARGET      = 1680;
    const double TURRET_RIGHT_TARGET    = 2500;
    const double HOOD_HIGH_TARGET       = 450;
    const double HOOD_MID_TARGET        = 840;
    const double HOOD_LOW_TARGET        = 1200;

    /////AUTO AIM
    const double AUTO_TOLERANCE = 10;

    void init();
    void destroy();

    extern Vision::vision_targeting* vision;

    struct turret_meta {
        double turret_set_point;
        double hood_set_point;
    };

    extern state_controller<turret_meta>* turret_state_controller;

    extern state* manual;
    extern state* set_point;
    extern state* auto_aim;
    extern state* ready;

    extern state_controller<bool>* shooter_state_controller;

    extern state* rest;
    extern state* spin_up;
    extern state* fire;
    extern state* walk;
    extern state* zero_dick;
}

#endif //VEX_U_2018_V5_SHOOTER_H
