#ifndef VEX_U_2018_V5_ELBOW_H
#define VEX_U_2018_V5_ELBOW_H

#include "fuego/fuego.h"
#include "afr-lib/scheduled.h"

#include "afr-vexu-lib/base-commandable/motor_commandable.h"

#include "afr-vexu-lib/base-readable/adi_digital_readable.h"
#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"

#include "afr-vexu-lib/base-action/zero_encoder_action.h"
#include "afr-vexu-lib/base-action/pid_action.h"

namespace AFR::VexU::Fuego::Cap::Elbow{

    const scheduled_update_t UPDATE_PERIOD = 10;

    const bool DIRECTION = true;

    const double ENCODER_SCALING = 1;

    const double P_TERM 					= 50;
    const double I_TERM 					= 0;
    const double D_TERM 					= 0;
    const int16_t MIN_I_TERM 				= -12000;
    const int16_t MAX_I_TERM 				= 12000;
    const int16_t MAX_VALUE                 = 12000;
    const int16_t MIN_VALUE                 = -12000;

    void init();
    void destroy();

    extern BaseCommandable::motor_commandable* motor;

    extern BaseReadable::adi_digital_readable* limit_switch;
    extern BaseReadable::motor_encoder_readable* encoder;

    extern BaseAction::pid_action<double, int16_t>* pid_controller;
    extern BaseAction::zero_encoder_action<bool, double, int16_t>* zero_action;
}

#endif //VEX_U_2018_V5_ELBOW_H
