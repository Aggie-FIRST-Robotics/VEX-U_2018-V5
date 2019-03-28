
#include "fuego/shooter/hood/hood.h"
#include "fuego/fuego.h"

namespace AFR::VexU::Fuego::Shooter::Hood{

    BaseCommandable::motor_commandable* motor = nullptr;
    BaseReadable::motor_encoder_readable* encoder = nullptr;
    BaseAction::pid_action<double,double>* pid = nullptr;
    BaseAction::bounded_value_action< double, int32_t ,int16_t >* follow_stick = nullptr;

    void init(){
        motor = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, HOOD_MOTOR_PORT, HOOD_GEARSET, DIRECTION, HOOD_BRAKE_MODE, "hood motor");

        encoder = new BaseReadable::motor_encoder_readable
                (HOOD_MOTOR_PORT, ENCODER_SCALING, "hood encoder");

        pid = new BaseAction::pid_action<double, double>
                (UPDATE_PERIOD, 100, 0, 0, MIN_VOLTAGE, MAX_VOLTAGE, MIN_VOLTAGE, MAX_VOLTAGE, 0, 0, 0, "hood auto aim action");

        follow_stick = new BaseAction::bounded_value_action< double, int32_t ,int16_t >
                (UPDATE_PERIOD, ENCODER_LIMIT,0, 0, 0,
                    std::function<int16_t(int32_t)>([](int32_t stick){return static_cast<int16_t >((12000/127)*stick);}),
                    std::function<int32_t()>([](){return BaseReadable::operator_controller->get_analog(HOOD_STICK);}),
                    std::function<double()>([](){return encoder->get_scaled_position();}),
                    "hood bounded value action");

    }

    void destroy(){
        delete motor;
        delete encoder;
        delete pid;
        delete follow_stick;
    }
}
