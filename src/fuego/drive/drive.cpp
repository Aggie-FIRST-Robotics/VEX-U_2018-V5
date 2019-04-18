#include "fuego/drive/drive.h"
namespace AFR::VexU::Fuego::Drive{


    /////Commandables
    BaseCommandable::motor_commandable* front_left_motor = nullptr;
    BaseCommandable::motor_commandable* front_right_motor = nullptr;
    BaseCommandable::motor_commandable* back_left_motor = nullptr;
    BaseCommandable::motor_commandable* back_right_motor = nullptr;

    //Encoders
    BaseReadable::motor_encoder_readable* left_encoder = nullptr;
    BaseReadable::motor_encoder_readable* right_encoder = nullptr;

    //Auto drive controller
    AutoDrive::auto_drive* auto_drivetrain = nullptr;

    /////State Controller
    state_controller<drive_meta>* drive_machine = nullptr;

    /////States
    state* manual = nullptr;
    state* autonomous = nullptr;

    /////Entry/Exit Functions
    std::function<void(state*)> start_entry{};
    std::function<void(state*)> start_exit{};
    std::function<void(state*)> autonomous_entry{};
    std::function<void(state*)> autonomous_exit{};

    //sensor lambdas
    std::function<double()> gyro_lambda = []() -> double {
        serial->enqueue_write(ARDUINO_ID, 0, 0);
        return serial->arduino_table.read(1) * PI / 1800.0;
    };

    std::function<double()> left_encoder_lambda = []() -> double {
        return left_encoder->get_scaled_position() * TICKS_TO_IN;
    };

    std::function<double()> right_encoder_lambda = []() -> double {
        return right_encoder->get_scaled_position() * TICKS_TO_IN;
    };

    std::function<double()> left_encoder_vel_lambda = []() -> double {
        return left_encoder->get_scaled_velocity() * PROS_TO_IN_VEL;
    };

    std::function<double()> right_encoder_vel_lambda = []() -> double {
        return right_encoder->get_scaled_velocity() * PROS_TO_IN_VEL;
    };

    /////Joystick Lambda
    std::function<int32_t()> DRIVE_SPEED = []() -> int32_t { 
                std::cout << "Angle: " << gyro_lambda() << std::endl;
                std::cout << "Left encoder: " << left_encoder_lambda() << std::endl;
                std::cout << "Right encoder: " << right_encoder_lambda() << std::endl;
                std::cout << "Left encoder vel: " << left_encoder_vel_lambda() << std::endl;
                std::cout << "Right encoder vel: " << right_encoder_vel_lambda() << std::endl;
        return (BaseReadable::driver_controller->get_analog(DRIVETRAIN_THROTTLE) * 12000) / 127; 
    };
    std::function<int32_t()> DRIVE_TURN = []() -> int32_t{ return (BaseReadable::driver_controller->get_analog(DRIVETRAIN_TURN) * 12000) / 127; };

    void init(){
        /////Commandables
        front_left_motor = new BaseCommandable::motor_commandable
                {UPDATE_PERIOD, LEFT_RAIL_MOTOR_A_PORT, DRIVETRAIN_GEARSET, !DIRECTION, DRIVETRAIN_BRAKE_MODE, "front_left_motor"};
        back_left_motor = new BaseCommandable::motor_commandable
                {UPDATE_PERIOD, LEFT_RAIL_MOTOR_B_PORT, DRIVETRAIN_GEARSET, !DIRECTION, DRIVETRAIN_BRAKE_MODE, "front_right_motor"};
        front_right_motor = new BaseCommandable::motor_commandable
                {UPDATE_PERIOD, RIGHT_RAIL_MOTOR_A_PORT, DRIVETRAIN_GEARSET, DIRECTION, DRIVETRAIN_BRAKE_MODE, "back_left_motor"};
        back_right_motor = new BaseCommandable::motor_commandable
                {UPDATE_PERIOD, RIGHT_RAIL_MOTOR_B_PORT, DRIVETRAIN_GEARSET, DIRECTION, DRIVETRAIN_BRAKE_MODE, "back_right_motor"};

        left_encoder = new BaseReadable::motor_encoder_readable(LEFT_RAIL_MOTOR_A_PORT, 1.0, "left_encoder");
        right_encoder = new BaseReadable::motor_encoder_readable(RIGHT_RAIL_MOTOR_A_PORT, 1.0, "right_encoder");

        auto_drivetrain = new AutoDrive::auto_drive(FUEGO_WIDTH, 100, 0, 0, "auto_drivetrain");
        auto_drivetrain->set_gyro_function(gyro_lambda);
        auto_drivetrain->set_left_wheel_function(left_encoder_lambda);
        auto_drivetrain->set_right_wheel_function(right_encoder_lambda);
        auto_drivetrain->set_left_wheel_vel_function(left_encoder_vel_lambda);
        auto_drivetrain->set_right_wheel_vel_function(right_encoder_vel_lambda);
        auto_drivetrain->disable();

        drive_machine = new state_controller<drive_meta>(UPDATE_PERIOD,{},"drive state controller");



        manual = new state("manual");

        /////Start
            /////Entry/Exit Functions
            start_entry = [](state* prev_state) -> void{
                front_left_motor->set_operation(std::function<int16_t()>([](){return DRIVE_SPEED() - DRIVE_TURN();}),drive_machine->get_name());
                back_left_motor->set_operation(std::function<int16_t()>([](){return DRIVE_SPEED() - DRIVE_TURN();}),drive_machine->get_name());
                front_right_motor->set_operation(std::function<int16_t()>([](){return DRIVE_SPEED() + DRIVE_TURN();}),drive_machine->get_name());
                back_right_motor->set_operation(std::function<int16_t()>([](){return DRIVE_SPEED() + DRIVE_TURN();}),drive_machine->get_name());
            };

            start_exit = [](state* next_state) -> void{};

            manual->set_on_state_entry(start_entry);
            manual->set_on_state_exit(start_exit);

        drive_machine->add_state(manual);

        autonomous = new state("autonomous");

            autonomous_entry = [](state* prev_state) -> void {
                auto_drivetrain->enable();
                front_left_motor->set_operation(std::function<int16_t()>([](){return auto_drivetrain->left_wheel_motor_val();}),drive_machine->get_name());
                back_left_motor->set_operation(std::function<int16_t()>([](){return auto_drivetrain->left_wheel_motor_val();}),drive_machine->get_name());
                front_right_motor->set_operation(std::function<int16_t()>([](){return auto_drivetrain->right_wheel_motor_val();}),drive_machine->get_name());
                back_right_motor->set_operation(std::function<int16_t()>([](){return auto_drivetrain->right_wheel_motor_val();}),drive_machine->get_name());
            };
            autonomous_entry = [](state* prev_state) -> void {
                auto_drivetrain->disable();
            };

            autonomous->set_on_state_entry(autonomous_entry);
            autonomous->set_on_state_exit(autonomous_exit);

        drive_machine->add_state(autonomous);

        drive_machine->set_state(manual);
    }

    void destroy(){
        delete(manual);
        delete(drive_machine);
    }
};
