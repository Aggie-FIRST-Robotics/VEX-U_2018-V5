#ifndef VEX_U_2018_V5_HOOD_H
#define VEX_U_2018_V5_HOOD_H

#include "fuego/fuego.h"
#include "afr-lib/scheduled.h"

#include "afr-vexu-lib/base-commandable/motor_commandable.h"

#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"
#include "afr-vexu-lib/base-readable/controller_readable.h"

#include "afr-vexu-lib/base-action/pid_action.h"
#include "afr-vexu-lib/base-action/bounded_value_action.h"

namespace AFR::VexU::Fuego::Shooter::Hood{

    const scheduled_update_t UPDATE_PERIOD = 10;

    const bool DIRECTION = true;
    const int AUTO_AIM_TOLERANCE = 200;
    const int MAX_VOLTAGE = 12000;
    const int MIN_VOLTAGE = -12000;
    const double ENCODER_SCALING = 1.0;
    const int ENCODER_LIMIT = 1300;
    const double PID_P = 50;
    const double PID_I = 20;
    const double PID_D = 0;

    void init();
    void destroy();

    extern BaseCommandable::motor_commandable* motor;
    extern BaseReadable::motor_encoder_readable* encoder;
    extern BaseAction::pid_action<double,double>* pid;
    extern BaseAction::bounded_value_action< double, int32_t ,int16_t >* follow_stick;
}

#endif //VEX_U_2018_V5_HOOD_H
