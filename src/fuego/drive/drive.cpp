#include "fuego/drive/drive.h"
namespace AFR::VexU::Fuego::Drive{

    struct Drive_Meta {};

    /////Commandables
    BaseCommandable::motor_commandable* front_left_motor{};
    BaseCommandable::motor_commandable* front_right_motor{};
    BaseCommandable::motor_commandable* back_left_motor{};
    BaseCommandable::motor_commandable* back_right_motor{};

    /////State Controller
    state_controller<Drive_Meta>* drive_machine = nullptr;

    /////States
    state *start = nullptr;

    /////Entry/Exit Functions
    std::function<void()> start_entry{};
    std::function<void()> start_exit{};

    /////Joystick Lambda
    std::function<int32_t()> DRIVE_SPEED = []() -> int32_t{ return BaseReadable::driver_controller->get_analog(LEFT_DRIVE_STICK); };
    std::function<int32_t()> DRIVE_TURN = []() -> int32_t{ return BaseReadable::driver_controller->get_analog(RIGHT_DRIVE_STICK); };

    void init(){
        /////Commandables
        front_left_motor = new BaseCommandable::motor_commandable{DRIVE_UPDATE_PERIOD, BALL_INTAKE_MOTOR_PORT,
                                                                  BALL_INTAKE_GEARSET, false,
                                                                  BALL_INTAKE_BRAKE_MODE, "front_left_motor"};
        front_right_motor = new BaseCommandable::motor_commandable{DRIVE_UPDATE_PERIOD, BALL_INTAKE_MOTOR_PORT,
                                                                   BALL_INTAKE_GEARSET, false,
                                                                   BALL_INTAKE_BRAKE_MODE, "front_right_motor"};
        back_left_motor = new BaseCommandable::motor_commandable{DRIVE_UPDATE_PERIOD, BALL_INTAKE_MOTOR_PORT,
                                                                 BALL_INTAKE_GEARSET, false,
                                                                 BALL_INTAKE_BRAKE_MODE, "back_left_motor"};
        back_right_motor = new BaseCommandable::motor_commandable{DRIVE_UPDATE_PERIOD, BALL_INTAKE_MOTOR_PORT,
                                                                  BALL_INTAKE_GEARSET, false,
                                                                  BALL_INTAKE_BRAKE_MODE, "back_right_motor"};

        drive_machine = new state_controller<Drive_Meta>(UPDATE_PERIOD,{},"drive state controller");

        start = new state("start");

        /////Start
            /////Entry/Exit Functions
            start_entry = []() -> void{
                front_left_motor->set_value(static_cast<int16_t>(DRIVE_SPEED() + DRIVE_TURN()), start->get_name());
                front_left_motor->set_value(static_cast<int16_t>(DRIVE_SPEED() - DRIVE_TURN()), start->get_name());
                front_left_motor->set_value(static_cast<int16_t>(DRIVE_SPEED() + DRIVE_TURN()), start->get_name());
                front_left_motor->set_value(static_cast<int16_t>(DRIVE_SPEED() - DRIVE_TURN()), start->get_name());
            };

            start_exit = []() -> void{};

            start->set_on_state_entry(start_entry);
            start->set_on_state_exit(start_exit);

        drive_machine->add_state(start);

        drive_machine->set_state(start);
    }

    void destroy(){
        delete(start);

        delete(drive_machine);
    }
};
