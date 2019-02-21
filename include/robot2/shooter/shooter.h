//
// Created by aamhi on 2/12/2019.
//

#ifndef VEX_U_2018_V5_SHOOTER_H
#define VEX_U_2018_V5_SHOOTER_H

#include "afr-vexu-lib/scheduled.h"
#include "afr-vexu-lib/subsystem_controller.h"

namespace AFR::VexU::Robot::Shooter{
    const scheduled_update_t START_UPDATE_PERIOD = 10;

//    const scheduled_update_t START_FRONT_LEFT_MOTOR_UPDATE_PERIOD = 10;
    const scheduled_update_t ELEVATION_UPDATE_PERIOD = 10;
    const scheduled_update_t SPINNER_UPDATE_PERIOD = 10;
    const scheduled_update_t FLYWHEEL_UPDATE_PERIOD = 10;
    const double AZIMUTH_THRESHOLD = 360;
    const double FLYWHEEL_THRESHOLD = 360;
//    const scheduled_update_t START_BACK_LEFT_MOTOR_UPDATE_PERIOD = 10;
//    const scheduled_update_t START_BACK_RIGHT_MOTOR_UPDATE_PERIOD = 10;

    extern subsystem_controller* shooter_subsystem;

    void init();

    void destroy();
}

#endif //VEX_U_2018_V5_SHOOTER_H
