#include "afr-vexu-lib/base-readable/controller_readable.h"
#include "afr-vexu-lib/base-action/dead_band_action.h"
#include "robot/catapult/catapult.h"
#include "robot/robot.h"

namespace AFR::VexU::Robot::Catapult{
    scheduled_update_t next_cock = 0;

    //Commandables
    BaseCommandable::motor_commandable* nautilus_motor = nullptr;

    //Readables
    BaseReadable::adi_digital_readable* nautilus_limit_switch = nullptr;
    BaseReadable::motor_encoder_readable* nautilus_encoder = nullptr;
    BaseReadable::controller_digital_readable* fire_button = nullptr;

    //Actions
    BaseAction::dead_band_action<double, int16_t>* hold_nautilus_action = nullptr;
    BaseAction::set_value_action<int16_t>* cock_nautilus_action = nullptr;
    BaseAction::set_value_action<int16_t>* stop_nautilus_action = nullptr;
    BaseAction::set_value_action<int16_t>* fire_nautilus_action = nullptr;

    //Action Vectors
    std::vector<action*> hold_actions{};
    std::vector<action*> cock_actions{};
    std::vector<action*> stop_actions{};
    std::vector<action*> fire_actions{};

    //Transition functions
    std::function<bool()> cock_to_hold{};
    std::function<bool()> hold_to_fire{};
    std::function<bool()> fire_to_stop{};
    std::function<bool()> stop_to_cock{};

    //Transition vectors
    std::vector<transition> cock_transitions{};
    std::vector<transition> hold_transitions{};
    std::vector<transition> fire_transitions{};
    std::vector<transition> stop_transitions{};

    //On-state entry functions
    std::function<void(state*)> on_cock_entry{};
    std::function<void(state*)> on_hold_entry{};
    std::function<void(state*)> on_fire_entry{};
    std::function<void(state*)> on_stop_entry{};

    //States
    state* cock = nullptr;
    state* hold = nullptr;
    state* fire = nullptr;
    state* stop = nullptr;

    //State map
    std::vector<state*> states{};

    //Commandable map
    std::vector<commandable*> commandables{};

    //State controller
    state_controller* catapult_state_machine = nullptr;

    //Ordered input map
    std::vector<readable*> inputs{};

    //State controller map
    std::vector<state_controller*> state_machines{};

    //Subsystem controller
    subsystem_controller* catapult_subsystem = nullptr;

    void init(){
        using namespace BaseCommandable;
        using namespace BaseReadable;
        using namespace BaseAction;

        nautilus_motor = new motor_commandable{NAUTILUS_MOTOR_PORT, NAUTILUS_MOTOR_GEARSET, false,
                                               NAUTILUS_MOTOR_BRAKE_MODE, "nautilus_motor"};

        nautilus_limit_switch = new adi_digital_readable{NAUTILUS_LIMIT_SWITCH_PORT, "nautilus_limit_switch"};
        nautilus_encoder = new motor_encoder_readable{NAUTILUS_MOTOR_PORT, 1.0, "nautilus_motor_encoder"};

        fire_button = get_controller_digital_readable(pros::E_CONTROLLER_MASTER, FIRE_BUTTON);

        hold_nautilus_action = new dead_band_action<double, int16_t>{HOLD_NAUTILUS_UPDATE_PERIOD, nautilus_motor, -90,
                                                                     90, nautilus_encoder, 0, 6000, -6000,
                                                                     "hold_nautilus_action"};
        cock_nautilus_action = new set_value_action<int16_t>{COCK_NAUTILUS_UPDATE_PERIOD, nautilus_motor, 12000,
                                                             "cock_nautilus_action"};
        stop_nautilus_action = new set_value_action<int16_t>{STOP_NAUTILUS_UPDATE_PERIOD, nautilus_motor, 0,
                                                             "stop_nautilus_action"};
        fire_nautilus_action = new set_value_action<int16_t>{FIRE_NAUTILUS_UPDATE_PERIOD, nautilus_motor, 12000,
                                                             "fire_nautilus_action"};

        hold_actions.push_back(hold_nautilus_action);
        cock_actions.push_back(cock_nautilus_action);
        stop_actions.push_back(stop_nautilus_action);
        fire_actions.push_back(fire_nautilus_action);

        cock_to_hold = []() -> bool{
            return nautilus_limit_switch->is_pressed();
        };
        hold_to_fire = []() -> bool{
            return fire_button->is_pressed();
        };
        fire_to_stop = []() -> bool{
            return nautilus_encoder->get_position() >= NAUTILUS_FIRE_THRESHOLD;
        };
        stop_to_cock = []() -> bool{
            return next_cock <= pros::millis();
        };

        cock_transitions.emplace_back(cock_to_hold, hold, "cock_to_hold");
        hold_transitions.emplace_back(hold_to_fire, fire, "hold_to_fire");
        fire_transitions.emplace_back(fire_to_stop, stop, "fire_to_stop");
        stop_transitions.emplace_back(stop_to_cock, cock, "stop_to_cock");

        on_cock_entry = [](state* last_state) -> void{};
        on_hold_entry = [](state* last_state) -> void{
            nautilus_encoder->tare_position();
        };
        on_fire_entry = [](state* last_state) -> void{};
        on_stop_entry = [](state* last_state) -> void{
            next_cock = pros::millis() + NAUTILUS_STOP_TIME;
        };

        cock = new state{cock_actions, cock_transitions, on_cock_entry, "cock"};
        hold = new state{hold_actions, hold_transitions, on_hold_entry, "hold"};
        fire = new state{fire_actions, fire_transitions, on_fire_entry, "fire"};
        stop = new state{stop_actions, stop_transitions, on_stop_entry, "stop"};

        states.push_back(cock);
        states.push_back(hold);
        states.push_back(fire);
        states.push_back(stop);

        commandables.push_back(nautilus_motor);

        catapult_state_machine = new state_controller{CATAPULT_UPDATE_PERIOD, states, commandables, cock,
                                                      "catapult_state_machine"};

        inputs.push_back(nautilus_limit_switch);
        inputs.push_back(nautilus_encoder);

        state_machines.push_back(catapult_state_machine);

        catapult_subsystem = new subsystem_controller{inputs, state_machines, "catapult_subsystem"};
    }

    void destroy(){
        delete (nautilus_motor);

        delete (nautilus_limit_switch);
        delete (nautilus_encoder);
        delete (fire_button);

        delete (hold_nautilus_action);
        delete (cock_nautilus_action);
        delete (stop_nautilus_action);
        delete (fire_nautilus_action);

        delete (cock);
        delete (hold);
        delete (fire);
        delete (stop);

        delete (catapult_state_machine);

        delete (catapult_subsystem);
    }
}
