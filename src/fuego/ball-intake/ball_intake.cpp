#include "fuego/ball-intake/ball_intake.h"

namespace AFR::VexU::Fuego::BallIntake{
    /////Commandables
    BaseCommandable::motor_commandable* ball_intake_motor = nullptr;

    /////Readables
    BaseReadable::digital_edge_detector* swallow_button = nullptr;

    /////State Controller
    
    state_controller<ball_intake_meta> *ball_intake_controller = nullptr;

    /////States
    state* spit = nullptr;
    state* swallow = nullptr;
    state* choke = nullptr;

    void init(){

        /////Commandables
        ball_intake_motor = new BaseCommandable::motor_commandable
                {UPDATE_PERIOD, BALL_INTAKE_MOTOR_PORT, BALL_INTAKE_GEARSET, DIRECTION, BALL_INTAKE_BRAKE_MODE, "ball_intake_motor"};

        swallow_button = new BaseReadable::digital_edge_detector
                (std::function<bool()>([](){return BaseReadable::driver_controller->is_digital_pressed(BALL_SWALLOW_BUTTON);}),"swallow_button");

        ball_intake_controller = new state_controller<ball_intake_meta>{UPDATE_PERIOD, {}, "ball_intake_controller"};

        spit = new state{"spit"};
        swallow = new state{"swallow"};
        choke = new state{"choke"};

        /////Spit
            /////Entry/Exit Functions
            spit->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
                ball_intake_motor->set_value(SPIT_VOLTAGE, ball_intake_controller->get_name());
            }));
            spit->set_on_state_exit(std::function<void(state*)>([](state* next_state){

            }));

            /////Transitions
            spit->add_transition(std::function<bool()>([](){
                return !BaseReadable::driver_controller->is_digital_pressed(BALL_SPIT_BUTTON);
            }),choke);

        /////Swallow
            /////Entry/Exit Functions
            swallow->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
                ball_intake_motor->set_value(SWALLOW_VOLTAGE, ball_intake_controller->get_name());
            }));
            swallow->set_on_state_exit(std::function<void(state*)>([](state* next_state){

            }));

            /////Transitions
            swallow->add_transition(std::function<bool()>([](){
                return BaseReadable::driver_controller->is_digital_pressed(BALL_SPIT_BUTTON);
            }),spit);

            swallow->add_transition(std::function<bool()>([](){
                return swallow_button->is_rising_edge();
            }),choke);

        /////Choke
            /////Entry/Exit Functions
            choke->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
                ball_intake_motor->set_value(0, ball_intake_controller->get_name());
            }));
            choke->set_on_state_exit(std::function<void(state*)>([](state* next_state){

            }));

            /////Transitions
            choke->add_transition(std::function<bool()>([](){
                return swallow_button->is_rising_edge();
            }),swallow);
            choke->add_transition(std::function<bool()>([](){
                return BaseReadable::driver_controller->is_digital_pressed(BALL_SPIT_BUTTON);
            }),spit);

        ball_intake_controller->add_state(spit);
        ball_intake_controller->add_state(swallow);
        ball_intake_controller->add_state(choke);

        ball_intake_controller->set_state(choke);
    }

    void destroy() {
        delete ball_intake_controller;
        delete ball_intake_motor;
        delete swallow_button;
        delete choke;
        delete swallow;
        delete spit;
    }
}