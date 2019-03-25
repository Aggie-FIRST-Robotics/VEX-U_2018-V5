
#include "fuego/shooter/hood/hood.h"
#include "fuego/fuego.h"

namespace AFR::VexU::Fuego::Shooter::Hood{

    BaseCommandable::motor_commandable* motor = nullptr;
    BaseReadable::motor_encoder_readable* encoder = nullptr;
    BaseAction::dead_band_action<double,double>* dead_band = nullptr;
    BaseAction::bounded_value_action< double, int32_t ,int16_t >* follow_stick = nullptr;

    void init(){
        motor = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, HOOD_MOTOR_PORT, HOOD_GEARSET, DIRECTION, HOOD_BRAKE_MODE, "hood motor");

        encoder = new BaseReadable::motor_encoder_readable
                (HOOD_MOTOR_PORT, ENCODER_SCALING, "hood encoder");

        dead_band = new BaseAction::dead_band_action<double, double>
                (UPDATE_PERIOD, 0, AUTO_AIM_TOLERANCE, MAX_VOLTAGE, MIN_VOLTAGE, "hood auto aim action");

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
        delete dead_band;
        delete follow_stick;
    }
}
