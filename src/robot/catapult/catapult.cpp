#include "afr-vexu-lib/base-readable/controller_readable.h"
#include "robot/catapult/catapult.h"
#include "robot/robot.h"

namespace AFR::VexU::Robot::Catapult{
    std::chrono::steady_clock::time_point next_cock = std::chrono::steady_clock::now();

    //Commandables
    BaseCommandable::motor_commandable* nautilus_motor = nullptr;

    //Readables
    BaseReadable::adi_digital_readable* nautilus_limit_switch = nullptr;
    BaseReadable::motor_encoder_readable* nautilus_encoder = nullptr;

    //Actions
    BaseAction::set_value_action<int16_t>* hold_nautilus_action = nullptr;
    BaseAction::set_value_action<int16_t>* cock_nautilus_action = nullptr;
    BaseAction::set_value_action<int16_t>* stop_nautilus_action = nullptr;
    BaseAction::set_value_action<int16_t>* fire_nautilus_action = nullptr;

    //Action Maps
    std::unordered_map<std::string, action&> hold_action_map{};
    std::unordered_map<std::string, action&> cock_action_map{};
    std::unordered_map<std::string, action&> stop_action_map{};
    std::unordered_map<std::string, action&> fire_action_map{};

    //Transition functions
    std::function<error_t(bool&)> cock_to_hold{};
    std::function<error_t(bool&)> hold_to_fire{};
    std::function<error_t(bool&)> fire_to_stop{};
    std::function<error_t(bool&)> stop_to_cock{};

    //Transition vectors
    std::vector<transition> cock_transitions{};
    std::vector<transition> hold_transitions{};
    std::vector<transition> fire_transitions{};
    std::vector<transition> stop_transitions{};

    //On-state entry functions
    std::function<error_t(const std::string&)> on_cock_entry{};
    std::function<error_t(const std::string&)> on_hold_entry{};
    std::function<error_t(const std::string&)> on_fire_entry{};
    std::function<error_t(const std::string&)> on_stop_entry{};

    //States
    state* cock = nullptr;
    state* hold = nullptr;
    state* fire = nullptr;
    state* stop = nullptr;

    //State map
    std::unordered_map<std::string, state&> state_map{};

    //Commandable map
    std::unordered_map<std::string, commandable&> commandable_map{};

    //State controller
    state_controller* catapult_state_machine = nullptr;

    //Ordered inputs
    ordered_input* nautilus_limit_switch_order = nullptr;
    ordered_input* nautilus_encoder_order = nullptr;

    //Ordered input map
    std::unordered_map<std::string, ordered_input&> inputs{};

    //State controller map
    std::unordered_map<std::string, state_controller&> state_machines{};

    //Subsystem controller
    subsystem_controller* catapult_subsystem = nullptr;

    void init(){
        using namespace BaseCommandable;
        using namespace BaseReadable;
        using namespace BaseAction;

        nautilus_motor = new motor_commandable{
                NAUTILUS_MOTOR_PORT,
                pros::E_MOTOR_GEARSET_INVALID,
                false,
                pros::E_MOTOR_BRAKE_INVALID
        };

        nautilus_limit_switch = new adi_digital_readable{LIMIT_SWITCH_UPDATE_PERIOD, NAUTILUS_LIMIT_SWITCH_PORT};
        nautilus_encoder = new motor_encoder_readable{
                NAUTILUS_MOTOR_PORT,
                pros::E_MOTOR_GEARSET_INVALID,
                false,
                1.0,
                ENCODER_UPDATE_PERIOD
        };

        hold_nautilus_action = new set_value_action<int16_t>{HOLD_NAUTILUS_UPDATE_PERIOD, *nautilus_motor, -10};
        cock_nautilus_action = new set_value_action<int16_t>{COCK_NAUTILUS_UPDATE_PERIOD, *nautilus_motor, 50};
        stop_nautilus_action = new set_value_action<int16_t>{STOP_NAUTILUS_UPDATE_PERIOD, *nautilus_motor, 0};
        fire_nautilus_action = new set_value_action<int16_t>{FIRE_NAUTILUS_UPDATE_PERIOD, *nautilus_motor, 100};

        hold_action_map.emplace("hold_action_nautilus", *hold_nautilus_action);
        cock_action_map.emplace("cock_action_nautilus", *cock_nautilus_action);
        stop_action_map.emplace("stop_action_nautilus", *stop_nautilus_action);
        fire_action_map.emplace("fire_action_nautilus", *fire_nautilus_action);

        cock_to_hold = [](bool& result) -> error_t{
            std::any out{};
            AFR_VEXU_INTERNAL_CALL(nautilus_limit_switch->get_value(out));
            result = std::any_cast<bool>(out);
            AFR_VEXU_INTERNAL_CALL(nautilus_encoder->tare_position());
            return SUCCESS;
        };
        hold_to_fire = [](bool& result) -> error_t{
            bool val = false;
//            AFR_VEXU_INTERNAL_CALL(Controller::driver_controller->digital_is_pressed(FIRE_BUTTON, val));
            result = val;
            return SUCCESS;
        };
        fire_to_stop = [](bool& result) -> error_t{
            double val{};
            AFR_VEXU_INTERNAL_CALL(nautilus_encoder->get_position(val));
            result = val >= NAUTILUS_FIRE_THRESHOLD;
            return SUCCESS;
        };
        stop_to_cock = [](bool& result) -> error_t{
            result = next_cock <= std::chrono::steady_clock::now();
            return SUCCESS;
        };

        cock_transitions.emplace_back(cock_to_hold, "hold");
        hold_transitions.emplace_back(hold_to_fire, "fire");
        fire_transitions.emplace_back(fire_to_stop, "stop");
        stop_transitions.emplace_back(stop_to_cock, "cock");

        on_cock_entry = [](const std::string& last_state) -> error_t{
            return SUCCESS;
        };
        on_hold_entry = [](const std::string& last_state) -> error_t{
            return SUCCESS;
        };
        on_fire_entry = [](const std::string& last_state) -> error_t{
            return SUCCESS;
        };
        on_stop_entry = [](const std::string& last_state) -> error_t{
            next_cock = std::chrono::steady_clock::now() +
                    std::chrono::duration<scheduled_update_t, scheduled_res_t>{NAUTILUS_STOP_TIME};
            return SUCCESS;
        };

        cock = new state{cock_action_map, cock_transitions, on_cock_entry};
        hold = new state{hold_action_map, hold_transitions, on_hold_entry};
        fire = new state{fire_action_map, fire_transitions, on_fire_entry};
        stop = new state{stop_action_map, stop_transitions, on_stop_entry};

        state_map.emplace("cock", *cock);
        state_map.emplace("hold", *hold);
        state_map.emplace("fire", *fire);
        state_map.emplace("stop", *stop);

        commandable_map.emplace("nautilus_motor", *nautilus_motor);

        catapult_state_machine = new state_controller{CATAPULT_UPDATE_PERIOD, state_map, commandable_map, "cock"};

        nautilus_limit_switch_order = new ordered_input{NAUTILUS_LIMIT_SWITCH_ORDER, nautilus_limit_switch};
        nautilus_encoder_order = new ordered_input{NAUTILUS_ENCODER_ORDER, nautilus_encoder};

        inputs.emplace("nautilus_limit_switch", *nautilus_limit_switch_order);
        inputs.emplace("nautilus_encoder", *nautilus_encoder_order);

        state_machines.emplace("main", *catapult_state_machine);

        catapult_subsystem = new subsystem_controller{inputs, state_machines};
    }

    void destroy(){
        delete (nautilus_motor);

        delete (nautilus_limit_switch);
        delete (nautilus_encoder);

        delete (hold_nautilus_action);
        delete (cock_nautilus_action);
        delete (stop_nautilus_action);
        delete (fire_nautilus_action);

        delete (cock);
        delete (hold);
        delete (fire);
        delete (stop);

        delete (catapult_state_machine);

        delete (nautilus_limit_switch_order);
        delete (nautilus_encoder_order);

        delete (catapult_subsystem);
    }
}
