#ifndef VEX_U_2018_V5_BASE_H
#define VEX_U_2018_V5_BASE_H

#include "rev/rev.h"
#include "afr-lib/scheduled.h"

#include "afr-vexu-lib/base-commandable/motor_commandable.h"

#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"
#include "afr-vexu-lib/base-readable/averager.h"

namespace AFR::VexU::Rev::Drive::Base{

    const scheduled_update_t UPDATE_PERIOD = 10;

    const bool DIRECTION = false;

    const double ENCODER_SCALING = 1.0;
    const size_t AVERAGER_SAMPLES = 10;

    void init();
    void destroy();

    extern BaseCommandable::motor_commandable* left_motor_1;
    extern BaseCommandable::motor_commandable* left_motor_2;
    extern BaseCommandable::motor_commandable* left_motor_3;
    extern BaseCommandable::motor_commandable* right_motor_1;
    extern BaseCommandable::motor_commandable* right_motor_2;
    extern BaseCommandable::motor_commandable* right_motor_3;

    extern BaseReadable::motor_encoder_readable* left_motor_1_encoder;
    extern BaseReadable::motor_encoder_readable* left_motor_2_encoder;
    extern BaseReadable::motor_encoder_readable* left_motor_3_encoder;
    extern BaseReadable::motor_encoder_readable* right_motor_1_encoder;
    extern BaseReadable::motor_encoder_readable* right_motor_2_encoder;
    extern BaseReadable::motor_encoder_readable* right_motor_3_encoder;

    extern BaseReadable::averager<double>* right_encoder;
    extern BaseReadable::averager<double>* left_encoder;
}

#endif //VEX_U_2018_V5_BASE_H
