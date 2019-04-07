#include "rev/ball-intake/ball_intake.h"

namespace AFR::VexU::Rev::BallIntake{

    /////Readables
    BaseReadable::digital_edge_detector* swallow_button = nullptr;

    /////State Controller
    struct ball_intake_meta{};
    state_controller<ball_intake_meta> *ball_intake_controller = nullptr;

    /////States
    state* spit = nullptr;
    state* swallow = nullptr;
    state* choke = nullptr;

    void init(){

        Rollers::init();

        swallow_button = new BaseReadable::digital_edge_detector(std::function<bool()>([](){
            return BaseReadable::driver_controller->is_digital_pressed(BALL_SWALLOW_BUTTON);
        }),"swallow_button");

        ball_intake_controller = new state_controller<ball_intake_meta>{UPDATE_PERIOD, {}, "ball_intake_controller"};

        spit = new state{"spit"};
        swallow = new state{"swallow"};
        choke = new state{"choke"};

        /////Spit
            /////Entry/Exit Functions
            spit->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
                Rollers::left_motor->set_value(SPIT_VOLTAGE, ball_intake_controller->get_name());
                Rollers::right_motor->set_value(SPIT_VOLTAGE, ball_intake_controller->get_name());
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
                Rollers::left_motor->set_value(SWALLOW_VOLTAGE, ball_intake_controller->get_name());
                Rollers::right_motor->set_value(SWALLOW_VOLTAGE, ball_intake_controller->get_name());
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
                Rollers::left_motor->set_value(0, ball_intake_controller->get_name());
                Rollers::right_motor->set_value(0, ball_intake_controller->get_name());
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
        Rollers::destroy();
        delete ball_intake_controller;
        delete swallow_button;
        delete choke;
        delete swallow;
        delete spit;
    }
}