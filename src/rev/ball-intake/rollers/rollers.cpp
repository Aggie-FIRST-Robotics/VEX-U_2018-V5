#include "rev/ball-intake/rollers/rollers.h"

namespace AFR::VexU::Rev::BallIntake::Rollers{

    BaseCommandable::motor_commandable* left_motor = nullptr;
    BaseCommandable::motor_commandable* right_motor = nullptr;

    BaseReadable::adi_digital_readable* limit_switch = nullptr;
    BaseReadable::digital_debounce* debounce = nullptr;

    void init(){

        left_motor = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, SHOULDER_LEFT_MOTOR_PORT, SHOULDER_GEARSET,
                 DIRECTION,SHOULDER_BRAKE_MODE, "left roller motor");

        right_motor = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, SHOULDER_RIGHT_MOTOR_PORT, SHOULDER_GEARSET,
                !DIRECTION,SHOULDER_BRAKE_MODE, "right roller motor");

        limit_switch = new BaseReadable::adi_digital_readable
                (SHOULDER_LIMIT_SWITCH_PORT, "roller switch");


        debounce = new BaseReadable::digital_debounce
                (std::function<bool()>([](){ return limit_switch->is_pressed(); }), DEBOUNCE_THRESHOLD ,"rollers debounce");

    }

    void destroy(){
        delete left_motor;
        delete right_motor;
        delete limit_switch;
    }
}
