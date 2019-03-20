
#include "fuego/cap/shoulder/shoulder.h"
#include "fuego/fuego.h"

namespace AFR::VexU::Fuego::Cap::Shoulder{

    BaseCommandable::motor_commandable* left_motor = nullptr;
    BaseCommandable::motor_commandable* right_motor = nullptr;

    BaseReadable::adi_digital_readable* limit_switch = nullptr;
    BaseReadable::motor_encoder_readable* encoder = nullptr;

    BaseAction::pid_action<double, int16_t>* pid_controller = nullptr;
    BaseAction::zero_encoder_action<bool, double, int16_t>* zero_action = nullptr;

    void init(){
        left_motor = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, SHOULDER_LEFT_MOTOR_PORT, SHOULDER_GEARSET,
                 SHOULDER_DIRECTION,SHOULDER_BRAKE_MODE, "left shoulder motor");

        right_motor = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, SHOULDER_RIGHT_MOTOR_PORT, SHOULDER_GEARSET,
                !SHOULDER_DIRECTION,SHOULDER_BRAKE_MODE, "right shoulder motor");

        limit_switch = new BaseReadable::adi_digital_readable
                (SHOULDER_LIMIT_SWITCH_PORT, "shoulder limit switch");

        encoder = new BaseReadable::motor_encoder_readable
                (SHOULDER_LEFT_MOTOR_PORT, ENCODER_SCALING, "shoulder encoder");

        pid_controller = new BaseAction::pid_action< double, int16_t >
                (UPDATE_PERIOD, P_TERM, I_TERM, D_TERM, MIN_VALUE, MAX_VALUE,
                MIN_I_TERM, MAX_I_TERM, 0, 0, 0, "shoulder PID controller");

        zero_action = new BaseAction::zero_encoder_action< bool, double, int16_t >
                (std::function<bool()>([](){ return limit_switch->is_pressed();}),
                encoder, true, -12000, pid_controller, "shoulder zero encoder action");

    }

    void destroy(){
        delete left_motor;
        delete right_motor;
        delete limit_switch;
        delete encoder;
        delete pid_controller;
        delete zero_action;
    }
}
