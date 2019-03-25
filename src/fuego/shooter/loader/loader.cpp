
#include "fuego/shooter/loader/loader.h"
#include "fuego/fuego.h"

namespace AFR::VexU::Fuego::Shooter::Loader{

    BaseCommandable::motor_commandable* motor = nullptr;
    BaseReadable::motor_encoder_readable* encoder = nullptr;
    BaseAction::dead_band_action<double, int16_t>* dead_band = nullptr;

    void init(){
        motor = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, LOADER_MOTOR_PORT, LOADER_GEARSET, DIRECTION, LOADER_BRAKE_MODE, "loader motor");

        encoder = new BaseReadable::motor_encoder_readable
                (LOADER_MOTOR_PORT, ENCODER_SCALING, "loader encoder");

        dead_band = new BaseAction::dead_band_action<double, int16_t>
                (UPDATE_PERIOD, INITIAL_TARGET, TOLERANCE, MAX_VOLTAGE, MIN_VOLTAGE, "Loader dead band action");
    }

    void destroy(){
        delete motor;
        delete encoder;
        delete dead_band;
    }
}
