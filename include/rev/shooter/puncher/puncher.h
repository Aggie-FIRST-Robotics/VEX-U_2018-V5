#ifndef VEX_U_2018_V5_PUNCHER_H
#define VEX_U_2018_V5_PUNCHER_H

#include "rev/rev.h"
#include "afr-lib/scheduled.h"

#include "afr-vexu-lib/base-commandable/motor_commandable.h"

#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"
#include "afr-vexu-lib/base-readable/adi_digital_readable.h"

#include "afr-vexu-lib/base-action/dead_band_action.h"

namespace AFR::VexU::Rev::Shooter::Puncher{

    const scheduled_update_t UPDATE_PERIOD = 10;

    //Motor
    const bool DIRECTION             = false;

    //Encoder
    const double ENCODER_SCALING     = 1;

    //Dead Band
    const double INITIAL_TARGET      = 0;
    const double TOLERANCE           = 300;
    const int16_t MAX_VOLTAGE        = 12000;
    const int16_t MIN_VOLTAGE        = -12000;

    void init();
    void destroy();

    extern BaseCommandable::motor_commandable* motor;
    extern BaseReadable::motor_encoder_readable* encoder;
    extern BaseReadable::adi_digital_readable* limit_switch;
    extern BaseAction::dead_band_action<double, int16_t>* dead_band;

}

#endif //VEX_U_2018_V5_PUNCHER_H
