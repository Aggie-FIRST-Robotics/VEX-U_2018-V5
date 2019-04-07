#include "rev/drive/shifter/shifter.h"

namespace AFR::VexU::Rev::Drive::Shifter{

    BaseCommandable::motor_commandable* motor = nullptr;

    BaseReadable::motor_encoder_readable* encoder = nullptr;

    BaseAction::dead_band_action<double, int16_t>* dead_band = nullptr;

    void init(){

        motor = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, SHIFTER_MOTOR, SHIFTER_GEARSET,
                 DIRECTION,SHIFTER_BRAKE_MODE, "shifter motor");

        encoder = new BaseReadable::motor_encoder_readable
            (SHIFTER_MOTOR, ENCODER_SCALING, "shifter encoder");

        dead_band = new BaseAction::dead_band_action<double, int16_t>
                (UPDATE_PERIOD, INITIAL_TARGET, TOLERANCE, MAX_VOLTAGE, MIN_VOLTAGE, "shifter dead band action");
    }

    void destroy(){
        delete motor;
        delete encoder;
        delete dead_band;
    }
}
