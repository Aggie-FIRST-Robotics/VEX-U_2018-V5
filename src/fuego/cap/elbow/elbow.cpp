#include "fuego/cap/elbow/elbow.h"
#include "fuego/fuego.h"

namespace AFR::VexU::Fuego::Cap::Elbow{

    BaseCommandable::motor_commandable* motor = nullptr;

    BaseReadable::adi_digital_readable* limit_switch = nullptr;
    BaseReadable::motor_encoder_readable* encoder = nullptr;
    BaseReadable::digital_debounce* debounce = nullptr;

    BaseAction::pid_action<double, int16_t>* pid_controller = nullptr;
    BaseAction::zero_encoder_action<bool, int16_t>* zero_action = nullptr;

    void init(){
        //memes
        motor = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, ELBOW_MOTOR_PORT, ELBOW_GEARSET,
                 DIRECTION,ELBOW_BRAKE_MODE, "elbow_motor");

        limit_switch = new BaseReadable::adi_digital_readable
                (ELBOW_LIMIT_SWITCH_PORT, "elbow_limit_switch");

        encoder = new BaseReadable::motor_encoder_readable
                (ELBOW_MOTOR_PORT, ENCODER_SCALING, "elbow_encoder");

        debounce = new BaseReadable::digital_debounce
                (std::function<bool()>([](){ return limit_switch->is_pressed(); }),5,"elbow debounce");

        pid_controller = new BaseAction::pid_action< double, int16_t >
                (UPDATE_PERIOD, P_TERM, I_TERM, D_TERM, MIN_VALUE, MAX_VALUE,
                 MIN_I_TERM, MAX_I_TERM, 0, 0, 0, "elbow_pid_controller");

        zero_action = new BaseAction::zero_encoder_action< bool, int16_t >
                (std::function<bool()>([](){ return limit_switch->is_pressed();}), encoder, true, -5000, -100);
    }

    void destroy(){
        delete motor;
        delete limit_switch;
        delete encoder;
        delete pid_controller;
        delete zero_action;
    }
}
