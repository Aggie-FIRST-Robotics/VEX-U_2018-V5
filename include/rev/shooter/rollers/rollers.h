#ifndef VEX_U_2018_V5_ROLLERS_H
#define VEX_U_2018_V5_ROLLERS_H

#include "rev/rev.h"
#include "afr-lib/scheduled.h"

#include "afr-vexu-lib/base-commandable/motor_commandable.h"

#include "afr-vexu-lib/base-readable/adi_analog_readable.h"
#include "afr-vexu-lib/base-readable/digital_debounce.h"
#include "afr-vexu-lib/base-readable/adi_digital_readable.h"
#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"

namespace AFR::VexU::Rev::Shooter::Rollers{

    const scheduled_update_t UPDATE_PERIOD = 10;

    const bool DIRECTION = false;
    const uint8_t DEBOUNCE_THRESHOLD = 5;

    const double ENCODER_SCALING = 1;

    void init();
    void destroy();

    extern BaseCommandable::motor_commandable* front_motor;
    extern BaseCommandable::motor_commandable* top_motor;
    extern BaseReadable::motor_encoder_readable* top_encoder;

    extern BaseReadable::adi_analog_readable* cup_sensor;
    extern BaseReadable::adi_digital_readable* limit_switch;
}

#endif //VEX_U_2018_V5_ROLLERS_H
