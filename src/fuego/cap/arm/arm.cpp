#include "fuego/cap/arm/arm.h"

namespace AFR::VexU::Fuego::Cap::Arm{

    BaseCommandable::motor_commandable* left_motor = nullptr;
    BaseCommandable::motor_commandable* right_motor = nullptr;

    BaseReadable::adi_digital_readable* limit_switch = nullptr;
    BaseReadable::motor_encoder_readable* encoder = nullptr;
    BaseReadable::digital_debounce* debounce = nullptr;

    BaseAction::pid_action<double, int16_t>* pid_controller = nullptr;
    BaseAction::zero_encoder_action<bool, int16_t>* zero_action = nullptr;

    void init(){

        left_motor = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, SHOULDER_LEFT_MOTOR_PORT, SHOULDER_GEARSET,
                 DIRECTION,SHOULDER_BRAKE_MODE, "left_arm_motor");

        right_motor = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, SHOULDER_RIGHT_MOTOR_PORT, SHOULDER_GEARSET,
                !DIRECTION,SHOULDER_BRAKE_MODE, "right_arm_motor");

        limit_switch = new BaseReadable::adi_digital_readable
                (SHOULDER_LIMIT_SWITCH_PORT, "arm_limit_switch");

        encoder = new BaseReadable::motor_encoder_readable
                (SHOULDER_LEFT_MOTOR_PORT, ENCODER_SCALING, "arm_encoder");

        debounce = new BaseReadable::digital_debounce
                (std::function<bool()>([](){ return limit_switch->is_pressed(); }),5,"arm debounce");

        pid_controller = new BaseAction::pid_action< double, int16_t >
                (UPDATE_PERIOD, P_TERM, I_TERM, D_TERM, MIN_VALUE, MAX_VALUE,
                MIN_I_TERM, MAX_I_TERM, 0, 0, 0, "arm_pid_controller");

        zero_action = new BaseAction::zero_encoder_action<bool, int16_t>
                {std::function<bool()>([](){ return limit_switch->is_pressed();}), encoder, true, -9000, 0};

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
