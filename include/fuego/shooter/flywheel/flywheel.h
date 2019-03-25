#ifndef VEX_U_2018_V5_FLYWHEEL_H
#define VEX_U_2018_V5_FLYWHEEL_H

#include "fuego/fuego.h"
#include "afr-lib/scheduled.h"

#include "afr-vexu-lib/base-commandable/motor_commandable.h"

#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"
#include "afr-vexu-lib/base-readable/averager.h"

#include "afr-vexu-lib/base-action/pid_action.h"

namespace AFR::VexU::Fuego::Shooter::Flywheel{

    const scheduled_update_t UPDATE_PERIOD = 10;

    const bool DIRECTION            = true;
    const double ENCODER_SCALING    = 1;
    const size_t AVERAGING_WIDTH    = 10;

    const unsigned int SPEED 		 = 560;
    const short MIN_VALUE           = 0;
    const short MAX_VALUE           = 12000;
    const double P_TERM 		     = 200;
    const double I_TERM             = 30;
    const double D_TERM             = 0;
    const short MIN_I_TERM          = -12000;
    const short MAX_I_TERM          = 12000;

    void init();
    void destroy();

    extern BaseCommandable::motor_commandable* left_motor;
    extern BaseCommandable::motor_commandable* right_motor;
    extern BaseReadable::motor_encoder_readable* encoder;
    extern BaseReadable::averager<double>* avg_speed;
    extern BaseAction::pid_action<double, int16_t>* pid_controller;
}

#endif //VEX_U_2018_V5_FLYWHEEL_H
