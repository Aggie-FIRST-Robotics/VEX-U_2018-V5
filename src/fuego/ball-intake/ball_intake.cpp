#include "fuego/ball-intake/ball_intake.h"

namespace AFR::VexU::Fuego::BallIntake{
    /////Commandables
    BaseCommandable::motor_commandable* ball_intake_motor{};

    /////State Controller
    state_controller<void>* ball_intake_controller{};

    /////States
    state* spit{};
    state* swallow{};
    state* choke{};

    /////Transition Functions
    std::function<bool()> spit_to_choke{};
    std::function<bool()> swallow_to_spit{};
    std::function<bool()> swallow_to_choke{};
    std::function<bool()> choke_to_spit{};
    std::function<bool()> choke_to_swallow{};

    void init(){

        /////Commandables
        ball_intake_motor = new BaseCommandable::motor_commandable{BALL_INTAKE_UPDATE_PERIOD, BALL_INTAKE_MOTOR_PORT,
                                                                   BALL_INTAKE_GEARSET, false,
                                                                   BALL_INTAKE_BRAKE_MODE, "ball_intake_motor"};

        ball_intake_controller = new state_controller<void>{BALL_INTAKE_UPDATE_PERIOD, "ball_intake_controller"};

        spit = new state{"spit"};
        swallow = new state{"swallow"};
        choke = new state{"choke"};

        /////Spit
            /////Entry Function
            spit->set_on_state_entry(std::function<void()>{[]() -> void{
                ball_intake_motor->set_value(-12000, spit->get_name());
            }});

            /////Transitions
            spit_to_choke = []() -> bool{
                return !BaseReadable::driver_controller->is_digital_pressed(BALL_SPIT_BUTTON);
            };

            spit->add_transition(spit_to_choke, choke);

        /////Swallow
            /////Entry Function
            swallow->set_on_state_entry(std::function<void()>{[]() -> void{
                ball_intake_motor->set_value(12000, swallow->get_name());
            }});

            /////Transitions
            swallow_to_spit = []() -> bool{
                return BaseReadable::driver_controller->is_digital_pressed(BALL_SPIT_BUTTON);
            };
            swallow_to_choke = []() -> bool{
                return !BaseReadable::driver_controller->is_digital_pressed(BALL_SWALLOW_BUTTON);
            };

            swallow->add_transition(swallow_to_spit, spit);
            swallow->add_transition(swallow_to_choke, choke);

        /////Choke
            /////Entry Function
            choke->set_on_state_entry(std::function<void()>{[]() -> void{
                ball_intake_motor->set_value(0, choke->get_name());
            }});

            /////Transitions
            choke_to_spit = []() -> bool{
                return BaseReadable::driver_controller->is_digital_pressed(BALL_SPIT_BUTTON);
            };
            choke_to_swallow = []() -> bool{
                return BaseReadable::driver_controller->is_digital_pressed(BALL_SWALLOW_BUTTON);
            };

            choke->add_transition(choke_to_spit, spit);
            choke->add_transition(choke_to_swallow, swallow);

        ball_intake_controller->add_state(spit);
        ball_intake_controller->add_state(swallow);
        ball_intake_controller->add_state(choke);

        ball_intake_controller->set_state(choke);
    }
}