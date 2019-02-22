//
// Created by aamhi on 2/12/2019.
//

#ifndef VEX_U_2018_V5_SHOOTER_H
#define VEX_U_2018_V5_SHOOTER_H

#include "afr-vexu-lib/scheduled.h"
#include "afr-vexu-lib/subsystem_controller.h"

namespace AFR::VexU::Robot2::Shooter{

    const scheduled_update_t LOADER_UPDATE_PERIOD = 10;
    const scheduled_update_t SHOOTER_UPDATE_PERIOD = 10;
    const scheduled_update_t AUTO_AIM_UPDATE_PERIOD = 10;

    const int HOOD_TOLERANCE = 10;
    const int HOOD_VOLTAGE = 6000;
    const double HOOD_ENCODER_SCALING = 1.0;
    const int HOOD_ENCODER_LIMIT = 1300;

    const int TURRET_TOLERANCE = 10;
    const int TURRET_VOLTAGE = 6000;
    const double TURRET_ENCODER_SCALING = 1.0;
    const int TURRET_ENCODER_LIMIT = 4000;

    const unsigned int FLYWHEEL_SPEED 		= 6000;
    const double P_TERM 					= 100;
    const double I_TERM 					= 1;
    const double D_TERM 					= 0;
    const short MIN_I_TERM 				= -6000;
    const short MAX_I_TERM 				= 6000;
    const unsigned int FLYWHEEL_TOLERANCE 	= 100;


    const scheduled_update_t LOADER_STOP_TIME = 250;
    const scheduled_update_t AUTO_AIM_DELAY = 250;
//    const scheduled_update_t START_BACK_LEFT_MOTOR_UPDATE_PERIOD = 10;
//    const scheduled_update_t START_BACK_RIGHT_MOTOR_UPDATE_PERIOD = 10;


    extern subsystem_controller* shooter_subsystem;

    void init();

    void destroy();
}

#endif //VEX_U_2018_V5_SHOOTER_H
