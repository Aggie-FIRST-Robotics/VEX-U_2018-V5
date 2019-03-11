

#include "afr-vexu-lib/base-action/pid_action.h"
#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"
#include "afr-vexu-lib/base-readable/digital_edge_detector.h"
#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "afr-vexu-lib/base-readable/adi_analog_readable.h"
#include "afr-vexu-lib/base-action/dead_band_action.h"
#include "fuego/shooter/shooter.h"
#include "afr-vexu-lib/base-readable/controller_readable.h"
#include "afr-vexu-lib/base-action/bounded_value_action.h"
#include "afr-vexu-lib/base-readable/averager.h"
#include "afr-vexu-lib/ports_list.h"



namespace AFR::VexU::Fuego::Shooter{

    //////////////////////////////////////Controls////////////////////////////////////////////////

    std::function<int32_t()> TURRET_OPERATOR = []() -> int32_t{ return BaseReadable::operator_controller->get_left_x(); };
    std::function<int32_t()> HOOD_OPERATOR = []() -> int32_t{ return BaseReadable::operator_controller->get_left_y(); };
    std::function<bool()> FLYWHEEL_OPERATOR = []() -> bool{ return BaseReadable::operator_controller->get_R2(); };
    std::function<bool()> LOADER_OPERATOR = []() -> bool{ return BaseReadable::operator_controller->get_R1(); };
    std::function<bool()> AUTO_AIM_OPERATOR = []() -> bool{ return BaseReadable::operator_controller->get_L1(); };
    std::function<bool()> WALKER_DRIVER = []() -> bool{ return BaseReadable::operator_controller->get_R2(); };

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
    BaseAction::dead_band_action<double, int16_t>* loader_cock_dead_band = nullptr;
    BaseAction::dead_band_action<double, int16_t>* loader_fire_dead_band = nullptr;
    BaseAction::dead_band_action<double, int16_t>* loader_walk_dead_band = nullptr;

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


        BaseAction::bounded_value_action< double, int32_t ,int16_t >* follow_stick_turret = nullptr;
            std::function<int16_t(int32_t)> stick_x_to_turret{};
            std::function<double()> get_turret_encoder{};

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

    /////////////////////////////////////////////////////////////////////////////////////////////


    void init(){

        /////Flywheel
        left_flywheel_motor = new BaseCommandable::motor_commandable(SHOOTER_UPDATE_PERIOD, FLYWHEEL_LEFT_PORT, FLYWHEEL_GEARSET,
                FLYWHEEL_DIRECTION,FLYWHEEL_BRAKE_MODE, "left flywheel motor");

        right_flywheel_motor = new BaseCommandable::motor_commandable(SHOOTER_UPDATE_PERIOD, FLYWHEEL_RIGHT_PORT, FLYWHEEL_GEARSET,
                !FLYWHEEL_DIRECTION,FLYWHEEL_BRAKE_MODE, "right flywheel motor");

        flywheel_encoder = new BaseReadable::motor_encoder_readable(FLYWHEEL_LEFT_PORT, FLYWHEEL_ENCODER_SCALING, "flywheel encoder");

        avg_flywheel_speed = new BaseReadable::averager<double>([](){return flywheel_encoder->get_scaled_velocity();},
                FLYWHEEL_AVERAGING_WIDTH, "flywheel encoder averager");


        flywheel_pid = new BaseAction::pid_action<double, int16_t >(SHOOTER_UPDATE_PERIOD, P_TERM,
                I_TERM, D_TERM, FLYWHEEL_SPEED - FLYWHEEL_TOLERANCE, FLYWHEEL_SPEED + FLYWHEEL_TOLERANCE,
                MIN_I_TERM, MAX_I_TERM, 0, 0,
                FLYWHEEL_SPEED, "flywheel PID controller");

        /////Loader
        loader_motor = new BaseCommandable::motor_commandable(LOADER_UPDATE_PERIOD, LOADER_MOTOR_PORT, LOADER_GEARSET,
                                                               LOADER_DIRECTION,LOADER_BRAKE_MODE, "left flywheel motor");

        loader_encoder = new BaseReadable::motor_encoder_readable(LOADER_MOTOR_PORT, LOADER_ENCODER_SCALING, "loader encoder");

        loader_cock_dead_band = new BaseAction::dead_band_action<double, int16_t>(LOADER_UPDATE_PERIOD, 0,
                                                                                      LOADER_TOLERANCE, LOADER_MAX_VOLTAGE,
                                                                                      -LOADER_MAX_VOLTAGE, "set to cock dead band");
        loader_fire_dead_band = new BaseAction::dead_band_action<double, int16_t>(LOADER_UPDATE_PERIOD, LOADER_FIRE_TARGET,
                                                                                      LOADER_TOLERANCE, LOADER_MAX_VOLTAGE,
                                                                                      -LOADER_MAX_VOLTAGE, "set to cock dead band");
        loader_walk_dead_band = new BaseAction::dead_band_action<double, int16_t>(LOADER_UPDATE_PERIOD, LOADER_WALK_TARGET,
                                                                                      LOADER_TOLERANCE, LOADER_MAX_VOLTAGE,
                                                                                      -LOADER_MAX_VOLTAGE, "set to cock dead band");

        /////HOOD
        hood_motor = new BaseCommandable::motor_commandable
                (SHOOTER_UPDATE_PERIOD, HOOD_MOTOR_PORT, HOOD_GEARSET, HOOD_DIRECTION,HOOD_BRAKE_MODE, "hood motor");

        hood_encoder = new BaseReadable::motor_encoder_readable
                (HOOD_MOTOR_PORT, HOOD_ENCODER_SCALING, "hood encoder");

        follow_stick_hood = new BaseAction::bounded_value_action< double, int32_t ,int16_t >
                (SHOOTER_UPDATE_PERIOD, HOOD_ENCODER_LIMIT,0, 0, 0, [](int32_t) {return static_cast<int16_t >((12000/127)*HOOD_OPERATOR());},
                    HOOD_OPERATOR, hood_encoder->get_scaled_position(), "hood bounded value action");

        hood_dead_band = new BaseAction::dead_band_action<double, double>(AUTO_AIM_UPDATE_PERIOD, [&](double){return 0;},
                                                                                  AUTO_AIM_HOOD_TOLERANCE, HOOD_MAX_VOLTAGE,
                                                                                  -HOOD_MAX_VOLTAGE, "hood auto aim action");

        /////TURRET
        turret_motor = new BaseCommandable::motor_commandable
                (SHOOTER_UPDATE_PERIOD, TURRET_MOTOR_PORT, TURRET_GEARSET, TURRET_DIRECTION,TURRET_BRAKE_MODE, "turret motor");

        turret_encoder = new BaseReadable::motor_encoder_readable
                (TURRET_MOTOR_PORT, TURRET_ENCODER_SCALING, "turret encoder");

        follow_stick_turret = new BaseAction::bounded_value_action< double, int32_t ,int16_t >
                (SHOOTER_UPDATE_PERIOD, TURRET_ENCODER_LIMIT,0, 0, 0, [](int32_t) {return static_cast<int16_t >((12000/127)*TURRET_OPERATOR());},
                 HOOD_OPERATOR, turret_encoder->get_scaled_position(), "turret bounded value action");

        turret_dead_band = new BaseAction::dead_band_action<double, double>(AUTO_AIM_UPDATE_PERIOD, [&](double){return 0;},
                                                                          AUTO_AIM_TURRET_TOLERANCE, TURRET_MAX_VOLTAGE,
                                                                          -TURRET_MAX_VOLTAGE, "hood auto aim action");

        /////////////////////////////////////////////////////////////////////////////////////////////

        shooter_state_controller = new state_controller<bool>{SHOOTER_UPDATE_PERIOD,false,"shooter state machine"};

        //Readables
        flywheel_spin_up_toggle = new BaseReadable::digital_edge_detector(FLYWHEEL_OPERATOR,"flywheel_spin_up_toggle");

            //Shooter wheel is inactive
            rest = new state("flywheel: rest");
            spin_up = new state("flywheel: spin up");

                std::vector<std::pair<std::function<bool()>, state*>> rest_transitions;
                rest_transitions.emplace_back(flywheel_spin_up_toggle->is_rising_edge(),spin_up);

            rest->set_transitions(rest_transitions);

                rest_entry = []() -> void{
                    left_flywheel_motor->set_value(0,shooter_state_controller->get_name());
                    right_flywheel_motor->set_value(0,shooter_state_controller->get_name());
                };
                rest_exit = []() -> void{
                    left_flywheel_motor->set_value(flywheel_pid->get_pid_value(),shooter_state_controller->get_name());
                    right_flywheel_motor->set_value(flywheel_pid->get_pid_value(),shooter_state_controller->get_name());
                };

            rest->set_on_state_entry(rest_entry);
            rest->set_on_state_exit(rest_exit);

        shooter_state_controller->add_state(rest);

            //Shooter wheel is spinning up
                std::vector<std::pair<std::function<bool()>, state*>> spin_up_transitions;
                spin_up_transitions.emplace_back(flywheel_spin_up_toggle->is_rising_edge(),spin_up);

            spin_up->set_transitions(spin_up_transitions);

                spin_up_entry = []() -> void{
                    left_flywheel_motor->set_value(flywheel_pid->get_pid_value(),shooter_state_controller->get_name());
                    right_flywheel_motor->set_value(flywheel_pid->get_pid_value(),shooter_state_controller->get_name());
                };
                spin_up_exit = []() -> void{
                    left_flywheel_motor->set_value(0,shooter_state_controller->get_name());
                    right_flywheel_motor->set_value(0,shooter_state_controller->get_name());
                };

            spin_up->set_on_state_entry(spin_up_entry);
            spin_up->set_on_state_exit(spin_up_entry);

        shooter_state_controller->add_state(spin_up);

        shooter_state_controller->set_state(rest);

        /////////////////////////////////////////////////////////////////////////////////////////////

        //Readables
        loader_operator_toggle = new BaseReadable::digital_edge_detector(LOADER_OPERATOR,"flywheel_spin_up_toggle");

        loader_state_controller = new state_controller<bool>{LOADER_UPDATE_PERIOD,false,"loader state machine"};

            //Loader is holding position at ready
            state* cock = new state("loader: cock");
            state* fire = new state("loader: fire");
            state* walk = new state("loader: walk");

                std::vector<std::pair<std::function<bool()>, state*>> cock_transitions;
                cock_transitions.emplace_back(loader_operator_toggle->is_rising_edge() && !WALKER_DRIVER(),fire);
                cock_transitions.emplace_back(WALKER_DRIVER,walk);

            cock->set_transitions(cock_transitions);

                cock_entry = []() -> void{
                    loader_motor->set_value(loader_cock_dead_band->get_deadband_value(),loader_state_controller->get_name());
                };
                cock_exit = []() -> void{
                    loader_motor->set_value(0,loader_state_controller->get_name());
                };

            cock->set_on_state_entry(cock_entry);
            cock->set_on_state_exit(cock_exit);

        loader_state_controller->add_state(cock);

            //Loader goes to the high position, fires ball
                std::vector<std::pair<std::function<bool()>, state*>> fire_transitions;
                fire_transitions.emplace_back([](bool){return loader_fire_dead_band->is_in_range(LOADER_TOLERANCE);},cock);

            fire->set_transitions(fire_transitions);

                fire_entry = []() -> void{
                    loader_motor->set_value(loader_fire_dead_band->get_deadband_value(),loader_state_controller->get_name());
                };
                fire_exit = []() -> void{
                    loader_motor->set_value(loader_cock_dead_band->get_deadband_value(),loader_state_controller->get_name());
                };

            fire->set_on_state_entry(fire_entry);
            fire->set_on_state_exit(fire_exit);

        loader_state_controller->add_state(fire);

            //Loader goes to low position, lifts robot

                std::vector<std::pair<std::function<bool()>, state*>> walk_transitions;
                walk_transitions.emplace_back([](bool){return !WALKER_DRIVER() && !LOADER_OPERATOR();},cock);
                walk_transitions.emplace_back([](bool){return !WALKER_DRIVER && LOADER_OPERATOR;},fire);

            walk->set_transitions(walk_transitions);

                walk_entry = []() -> void{
                    loader_motor->set_value(loader_walk_dead_band->get_deadband_value(),loader_state_controller->get_name());
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
                    hood_motor->set_value(follow_stick_hood->get_current_value(),auto_aim_state_controller->get_name());
                };
                manual_exit = []() -> void{
                    //Stop bounded value action
                };
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