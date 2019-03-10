

#include "afr-vexu-lib/base-action/pid_action.h"
#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"
#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "afr-vexu-lib/base-readable/adi_analog_readable.h"
#include "afr-vexu-lib/base-action/dead_band_action.h"
#include "fuego/shooter/shooter.h"
#include "afr-vexu-lib/base-readable/controller_readable.h"
#include "afr-vexu-lib/base-readable/motor_encoder_velocity_readable.h"
#include "afr-vexu-lib/base-action/bounded_value_action.h"



namespace AFR::VexU::Fuego::Shooter{

    /////////////////////////////////////////////////////////////////////////////////////////////

    state_controller<void>* shooter_state_controller = nullptr;

        //Shooter wheel is inactive
        state* rest = nullptr;

            std::function<bool()> rest_to_spin_up{};
            std::function<void()> rest_entry{};
            std::function<void()> rest_exit{};

        //Shooter wheel is spinning up
        state* spin_up = nullptr;

            std::function<bool()> spin_up_to_rest{};
            std::function<void()> spin_up_entry{};
            std::function<void()> spin_up_exit{};

        //Flywheel commandables
        BaseCommandable::motor_commandable* left_flywheel = nullptr;
        BaseCommandable::motor_commandable* right_flywheel = nullptr;
        BaseAction::pid_action< double, int16_t >* target_speed = nullptr;

    /////////////////////////////////////////////////////////////////////////////////////////////

    state_controller<void>* loader_state_controller = nullptr;

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

    state_controller<void>* auto_aim_state_controller = nullptr;

        //Operate shooter in manual mode via control sticks
        state* manual = nullptr;
            std::function<bool()> manual_to_auto{};
            std::function<void()> manual_entry{};
            std::function<void()> manual_exit{};

        //-------------------------------------------------//

        BaseAction::bounded_value_action< double, int32_t ,int16_t >* follow_stick_hood = nullptr;
            std::function<int16_t(int32_t)> stick_y_to_hood{};
            std::function<int32_t()> get_stick_y{};
            std::function<double()> get_hood_encoder{};

        BaseAction::bounded_value_action< double, int32_t ,int16_t >* follow_stick_turret = nullptr;
            std::function<int16_t(int32_t)> stick_x_to_turret{};
            std::function<int32_t()> get_stick_x{};
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
        /////////////////////////////////////////////////////////////////////////////////////////////

        shooter_state_controller = new state_controller<void>{SHOOTER_UPDATE_PERIOD,"shooter state machine"};

            //Shooter wheel is inactive
            rest = new state("flywheel: rest");
            spin_up = new state("flywheel: spin up");

                rest_to_spin_up = []() -> bool{
                    //Is spin up button pressed
                };
                std::vector<std::pair<std::function<bool()>, state*>> rest_transitions;
                rest_transitions.emplace_back(rest_to_spin_up,spin_up);

            rest->set_transitions(rest_transitions);

                rest_entry = []() -> void{
                    //set voltage to zero
                };
                rest_exit = []() -> void{
                    //turn off commandable
                };

            rest->set_on_state_entry(rest_entry);
            rest->set_on_state_exit(rest_exit);

        shooter_state_controller->add_state(rest);

            //Shooter wheel is spinning up

                spin_up_to_rest = []() -> bool{
                    //Is spin up button pressed
                };
                std::vector<std::pair<std::function<bool()>, state*>> spin_up_transitions;
                spin_up_transitions.emplace_back(spin_up_to_rest,spin_up);

            spin_up->set_transitions(spin_up_transitions);

                spin_up_entry = []() -> void{
                    //Start PID
                };
                spin_up_exit = []() -> void{
                    //Stop PID
                };

            spin_up->set_on_state_entry(spin_up_entry);
            spin_up->set_on_state_exit(spin_up_entry);

        shooter_state_controller->add_state(spin_up);

        shooter_state_controller->set_state(rest);

        /////////////////////////////////////////////////////////////////////////////////////////////

        loader_state_controller = new state_controller<void>{LOADER_UPDATE_PERIOD,"loader state machine"};

            //Loader is holding position at ready
            state* cock = new state("loader: cock");
            state* fire = new state("loader: fire");
            state* walk = new state("loader: walk");

                cock_to_fire = []() -> bool{
                    //Is fire button pressed
                };
                cock_to_walk = []() -> bool{
                    //Is walk button pressed
                };
                std::vector<std::pair<std::function<bool()>, state*>> cock_transitions;
                cock_transitions.emplace_back(cock_to_fire,fire);
                cock_transitions.emplace_back(cock_to_walk,walk);

            cock->set_transitions(cock_transitions);

                cock_entry = []() -> void{
                    //Set dead band to 0
                };
                cock_exit = []() -> void{
                    //Stop dead band
                };

            cock->set_on_state_entry(cock_entry);
            cock->set_on_state_exit(cock_exit);

        loader_state_controller->add_state(cock);

            //Loader goes to the high position, fires ball

                fire_to_cock = []() -> bool{
                    //Fire button is not pressed and walk button is not pressed
                };
                fire_to_walk = []() -> bool{
                    //Fire button is not pressed and walk button is pressed
                };
                std::vector<std::pair<std::function<bool()>, state*>> fire_transitions;
                fire_transitions.emplace_back(fire_to_cock,cock);
                fire_transitions.emplace_back(fire_to_walk,walk);

            fire->set_transitions(fire_transitions);

                fire_entry = []() -> void{
                    //Set dead band to high
                };
                fire_exit = []() -> void{
                    //Stop dead band
                };

            fire->set_on_state_entry(fire_entry);
            fire->set_on_state_exit(fire_exit);

        loader_state_controller->add_state(fire);

            //Loader goes to low position, lifts robot

                walk_to_cock = []() -> bool{
                    //Fire button is not pressed and walk button is not pressed
                };
                walk_to_fire = []() -> bool{
                    //Fire button is not pressed and walk button is pressed
                };
                std::vector<std::pair<std::function<bool()>, state*>> walk_transitions;
                walk_transitions.emplace_back(walk_to_cock,cock);
                walk_transitions.emplace_back(walk_to_fire,fire);

            walk->set_transitions(walk_transitions);

                walk_entry = []() -> void{
                    //Set dead band to low
                };
                walk_exit = []() -> void{
                    //Stop dead band
                };

            walk->set_on_state_entry(walk_entry);
            walk->set_on_state_exit(walk_exit);

        loader_state_controller->add_state(walk);

        loader_state_controller->set_state(cock);

        /////////////////////////////////////////////////////////////////////////////////////////////

        auto_aim_state_controller = new state_controller<void>{AUTO_AIM_UPDATE_PERIOD, "auto aim state machine"};

            //Operate shooter in manual mode via control sticks
            state* manual = new state("auto aim: manual");

                manual_to_auto = []() -> bool{ return false; };

            manual->add_transition(manual_to_auto,auto_aim);

                manual_entry = []() -> void{
                    //Start bounded value action
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