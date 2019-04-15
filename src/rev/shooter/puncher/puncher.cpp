
#include "rev/shooter/puncher/puncher.h"

namespace AFR::VexU::Rev::Shooter::Puncher{

    BaseCommandable::motor_commandable* motor = nullptr;
    BaseReadable::motor_encoder_readable* encoder = nullptr;
    BaseReadable::adi_digital_readable* limit_switch = nullptr;
    BaseAction::dead_band_action<double, int16_t>* dead_band = nullptr;

    void init(){
        motor = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, PUNCHER_MOTOR_PORT, PUNCHER_GEARSET, !DIRECTION, PUNCHER_BRAKE_MODE, "puncher motor");

        encoder = new BaseReadable::motor_encoder_readable
                (PUNCHER_MOTOR_PORT, ENCODER_SCALING, "puncher encoder");

        limit_switch = new BaseReadable::adi_digital_readable
                (PUNCHER_LIMIT_SWITCH_PORT, "puncher limit switch");

        dead_band = new BaseAction::dead_band_action<double, int16_t>
                (UPDATE_PERIOD, INITIAL_TARGET, TOLERANCE, MAX_VOLTAGE, MIN_VOLTAGE, "puncher dead band action");
    }

    void destroy(){
        delete motor;
        delete encoder;
        delete limit_switch;
        delete dead_band;
    }
}
