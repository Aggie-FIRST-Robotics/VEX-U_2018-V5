#ifndef VEX_U_2018_V5_TURRET_H
#define VEX_U_2018_V5_TURRET_H

#include "fuego/fuego.h"
#include "afr-lib/scheduled.h"

#include "afr-vexu-lib/base-commandable/motor_commandable.h"

#include "afr-vexu-lib/base-readable/adi_digital_readable.h"
#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"

#include "afr-vexu-lib/base-action/dead_band_action.h"
#include "afr-vexu-lib/base-action/bounded_value_action.h"

namespace AFR::VexU::Fuego::Shooter::Turret{

    const scheduled_update_t UPDATE_PERIOD = 10;

    const bool DIRECTION = false;
    const int AUTO_AIM_TOLERANCE = 200;
    const int MAX_VOLTAGE = 12000;
    const int MIN_VOLTAGE = -12000;
    const double ENCODER_SCALING = 1.0;
    const int ENCODER_LIMIT = 3100;

    void init();
    void destroy();

    extern BaseCommandable::motor_commandable* motor;
    extern BaseReadable::motor_encoder_readable* encoder;
    extern BaseAction::dead_band_action<double,double>* dead_band;
    extern BaseAction::bounded_value_action< double, int32_t ,int16_t >* follow_stick;
}

#endif //VEX_U_2018_V5_SHOULDER_H
