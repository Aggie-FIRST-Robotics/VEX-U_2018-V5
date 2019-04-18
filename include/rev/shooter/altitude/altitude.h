#ifndef VEX_U_2018_V5_ALTITUDE_H
#define VEX_U_2018_V5_ALTITUDE_H

#include "rev/rev.h"
#include "afr-lib/scheduled.h"

#include "afr-vexu-lib/base-commandable/motor_commandable.h"

#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"
#include "afr-vexu-lib/base-readable/controller_readable.h"

#include "afr-vexu-lib/base-action/pid_action.h"

namespace AFR::VexU::Rev::Shooter::Altitude{

    const scheduled_update_t UPDATE_PERIOD = 10;

    const double ENCODER_LIMIT = 100;

    /////Motor
    const bool DIRECTION = false;

    /////PID Controller
    const double P_VALUE = 200;
    const double I_VALUE = 0;
    const double D_VALUE = 0;
    const int16_t MAX_VOLTAGE = 12000;
    const int16_t MIN_VOLTAGE = -12000;
    const int16_t MAX_I_VAL = 12000;
    const int16_t MIN_I_VAL = 12000;
    const int16_t OFFSET = 0;
    const int16_t DISABLED_VALUE = 0;
    const double TARGET = 0;

    /////Encoder
    const double ENCODER_SCALING = 1.0;

    void init();
    void destroy();

    extern BaseCommandable::motor_commandable* motor;
    extern BaseReadable::motor_encoder_readable* encoder;
    extern BaseAction::pid_action<double,int16_t>* pid;
}

#endif //VEX_U_2018_V5_ALTITUDE_H
