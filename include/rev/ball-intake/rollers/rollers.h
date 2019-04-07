#ifndef VEX_U_2018_V5_ROLLERS_H
#define VEX_U_2018_V5_ROLLERS_H

#include "rev/rev.h"
#include "afr-lib/scheduled.h"

#include "afr-vexu-lib/base-commandable/motor_commandable.h"

#include "afr-vexu-lib/base-readable/adi_digital_readable.h"
#include "afr-vexu-lib/base-readable/digital_debounce.h"

namespace AFR::VexU::Rev::BallIntake::Rollers{

    const scheduled_update_t UPDATE_PERIOD = 10;

    const bool DIRECTION = false;
    const uint8_t DEBOUNCE_THRESHOLD = 5;

    void init();
    void destroy();

    extern BaseCommandable::motor_commandable* left_motor;
    extern BaseCommandable::motor_commandable* right_motor;

    extern BaseReadable::adi_digital_readable* limit_switch;
    extern BaseReadable::digital_debounce* debounce;
}

#endif //VEX_U_2018_V5_ROLLERS_H
