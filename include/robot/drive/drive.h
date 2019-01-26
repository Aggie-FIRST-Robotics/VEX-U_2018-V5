//
// Created by aamhi on 11/30/2018.
//
//#include <cmath>

#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "robot/robot.h"
#include "afr-vexu-lib/subsystem_controller.h"
#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "afr-vexu-lib/base-action/set_value_action.h"
#include "afr-vexu-lib/base-readable/adi_digital_readable.h"
#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"
#ifndef VEX_U_2018_V5_DRIVE_H
#define VEX_U_2018_V5_DRIVE_H
#endif //VEX_U_2018_V5_DRIVE_H

namespace AFR::VexU::Robot::Drive {

    const scheduled_update_t START_TOPLEFTMOTOR_UPDATE_PERIOD = 100;
    const scheduled_update_t START_UPDATE_PERIOD = 100;
    const scheduled_update_t START_TOPRIGHTMOTOR_UPDATE_PERIOD = 100;
    const scheduled_update_t START_BOTTOMLEFTMOTOR_UPDATE_PERIOD = 100;
    const scheduled_update_t START_BOTTOMRIGHTMOTOR_UPDATE_PERIOD = 100;
    //Commandables
    BaseCommandable::motor_commandable* topleftmotor = nullptr;
    BaseCommandable::motor_commandable* toprightmotor = nullptr;
    BaseCommandable::motor_commandable* bottomleftmotor = nullptr;
    BaseCommandable::motor_commandable* bottomrightmotor = nullptr;



    //Actions
    BaseAction::set_value_action<int16_t>*start_topleftmotor = nullptr;
    BaseAction::set_value_action<int16_t>*start_toprightmotor = nullptr;
    BaseAction::set_value_action<int16_t>*start_bottomrightmotor = nullptr;
    BaseAction::set_value_action<int16_t>*start_bottomleftmotor = nullptr;


    //Action Map
    std::unordered_map<std::string, action&> start_map{};

    //Transition functions
    std::function<error_t(bool&)> to_start{};

    //Transition vectors
    std::vector<transition> start_transitions{};
    //On-state entry functions
    std::function<error_t(const std::string&)> on_start_entry{};


    //States
    state* start = nullptr;


    //State map
    std::unordered_map<std::string, state&> state_map{};

    //Commandable map
    std::unordered_map<std::string, commandable&> commandable_map{};

    //State controller
    state_controller* drive_state_machine = nullptr;



    //Ordered input map
    std::unordered_map<std::string, ordered_input&> inputs{};

    //State controller map
    std::unordered_map<std::string, state_controller&> state_machines{};

    //Subsystem controller
    subsystem_controller* drive_subsystem = nullptr;
}

       void init();
       void arcadedrive(const std::int32_t &leftpower_, const std::int32_t &rightpower_);
       void destroy();



}
