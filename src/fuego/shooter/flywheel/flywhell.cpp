
#include "fuego/shooter/flywheel/flywheel.h"
#include "fuego/fuego.h"

namespace AFR::VexU::Fuego::Shooter::Flywheel{

    BaseCommandable::motor_commandable* left_motor = nullptr;
    BaseCommandable::motor_commandable* right_motor = nullptr;
    BaseReadable::motor_encoder_readable* encoder = nullptr;
    BaseReadable::averager<double>* avg_speed = nullptr;
    BaseAction::pid_action<double, int16_t >* pid_controller = nullptr;


    void init(){
        left_motor = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, FLYWHEEL_LEFT_PORT, FLYWHEEL_GEARSET, DIRECTION,FLYWHEEL_BRAKE_MODE, "left flywheel motor");

        right_motor = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, FLYWHEEL_RIGHT_PORT, FLYWHEEL_GEARSET, !DIRECTION,FLYWHEEL_BRAKE_MODE, "right flywheel motor");

        encoder = new BaseReadable::motor_encoder_readable
                (FLYWHEEL_LEFT_PORT, ENCODER_SCALING, "flywheel encoder");

        avg_speed = new BaseReadable::averager<double>
                ([](){return encoder->get_scaled_velocity();}, AVERAGING_WIDTH, "flywheel encoder averager");


        pid_controller = new BaseAction::pid_action< double, int16_t >
                (UPDATE_PERIOD, P_TERM, I_TERM, D_TERM, MIN_VALUE, MAX_VALUE, MIN_I_TERM, MAX_I_TERM, 0, 0, SPEED, "flywheel PID controller");

    }

    void destroy(){
        delete left_motor;
        delete right_motor;
        delete encoder;
        delete avg_speed;
        delete pid_controller;
    }
}
