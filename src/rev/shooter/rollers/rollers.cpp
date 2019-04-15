#include "rev/shooter/rollers/rollers.h"

namespace AFR::VexU::Rev::Shooter::Rollers{

    BaseCommandable::motor_commandable* front_motor = nullptr;
    BaseCommandable::motor_commandable* top_motor = nullptr;

    BaseReadable::adi_analog_readable* cup_sensor = nullptr;

    void init(){

        front_motor = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, FRONT_INTAKE_MOTOR_PORT, FRONT_INTAKE_GEARSET,
                 !DIRECTION, FRONT_INTAKE_BRAKE_MODE, "front intake motor");

        top_motor = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, TOP_INTAKE_MOTOR_PORT, TOP_INTAKE_GEARSET,
                DIRECTION, TOP_INTAKE_BRAKE_MODE, "top intake motor");

        cup_sensor = new BaseReadable::adi_analog_readable
                (CUP_SENSOR_PORT, "roller sensor");

    }

    void destroy(){
        delete front_motor;
        delete top_motor;
        delete cup_sensor;
    }
}
