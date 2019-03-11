//
// Created by aamhi on 2/12/2019.
//

#ifndef VEX_U_2018_V5_SHOOTER_H
#define VEX_U_2018_V5_SHOOTER_H

#include "afr-lib/scheduled.h"
#include "afr-lib/state_controller.h"
#include "fuego/fuego.h"

namespace AFR::VexU::Fuego::Shooter{

    const scheduled_update_t LOADER_UPDATE_PERIOD = 10;
    const scheduled_update_t SHOOTER_UPDATE_PERIOD = 10;
    const scheduled_update_t AUTO_AIM_UPDATE_PERIOD = 10;

    /////FLYWHEEL
    const bool FLYWHEEL_DIRECTION          = false;
    const double FLYWHEEL_ENCODER_SCALING  = 1;
    const size_t FLYWHEEL_AVERAGING_WIDTH  = 10;
    const unsigned int FLYWHEEL_SPEED 		= 2000;
    const double P_TERM 					= 100;
    const double I_TERM 					= 50;
    const double D_TERM 					= 0;
    const short MIN_I_TERM 				    = -12000;
    const short MAX_I_TERM 				    = 12000;
    const unsigned int FLYWHEEL_TOLERANCE 	= 800;

    /////LOADER
    const bool LOADER_DIRECTION             = false;
    const double LOADER_ENCODER_SCALING     = 1;
    const double LOADER_FIRE_TARGET         = 500;
    const double LOADER_WALK_TARGET         = -500;
    const double LOADER_TOLERANCE           = 100;
    const int16_t LOADER_MAX_VOLTAGE        = 12000;

    /////HOOD
    const bool HOOD_DIRECTION = false;
    const int AUTO_AIM_HOOD_TOLERANCE = 10;
    const int HOOD_MAX_VOLTAGE = 6000;
    const double HOOD_ENCODER_SCALING = 1.0;
    const int HOOD_ENCODER_LIMIT = 1300;

    /////TURRET
    const bool TURRET_DIRECTION = false;
    const int AUTO_AIM_TURRET_TOLERANCE = 10;
    const int TURRET_MAX_VOLTAGE = 6000;
    const double TURRET_ENCODER_SCALING = 1.0;
    const int TURRET_ENCODER_LIMIT = 3200;

    void init();

    void destroy();
}

#endif //VEX_U_2018_V5_SHOOTER_H
