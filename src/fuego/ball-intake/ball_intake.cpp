#include "fuego/ball-intake/ball_intake.h"
#include "fuego/fuego.h"

#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "afr-vexu-lib/base-action/bidirectional_control_action.h"
#include "afr-vexu-lib/base-readable/controller_readable.h"

namespace AFR::VexU::Fuego::BallIntake{
    BaseCommandable::motor_commandable* ball_intake_motor{};

    BaseAction::set_value_action<int16_t>* intake_spit{}, * intake_swallow{}, * intake_choke{};

    BaseReadable::controller_digital_readable* spit_button{}, * swallow_button{};

    std::vector<action*> spit_actions{}, swallow_actions{}, choke_actions{};

    std::function<bool()> spit_to_choke{};

    std::function<bool()> swallow_to_spit{}, swallow_to_choke{};

    std::function<bool()> choke_to_spit{}, choke_to_swallow{};

    std::vector<transition> spit_transitions{}, swallow_transitions{}, choke_transitions{};

    std::function<void(state*)> on_spit_entry{}, on_swallow_entry{}, on_choke_entry{};

    state* spit{}, * swallow{}, * choke{};

    std::vector<state*> states{};

    std::vector<commandable*> commandables{};

    state_controller* ball_intake_state_controller{};

    std::vector<readable*> readables{};

    std::vector<state_controller*> state_controllers{};

    subsystem_controller* ball_intake_subsystem{};

    void init(){
            using namespace BaseCommandable;
            using namespace BaseReadable;
            using namespace BaseAction;

            ball_intake_motor = new motor_commandable{BALL_INTAKE_MOTOR_PORT, BALL_INTAKE_GEARSET, false,
                                                      BALL_INTAKE_BRAKE_MODE, "ball_intake_motor"};

            intake_spit = new set_value_action<int16_t>{10, ball_intake_motor, -12000, "intake_spit"};
            intake_swallow = new set_value_action<int16_t>{10, ball_intake_motor, 12000, "intake_swallow"};
            intake_choke = new set_value_action<int16_t>{10, ball_intake_motor, 0, "intake_choke"};

            spit_actions.push_back(intake_spit);
            swallow_actions.push_back(intake_swallow);
            choke_actions.push_back(intake_choke);

            spit_button = get_controller_digital_readable(pros::E_CONTROLLER_MASTER, BALL_SPIT_BUTTON);
            swallow_button = get_controller_digital_readable(pros::E_CONTROLLER_MASTER, BALL_SWALLOW_BUTTON);

            spit_to_choke = []() -> bool{
                return !spit_button->is_pressed();
            };

            swallow_to_spit = []() -> bool{
                return spit_button->is_pressed();
            };
            swallow_to_choke = []() -> bool{
                return swallow_button->is_rising_edge();
            };

            choke_to_spit = []() -> bool{
                return spit_button->is_pressed();
            };
            choke_to_swallow = []() -> bool{
                return swallow_button->is_rising_edge();
            };

            spit_transitions.emplace_back(spit_to_choke, choke, "spit_to_choke");

            swallow_transitions.emplace_back(swallow_to_spit, spit, "swallow_to_spit");
            swallow_transitions.emplace_back(swallow_to_choke, choke, "swallow_to_choke");

            choke_transitions.emplace_back(choke_to_spit, spit, "choke_to_spit");
            choke_transitions.emplace_back(choke_to_swallow, swallow, "choke_to_swallow");

            on_spit_entry = [](state* last_state) -> void{};
            on_swallow_entry = [](state* last_state) -> void{};
            on_choke_entry = [](state* last_state) -> void{};

            spit = new state{spit_actions, spit_transitions, on_spit_entry, "spit"};
            swallow = new state{swallow_actions, swallow_transitions, on_swallow_entry, "swallow"};
            choke = new state{choke_actions, choke_transitions, on_choke_entry, "choke"};

            states.push_back(spit);
            states.push_back(swallow);
            states.push_back(choke);

            commandables.push_back(ball_intake_motor);

            ball_intake_state_controller = new state_controller{10, states, commandables, choke,
                                                                "ball_intake_state_controller"};

            state_controllers.push_back(ball_intake_state_controller);

            ball_intake_subsystem = new subsystem_controller{readables, state_controllers, "ball_intake_subsystem"};
    }
}