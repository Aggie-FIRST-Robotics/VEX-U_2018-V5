#include "fuego/cap/arm/arm.h"

namespace AFR::VexU::Fuego::Cap::Arm{

    BaseCommandable::motor_commandable* left_arm_motor = nullptr;
    BaseCommandable::motor_commandable* right_arm_motor = nullptr;

    BaseReadable::adi_digital_readable* arm_limit_switch = nullptr;
    BaseReadable::motor_encoder_readable* arm_encoder = nullptr;

    BaseAction::pid_action<double, int16_t>* arm_pid_controller = nullptr;
    BaseAction::zero_encoder_action<bool, double, int16_t>* zero_action = nullptr;

    void init(){
        using namespace BaseCommandable;
        using namespace BaseReadable;
        using namespace BaseAction;
        left_arm_motor = new motor_commandable
                (UPDATE_PERIOD, SHOULDER_LEFT_MOTOR_PORT, SHOULDER_GEARSET,
                 SHOULDER_DIRECTION,SHOULDER_BRAKE_MODE, "left_arm_motor");

        right_arm_motor = new motor_commandable
                (UPDATE_PERIOD, SHOULDER_RIGHT_MOTOR_PORT, SHOULDER_GEARSET,
                !SHOULDER_DIRECTION,SHOULDER_BRAKE_MODE, "right_arm_motor");

        arm_limit_switch = new adi_digital_readable
                (SHOULDER_LIMIT_SWITCH_PORT, "arm_limit_switch");

        arm_encoder = new motor_encoder_readable
                (SHOULDER_LEFT_MOTOR_PORT, ENCODER_SCALING, "arm_encoder");

        arm_pid_controller = new pid_action< double, int16_t >
                (UPDATE_PERIOD, P_TERM, I_TERM, D_TERM, MIN_VALUE, MAX_VALUE,
                MIN_I_TERM, MAX_I_TERM, 0, 0, 0, "arm_pid_controller");

        zero_action = new zero_encoder_action<bool, double, int16_t>{std::function<bool()>([](){ return limit_switch->is_pressed();}),
                encoder, true, -12000, pid_controller, "shoulder zero encoder action"};

    }

    void destroy(){
        delete left_arm_motor;
        delete right_arm_motor;
        delete arm_limit_switch;
        delete arm_encoder;
        delete arm_pid_controller;
        delete zero_action;
    }
}
