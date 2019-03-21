#include "afr-vexu-lib/base-action/pid_action.h"
#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"
#include "afr-vexu-lib/base-readable/digital_edge_detector.h"
#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "afr-vexu-lib/base-readable/adi_analog_readable.h"
#include "afr-vexu-lib/base-action/dead_band_action.h"
#include "fuego/shooter/shooter.h"
#include "afr-vexu-lib/base-action/bounded_value_action.h"
#include "afr-vexu-lib/base-readable/averager.h"

namespace AFR::VexU::Fuego::Shooter{

    //////////////////////////////////////Controls////////////////////////////////////////////////

    std::function<int32_t()> TURRET_OPERATOR = []() -> int32_t{
        return BaseReadable::driver_controller->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
    };
    std::function<int32_t()> HOOD_OPERATOR = []() -> int32_t{
        return BaseReadable::driver_controller->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    };
    std::function<bool()> FLYWHEEL_OPERATOR = []() -> bool{
        return BaseReadable::driver_controller->is_digital_pressed(pros::E_CONTROLLER_DIGITAL_R2);
    };
    std::function<bool()> LOADER_OPERATOR = []() -> bool{
        return BaseReadable::driver_controller->is_digital_pressed(pros::E_CONTROLLER_DIGITAL_R1);
    };
    std::function<bool()> AUTO_AIM_OPERATOR = []() -> bool{
        return BaseReadable::driver_controller->is_digital_pressed(pros::E_CONTROLLER_DIGITAL_L1);
    };
    std::function<bool()> WALKER_DRIVER = []() -> bool{
        return BaseReadable::driver_controller->is_digital_pressed(pros::E_CONTROLLER_DIGITAL_X);
    };

    //////////////////////////////Commandables and Readables///////////////////////////////////////

    //Flywheel
    BaseCommandable::motor_commandable* left_flywheel_motor = nullptr;
    BaseCommandable::motor_commandable* right_flywheel_motor = nullptr;
    BaseReadable::motor_encoder_readable* flywheel_encoder = nullptr;
    BaseReadable::averager<double>* avg_flywheel_speed = nullptr;
    BaseAction::pid_action<double, int16_t >* flywheel_pid = nullptr;

    //Loader
    BaseCommandable::motor_commandable* loader_motor = nullptr;
    BaseReadable::motor_encoder_readable* loader_encoder = nullptr;
    BaseAction::dead_band_action<double, int16_t>* loader_dead_band = nullptr;

    //Auto Aim
    BaseCommandable::motor_commandable* hood_motor = nullptr;
    BaseCommandable::motor_commandable* turret_motor = nullptr;
    BaseReadable::motor_encoder_readable* hood_encoder = nullptr;
    BaseReadable::motor_encoder_readable* turret_encoder = nullptr;
    BaseAction::dead_band_action<double,double>* hood_dead_band = nullptr;
    BaseAction::dead_band_action<double,double>* turret_dead_band = nullptr;
    BaseAction::bounded_value_action< double, int32_t ,int16_t >* follow_stick_hood = nullptr;
    BaseAction::bounded_value_action< double, int32_t ,int16_t >* follow_stick_turret = nullptr;

    /////////////////////////////////////////////////////////////////////////////////////////////

    //Readables
    BaseReadable::digital_edge_detector* flywheel_spin_up_toggle = nullptr;


    state_controller<bool>* shooter_state_controller = nullptr;

        //Shooter wheel is inactive
        state* rest = nullptr;

            std::function<void()> rest_entry{};
            std::function<void()> rest_exit{};

        //Shooter wheel is spinning up
        state* spin_up = nullptr;

            std::function<void()> spin_up_entry{};
            std::function<void()> spin_up_exit{};

        //Flywheel commandables
        BaseCommandable::motor_commandable* left_flywheel = nullptr;
        BaseCommandable::motor_commandable* right_flywheel = nullptr;
        BaseAction::pid_action< double, int16_t >* target_speed = nullptr;

    /////////////////////////////////////////////////////////////////////////////////////////////

    //Readables
    BaseReadable::digital_edge_detector* loader_operator_toggle = nullptr;

    state_controller<bool>* loader_state_controller = nullptr;

        //Loader is holding position at ready
        state* cock = nullptr;

            std::function<bool()> cock_to_fire{};
            std::function<bool()> cock_to_walk{};
            std::function<void()> cock_entry{};
            std::function<void()> cock_exit{};

        //Loader goes to the high position, fires ball
        state* fire = nullptr;

            std::function<bool()> fire_to_cock{};
            std::function<bool()> fire_to_walk{};
            std::function<void()> fire_entry{};
            std::function<void()> fire_exit{};


        //Loader goes to low position, lifts robot
        state* walk = nullptr;

            std::function<bool()> walk_to_cock{};
            std::function<bool()> walk_to_fire{};
            std::function<void()> walk_entry{};
            std::function<void()> walk_exit{};


    /////////////////////////////////////////////////////////////////////////////////////////////

    //Readables


    state_controller<bool>* auto_aim_state_controller = nullptr;

        //Operate shooter in manual mode via control sticks
        state* manual = nullptr;
            std::function<bool()> manual_to_auto{};

        std::function<void()> manual_entry{};
        std::function<void()> manual_exit{};

        //-------------------------------------------------//


        //-------------------------------------------------//

        //Shooter searches for target
        state* auto_aim = nullptr;
        std::vector<std::pair<std::function<bool()>, state*>> auto_aim_transitions;
        std::function<void()> auto_aim_entry;
        std::function<void()> auto_aim_exit;

        //Shooter is locked onto a target
        state* ready = nullptr;
        std::vector<std::pair<std::function<bool()>, state*>> ready_transitions;
        std::function<void()> ready_entry;
        std::function<void()> ready_exit;

    ////////////////////////////////////////////////////////////////////////////////////////////


    void init(){

        /////Flywheel
        left_flywheel_motor = new BaseCommandable::motor_commandable(SHOOTER_UPDATE_PERIOD, FLYWHEEL_LEFT_PORT, FLYWHEEL_GEARSET,
                FLYWHEEL_DIRECTION,FLYWHEEL_BRAKE_MODE, "left flywheel motor");

        right_flywheel_motor = new BaseCommandable::motor_commandable(SHOOTER_UPDATE_PERIOD, FLYWHEEL_RIGHT_PORT, FLYWHEEL_GEARSET,
                !FLYWHEEL_DIRECTION,FLYWHEEL_BRAKE_MODE, "right flywheel motor");

        flywheel_encoder = new BaseReadable::motor_encoder_readable(FLYWHEEL_LEFT_PORT, FLYWHEEL_ENCODER_SCALING, "flywheel encoder");

        avg_flywheel_speed = new BaseReadable::averager<double>([](){return flywheel_encoder->get_scaled_velocity();},
                FLYWHEEL_AVERAGING_WIDTH, "flywheel encoder averager");


        flywheel_pid = new BaseAction::pid_action< double, int16_t >(SHOOTER_UPDATE_PERIOD, P_TERM,
                I_TERM, D_TERM, MIN_I_TERM, MAX_I_TERM,
                MIN_I_TERM, MAX_I_TERM, 0, 0,
                FLYWHEEL_SPEED, "flywheel PID controller");



        /////Loader
        loader_motor = new BaseCommandable::motor_commandable(LOADER_UPDATE_PERIOD, LOADER_MOTOR_PORT, LOADER_GEARSET,
                                                               LOADER_DIRECTION,LOADER_BRAKE_MODE, "loader motor");

        loader_encoder = new BaseReadable::motor_encoder_readable(LOADER_MOTOR_PORT, LOADER_ENCODER_SCALING, "loader encoder");

        loader_dead_band = new BaseAction::dead_band_action<double, int16_t>(LOADER_UPDATE_PERIOD, 0,
                                                                                      LOADER_TOLERANCE, LOADER_MAX_VOLTAGE,
                                                                                      -LOADER_MAX_VOLTAGE, "Loader dead band action");


        /////HOOD
        hood_motor = new BaseCommandable::motor_commandable
                (SHOOTER_UPDATE_PERIOD, HOOD_MOTOR_PORT, HOOD_GEARSET, HOOD_DIRECTION,HOOD_BRAKE_MODE, "hood motor");

        hood_encoder = new BaseReadable::motor_encoder_readable
                (HOOD_MOTOR_PORT, HOOD_ENCODER_SCALING, "hood encoder");

        std::function<int16_t(int32_t)> hood_bounded_action_conversion_function = [](int32_t) -> int16_t {
            return static_cast<int16_t >((12000/127)*TURRET_OPERATOR());
        };

        std::function<int16_t()> hood_encoder_function = [] { return hood_encoder->get_scaled_position(); };

        follow_stick_hood = new BaseAction::bounded_value_action< double, int32_t ,int16_t >
                (SHOOTER_UPDATE_PERIOD, HOOD_ENCODER_LIMIT,0, 0, 0, std::function<int16_t(int32_t)>([](int32_t){ return static_cast<int16_t >((12000/127)*HOOD_OPERATOR());}),
                    HOOD_OPERATOR, hood_encoder_function, "hood bounded value action");

        hood_dead_band = new BaseAction::dead_band_action<double, double>(AUTO_AIM_UPDATE_PERIOD, 0,
                                                                                  AUTO_AIM_HOOD_TOLERANCE, HOOD_MAX_VOLTAGE,
                                                                                  -HOOD_MAX_VOLTAGE, "hood auto aim action");

        /////TURRET
        turret_motor = new BaseCommandable::motor_commandable
                (SHOOTER_UPDATE_PERIOD, TURRET_MOTOR_PORT, TURRET_GEARSET, TURRET_DIRECTION,TURRET_BRAKE_MODE, "turret motor");

        turret_encoder = new BaseReadable::motor_encoder_readable
                (TURRET_MOTOR_PORT, TURRET_ENCODER_SCALING, "turret encoder");

        std::function<double()> turret_encoder_function = []{ return turret_encoder->get_scaled_position(); };

        follow_stick_turret = new BaseAction::bounded_value_action< double, int32_t ,int16_t >
                (SHOOTER_UPDATE_PERIOD, TURRET_ENCODER_LIMIT,0, 0, 0, std::function<int16_t(int32_t)>([](int32_t){ return static_cast<int16_t >((12000/127)*TURRET_OPERATOR());}),
                 TURRET_OPERATOR, turret_encoder_function, "turret bounded value action");

        turret_dead_band = new BaseAction::dead_band_action<double, double>(AUTO_AIM_UPDATE_PERIOD, 0,
                                                                          AUTO_AIM_TURRET_TOLERANCE, TURRET_MAX_VOLTAGE,
                                                                          -TURRET_MAX_VOLTAGE, "turret auto aim action");

        /////////////////////////////////////////////////////////////////////////////////////////////

        shooter_state_controller = new state_controller<bool>{SHOOTER_UPDATE_PERIOD,false,"shooter state machine"};

        //Readables
        flywheel_spin_up_toggle = new BaseReadable::digital_edge_detector(FLYWHEEL_OPERATOR,"flywheel spin up toggle");

        flywheel_pid->set_operation(std::function<double()>([](){ return avg_flywheel_speed->get_average_value();}), shooter_state_controller->get_name());

            //Shooter wheel is inactive
            rest = new state("flywheel: rest");
            spin_up = new state("flywheel: spin up");

                rest->add_transition(std::function<bool()>([](){ return flywheel_spin_up_toggle->is_rising_edge();}),spin_up);

                rest_entry = []() -> void{
                    left_flywheel_motor->set_value(0,shooter_state_controller->get_name());
                    right_flywheel_motor->set_value(0,shooter_state_controller->get_name());
                };
                rest_exit = []() -> void{
                    left_flywheel_motor->set_operation(std::function<int16_t()>([](){return flywheel_pid->get_pid_value();}),shooter_state_controller->get_name());
                    right_flywheel_motor->set_operation(std::function<int16_t()>([](){return flywheel_pid->get_pid_value();}),shooter_state_controller->get_name());
                };

            rest->set_on_state_entry(rest_entry);
            rest->set_on_state_exit(rest_exit);

        shooter_state_controller->add_state(rest);

            //Shooter wheel is spinning up
            spin_up->add_transition(std::function<bool()>([]() { return flywheel_spin_up_toggle->is_rising_edge(); }),rest);

                spin_up_entry = []() -> void{
                    left_flywheel_motor->set_operation(std::function<int16_t()>([](){return flywheel_pid->get_pid_value();}),shooter_state_controller->get_name());
                    right_flywheel_motor->set_operation(std::function<int16_t()>([](){return flywheel_pid->get_pid_value();}),shooter_state_controller->get_name());
                };
                spin_up_exit = []() -> void{
                    left_flywheel_motor->set_value(0,shooter_state_controller->get_name());
                    right_flywheel_motor->set_value(0,shooter_state_controller->get_name());
                };

            spin_up->set_on_state_entry(spin_up_entry);
            spin_up->set_on_state_exit(spin_up_exit);

        shooter_state_controller->add_state(spin_up);

        shooter_state_controller->set_state(rest);

        /////////////////////////////////////////////////////////////////////////////////////////////

        //Readables
        loader_operator_toggle = new BaseReadable::digital_edge_detector(LOADER_OPERATOR,"loader toggle");

        loader_state_controller = new state_controller<bool>{LOADER_UPDATE_PERIOD,false,"loader state machine"};

        loader_dead_band->set_operation(std::function<double()>([](){ return loader_encoder->get_scaled_position();}), loader_state_controller->get_name());

        //Loader is holding position at ready
            state* cock = new state("loader: cock");
            state* fire = new state("loader: fire");
            state* walk = new state("loader: walk");

                cock->add_transition(std::function<bool()>([]() { return loader_operator_toggle->is_rising_edge() && !WALKER_DRIVER(); }),fire);
                cock->add_transition(std::function<bool()>([]() { return WALKER_DRIVER(); }),walk);

                cock_entry = []() -> void{
                    loader_dead_band->set_target(0);
                    loader_motor->set_operation(std::function<int16_t()>([](){
                        std::cout << "Cock dead band value: " << loader_dead_band->get_deadband_value() << std::endl;
                        return loader_dead_band->get_deadband_value();}),loader_state_controller->get_name());
                };
                cock_exit = []() -> void{
                    loader_motor->set_value(0,loader_state_controller->get_name());
                };

            cock->set_on_state_entry(cock_entry);
            cock->set_on_state_exit(cock_exit);

        loader_state_controller->add_state(cock);

            //Loader goes to the high position, fires ball
            fire->add_transition(std::function<bool()>([](){return loader_dead_band->is_in_range(LOADER_TOLERANCE);}),cock);

                fire_entry = []() -> void{
                    loader_dead_band->set_target(LOADER_FIRE_TARGET);
                    loader_motor->set_operation(std::function<int16_t()>([](){
                        std::cout << "Fire dead band value: " << loader_dead_band->get_deadband_value() << std::endl;
                        return loader_dead_band->get_deadband_value();}),loader_state_controller->get_name());
                };
                fire_exit = []() -> void{
                    loader_motor->set_value(0,loader_state_controller->get_name());
                };

            fire->set_on_state_entry(fire_entry);
            fire->set_on_state_exit(fire_exit);

        loader_state_controller->add_state(fire);

            //Loader goes to low position, lifts robot

                walk->add_transition(std::function<bool()>([](){return !WALKER_DRIVER() && !LOADER_OPERATOR();}),cock);
                walk->add_transition(std::function<bool()>([](){return !WALKER_DRIVER() && LOADER_OPERATOR();}),fire);

                walk_entry = []() -> void{
                    loader_dead_band->set_target(LOADER_WALK_TARGET);
                    loader_motor->set_operation(std::function<int16_t()>([](){
                        std::cout << "Walk dead band value: " << loader_dead_band->get_deadband_value() << std::endl;
                        return loader_dead_band->get_deadband_value();}),loader_state_controller->get_name());
                };
                walk_exit = []() -> void{
                    loader_motor->set_value(0,loader_state_controller->get_name());
                };

            walk->set_on_state_entry(walk_entry);
            walk->set_on_state_exit(walk_exit);

        loader_state_controller->add_state(walk);

        loader_state_controller->set_state(cock);

        /////////////////////////////////////////////////////////////////////////////////////////////

        auto_aim_state_controller = new state_controller<bool>{AUTO_AIM_UPDATE_PERIOD, false,"auto aim state machine"};

            //Operate shooter in manual mode via control sticks
            state* manual = new state("auto aim: manual");

                manual_to_auto = []() -> bool{ return false; };

            manual->add_transition(manual_to_auto,auto_aim);

                manual_entry = []() -> void{
                    hood_motor->set_operation(std::function<int16_t()>([](){return follow_stick_hood->get_bounded_value();}), auto_aim_state_controller->get_name());
                    turret_motor->set_operation(std::function<int16_t()>([](){return follow_stick_turret->get_bounded_value();}),auto_aim_state_controller->get_name());
                };
                manual_exit = []() -> void{
                    hood_motor->set_value(0,auto_aim_state_controller->get_name());
                    turret_motor->set_value(0,auto_aim_state_controller->get_name());
                };

            manual->set_on_state_entry(manual_entry);
            manual->set_on_state_exit(manual_exit);

        auto_aim_state_controller->set_state(manual);

        std::cout << "Created auto aim" << std::endl;
    }

    void destroy(){
        delete shooter_state_controller;
        delete rest;
        delete spin_up;
        delete loader_state_controller;
        delete cock;
        delete fire;
        delete walk;
        delete auto_aim_state_controller;
        delete manual;
        delete auto_aim;
        delete ready;
    }


}