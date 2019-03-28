
#include "fuego/shooter/turret/turret.h"
#include "fuego/fuego.h"

namespace AFR::VexU::Fuego::Shooter::Turret{

    //memes
    BaseCommandable::motor_commandable* motor = nullptr;
    BaseReadable::motor_encoder_readable* encoder = nullptr;
    BaseAction::pid_action<double,double>* pid = nullptr;
    BaseAction::bounded_value_action< double, int32_t ,int16_t >* follow_stick = nullptr;

    void init(){
        motor = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, TURRET_MOTOR_PORT, TURRET_GEARSET, DIRECTION, TURRET_BRAKE_MODE, "turret motor");

        encoder = new BaseReadable::motor_encoder_readable
                (TURRET_MOTOR_PORT, ENCODER_SCALING, "turret encoder");

        pid = new BaseAction::pid_action<double, double>
                (UPDATE_PERIOD, 100, 0, 0, MIN_VOLTAGE, MAX_VOLTAGE, MIN_VOLTAGE, MAX_VOLTAGE, 0, 0, 0, "turret auto aim action");

        follow_stick = new BaseAction::bounded_value_action< double, int32_t ,int16_t >
                (UPDATE_PERIOD, ENCODER_LIMIT,0, 0, 0,
                 std::function<int16_t(int32_t)>([](int32_t stick){return static_cast<int16_t >((12000/127)*stick);}),
                 std::function<int32_t()>([](){return BaseReadable::operator_controller->get_analog(TURRET_STICK);}),
                 std::function<double()>([](){return encoder->get_scaled_position();}),
                 "turret bounded value action");
    }

    void destroy(){
        delete motor;
        delete encoder;
        delete pid;
        delete follow_stick;
    }
}
