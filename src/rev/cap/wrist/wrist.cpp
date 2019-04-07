
#include "rev/cap/wrist/wrist.h"

namespace AFR::VexU::Rev::Cap::Wrist{

    BaseCommandable::motor_commandable* flipping_motor = nullptr;
    BaseCommandable::motor_commandable* intake_motor = nullptr;

    BaseReadable::adi_digital_readable* limit_switch = nullptr;
    BaseReadable::motor_encoder_readable* encoder = nullptr;

    BaseAction::pid_action<double, int16_t>* pid_controller = nullptr;

    void init(){
        flipping_motor = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, WRIST_MOTOR_PORT, WRIST_GEARSET,
                 WRIST_DIRECTION,WRIST_BRAKE_MODE, "wrist_motor");

        intake_motor = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, CAP_INTAKE_MOTOR_PORT, CAP_INTAKE_GEARSET,
                INTAKE_DIRECTION,CAP_INTAKE_BRAKE_MODE, "wrist_intake_motor");

        limit_switch = new BaseReadable::adi_digital_readable
                (WRIST_LIMIT_SWITCH_PORT, "wrist_limit_switch");

        encoder = new BaseReadable::motor_encoder_readable
                (WRIST_MOTOR_PORT, ENCODER_SCALING, "wrist_encoder");

        pid_controller = new BaseAction::pid_action< double, int16_t >
                (UPDATE_PERIOD, P_TERM, I_TERM, D_TERM, MIN_VALUE, MAX_VALUE,
                MIN_I_TERM, MAX_I_TERM, 0, 0, INITIAL_TARGET, "wrist_pid_controller");
    }

    void destroy(){
        delete flipping_motor;
        delete intake_motor;
        delete limit_switch;
        delete encoder;
        delete pid_controller;
    }
}
