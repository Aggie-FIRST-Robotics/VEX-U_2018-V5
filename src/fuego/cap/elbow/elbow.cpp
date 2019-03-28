#include "fuego/cap/elbow/elbow.h"
#include "fuego/fuego.h"

namespace AFR::VexU::Fuego::Cap::Elbow{

    BaseCommandable::motor_commandable* elbow_motor = nullptr;

    BaseReadable::adi_digital_readable* elbow_limit_switch = nullptr;
    BaseReadable::motor_encoder_readable* elbow_encoder = nullptr;

    BaseAction::pid_action<double, int16_t>* elbow_pid_controller = nullptr;
//    BaseAction::zero_encoder_action<bool, double, int16_t>* zero_action = nullptr;

    void init(){
        elbow_motor = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, ELBOW_MOTOR_PORT, ELBOW_GEARSET,
                 ELBOW_DIRECTION,ELBOW_BRAKE_MODE, "elbow_motor");

        elbow_limit_switch = new BaseReadable::adi_digital_readable
                (ELBOW_LIMIT_SWITCH_PORT, "elbow_limit_switch");

        elbow_encoder = new BaseReadable::motor_encoder_readable
                (ELBOW_MOTOR_PORT, ENCODER_SCALING, "elbow_encoder");

        elbow_pid_controller = new BaseAction::pid_action< double, int16_t >
                (UPDATE_PERIOD, P_TERM, I_TERM, D_TERM, MIN_VALUE, MAX_VALUE,
                 MIN_I_TERM, MAX_I_TERM, 0, 0, 0, "elbow_pid_controller");

//        zero_action = new BaseAction::zero_encoder_action< bool, double, int16_t >
//                (std::function<bool()>([](){ return limit_switch->is_pressed();}),
//                 encoder, true, -12000, pid_controller, "elbow zero encoder action");

    }

    void destroy(){
        delete elbow_motor;
        delete elbow_limit_switch;
        delete elbow_encoder;
        delete elbow_pid_controller;
//        delete zero_action;
    }
}
