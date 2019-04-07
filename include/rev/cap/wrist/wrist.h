#ifndef VEX_U_2018_V5_WRIST_H
#define VEX_U_2018_V5_WRIST_H

#include "rev/rev.h"
#include "afr-lib/scheduled.h"

#include "afr-vexu-lib/base-commandable/motor_commandable.h"

#include "afr-vexu-lib/base-readable/adi_digital_readable.h"
#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"

#include "afr-vexu-lib/base-action/zero_encoder_action.h"
#include "afr-vexu-lib/base-action/pid_action.h"

namespace AFR::VexU::Rev::Cap::Wrist{

    const scheduled_update_t UPDATE_PERIOD = 10;

    const bool WRIST_DIRECTION = true;
    const bool INTAKE_DIRECTION = false;

    const double ENCODER_SCALING = 1;

    const double INITIAL_TARGET            = 0;
    const double P_TERM 					= 50;
    const double I_TERM 					= 0;
    const double D_TERM 					= 0;
    const short MIN_I_TERM 				    = -12000;
    const short MAX_I_TERM 				    = 12000;
    const short MAX_VALUE                  = 12000;
    const short MIN_VALUE                  = -12000;

    void init();
    void destroy();

    extern BaseCommandable::motor_commandable* flipping_motor;
    extern BaseCommandable::motor_commandable* intake_motor;

    extern BaseReadable::adi_digital_readable* limit_switch;
    extern BaseReadable::motor_encoder_readable* encoder;

    extern BaseAction::pid_action<double, int16_t>* pid_controller;
}

#endif //VEX_U_2018_V5_WRIST_H
