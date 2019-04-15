
#include "rev/shooter/altitude/altitude.h"

namespace AFR::VexU::Rev::Shooter::Altitude{

    BaseCommandable::motor_commandable* motor = nullptr;
    BaseReadable::motor_encoder_readable* encoder = nullptr;
    BaseAction::pid_action<double,int16_t>* pid = nullptr;
    //memes

    void init(){
        motor = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, ALTITUDE_MOTOR_PORT, ALTITUDE_GEARSET, DIRECTION, ALTITUDE_BRAKE_MODE, "altitude motor");

        encoder = new BaseReadable::motor_encoder_readable
                (ALTITUDE_MOTOR_PORT, ENCODER_SCALING, "altitude encoder");

        pid = new BaseAction::pid_action<double,int16_t>
                (UPDATE_PERIOD, P_VALUE, I_VALUE, D_VALUE, MIN_VOLTAGE, MAX_VOLTAGE, MIN_I_VAL, MAX_I_VAL, 0, 0, 0, "altitude pid controller");

    }

    void destroy(){
        delete motor;
        delete encoder;
        delete pid;
    }
}
