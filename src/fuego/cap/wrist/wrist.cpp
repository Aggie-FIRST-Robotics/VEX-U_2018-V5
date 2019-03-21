
#include "fuego/cap/wrist/wrist.h"
#include "fuego/fuego.h"

namespace AFR::VexU::Fuego::Cap::Wrist{

    BaseCommandable::motor_commandable* wrist_motor = nullptr;
    BaseCommandable::motor_commandable* intake_motor = nullptr;

    BaseReadable::adi_digital_readable* limit_switch = nullptr;
    BaseReadable::motor_encoder_readable* encoder = nullptr;

    BaseAction::pid_action<double, int16_t>* pid_controller = nullptr;
    BaseAction::zero_encoder_action<bool, double, int16_t>* zero_action = nullptr;

    void init(){
        wrist_motor = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, WRIST_MOTOR_PORT, WRIST_GEARSET,
                 WRIST_DIRECTION,WRIST_BRAKE_MODE, "wrist motor");

        intake_motor = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, CAP_INTAKE_MOTOR_PORT, CAP_INTAKE_GEARSET,
                INTAKE_DIRECTION,CAP_INTAKE_BRAKE_MODE, "cap intake motor");

        limit_switch = new BaseReadable::adi_digital_readable
                (WRIST_LIMIT_SWITCH_PORT, "wrist limit switch");

        encoder = new BaseReadable::motor_encoder_readable
                (WRIST_MOTOR_PORT, ENCODER_SCALING, "wrist encoder");

        pid_controller = new BaseAction::pid_action< double, int16_t >
                (UPDATE_PERIOD, P_TERM, I_TERM, D_TERM, MIN_VALUE, MAX_VALUE,
                MIN_I_TERM, MAX_I_TERM, 0, 0, WRIST_FLIP_TARGET, "wrist PID controller");

//        zero_action = new BaseAction::zero_encoder_action< bool, double, int16_t >
//                (std::function<bool()>([](){ return limit_switch->is_pressed();}),
//                encoder, true, -12000, pid_controller, "wrist zero encoder action");
    }

    void destroy(){
        delete wrist_motor;
        delete intake_motor;
        delete limit_switch;
        delete encoder;
        delete pid_controller;
        delete zero_action;
    }
}
