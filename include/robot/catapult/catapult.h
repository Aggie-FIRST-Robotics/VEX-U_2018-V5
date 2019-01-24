#ifndef VEX_U_2018_V5_CATAPULT_H
#define VEX_U_2018_V5_CATAPULT_H

#include "afr-vexu-lib/subsystem_controller.h"
#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "afr-vexu-lib/base-action/set_value_action.h"
#include "afr-vexu-lib/base-readable/adi_digital_readable.h"
#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"

namespace AFR::VexU::Robot::Catapult{
    const scheduled_update_t LIMIT_SWITCH_UPDATE_PERIOD = 100;
    const scheduled_update_t ENCODER_UPDATE_PERIOD = 100;

    const scheduled_update_t HOLD_NAUTILUS_UPDATE_PERIOD = 100;
    const scheduled_update_t COCK_NAUTILUS_UPDATE_PERIOD = 100;
    const scheduled_update_t STOP_NAUTILUS_UPDATE_PERIOD = 100;
    const scheduled_update_t FIRE_NAUTILUS_UPDATE_PERIOD = 100;

    const scheduled_update_t CATAPULT_UPDATE_PERIOD = 100;

    const order_t NAUTILUS_LIMIT_SWITCH_ORDER = 1;
    const order_t NAUTILUS_ENCODER_ORDER = 1;

    const double NAUTILUS_FIRE_THRESHOLD = 100;
    const scheduled_update_t NAUTILUS_STOP_TIME = 250;

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

    void init();
    void destroy();
}

#endif //VEX_U_2018_V5_CATAPULT_H
