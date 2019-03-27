#include "fuego/drive/drive.h"
namespace AFR::VexU::Fuego::Drive{

    struct drive_meta {};

    /////Commandables
    BaseCommandable::motor_commandable* front_left_motor = nullptr;
    BaseCommandable::motor_commandable* front_right_motor = nullptr;
    BaseCommandable::motor_commandable* back_left_motor = nullptr;
    BaseCommandable::motor_commandable* back_right_motor = nullptr;

    /////State Controller
    state_controller<drive_meta>* drive_machine = nullptr;

    /////States
    state* manual = nullptr;

    /////Entry/Exit Functions
    std::function<void()> start_entry{};
    std::function<void()> start_exit{};

    /////Joystick Lambda
    std::function<int32_t()> DRIVE_SPEED = []() -> int32_t{ return (BaseReadable::driver_controller->get_analog(DRIVETRAIN_THROTTLE) * 12000) / 127; };
    std::function<int32_t()> DRIVE_TURN = []() -> int32_t{ return (BaseReadable::driver_controller->get_analog(DRIVETRAIN_TURN) * 12000) / 127; };

    void init(){
        /////Commandables
        front_left_motor = new BaseCommandable::motor_commandable
                {UPDATE_PERIOD, LEFT_RAIL_MOTOR_A_PORT, DRIVETRAIN_GEARSET, DIRECTION, DRIVETRAIN_BRAKE_MODE, "front_left_motor"};
        front_right_motor = new BaseCommandable::motor_commandable
                {UPDATE_PERIOD, LEFT_RAIL_MOTOR_B_PORT, DRIVETRAIN_GEARSET, !DIRECTION, DRIVETRAIN_BRAKE_MODE, "front_right_motor"};
        back_left_motor = new BaseCommandable::motor_commandable
                {UPDATE_PERIOD, RIGHT_RAIL_MOTOR_A_PORT, DRIVETRAIN_GEARSET, DIRECTION, DRIVETRAIN_BRAKE_MODE, "back_left_motor"};
        back_right_motor = new BaseCommandable::motor_commandable
                {UPDATE_PERIOD, RIGHT_RAIL_MOTOR_B_PORT, DRIVETRAIN_GEARSET, !DIRECTION, DRIVETRAIN_BRAKE_MODE, "back_right_motor"};

        drive_machine = new state_controller<drive_meta>(UPDATE_PERIOD,{},"drive state controller");



        manual = new state("manual");

        /////Start
            /////Entry/Exit Functions
            start_entry = []() -> void{
                front_left_motor->set_operation(std::function<int16_t()>([](){return DRIVE_SPEED() + DRIVE_TURN();}),drive_machine->get_name());
                front_right_motor->set_operation(std::function<int16_t()>([](){return DRIVE_SPEED() + DRIVE_TURN();}),drive_machine->get_name());
                back_left_motor->set_operation(std::function<int16_t()>([](){return DRIVE_SPEED() + DRIVE_TURN();}),drive_machine->get_name());
                back_right_motor->set_operation(std::function<int16_t()>([](){return DRIVE_SPEED() + DRIVE_TURN();}),drive_machine->get_name());
            };

            start_exit = []() -> void{};

            manual->set_on_state_entry(start_entry);
            manual->set_on_state_exit(start_exit);

        drive_machine->add_state(manual);

        drive_machine->set_state(manual);
    }

    void destroy(){
        delete(manual);
        delete(drive_machine);
    }
};
