#include "fuego/ball-intake/ball_intake.h"
#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "afr-vexu-lib/base-action/pid_action.h"

namespace AFR::VexU::Fuego::BallIntake{
    //////////////////////////////Commandables and Readables///////////////////////////////////////
    BaseCommandable::motor_commandable* ball_intake_motor{};

    ///////////////////////////////////////////////////////////////////////////////////////////////

    state_controller<void>* ball_intake_controller{};
    state* spit{};
    std::function<bool()> spit_to_choke{};
    state* swallow{};
    std::function<bool()> swallow_to_spit{};
    std::function<bool()> swallow_to_choke{};
    state* choke{};
    std::function<bool()> choke_to_spit{};
    std::function<bool()> choke_to_swallow{};

    void init(){
        using namespace BaseCommandable;
        using namespace BaseReadable;
        using namespace BaseAction;

        ball_intake_motor = new motor_commandable{BALL_INTAKE_UPDATE_PERIOD, BALL_INTAKE_MOTOR_PORT,
                                                  BALL_INTAKE_GEARSET, false,
                                                  BALL_INTAKE_BRAKE_MODE, "ball_intake_motor"};

        ball_intake_controller = new state_controller<void>{BALL_INTAKE_UPDATE_PERIOD, "ball_intake_controller"};

        spit = new state{"spit"};
        spit->set_on_state_entry(std::function<void()>{[]() -> void{
            ball_intake_motor->set_value(-12000, spit->get_name());
        }});

        swallow = new state{"swallow"};
        swallow->set_on_state_entry(std::function<void()>{[]() -> void{
            ball_intake_motor->set_value(12000, swallow->get_name());
        }});

        choke = new state{"choke"};
        choke->set_on_state_entry(std::function<void()>{[]() -> void{
            ball_intake_motor->set_value(0, choke->get_name());
        }});

        spit_to_choke = []() -> bool{
            return !driver_controller->is_digital_pressed(BALL_SPIT_BUTTON);
        };
        spit->add_transition(spit_to_choke, choke);

        swallow_to_spit = []() -> bool{
            return driver_controller->is_digital_pressed(BALL_SPIT_BUTTON);
        };
        swallow_to_choke = []() -> bool{
            return !driver_controller->is_digital_pressed(BALL_SWALLOW_BUTTON);
        };
        swallow->add_transition(swallow_to_spit, spit);
        swallow->add_transition(swallow_to_choke, choke);

        choke_to_spit = []() -> bool{
            return driver_controller->is_digital_pressed(BALL_SPIT_BUTTON);
        };
        choke_to_swallow = []() -> bool{
            return driver_controller->is_digital_pressed(BALL_SWALLOW_BUTTON);
        };
        choke->add_transition(choke_to_spit, spit);
        choke->add_transition(choke_to_swallow, swallow);

        ball_intake_controller->add_state(spit);
        ball_intake_controller->add_state(swallow);
        ball_intake_controller->add_state(choke);
    }
}