//
// Created by aamhi on 11/30/2018.
//
//#include <cmath>

#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "robot/robot.h"
#ifndef VEX_U_2018_V5_DRIVE_H
#define VEX_U_2018_V5_DRIVE_H
#endif //VEX_U_2018_V5_DRIVE_H

namespace AFR::VexU::Robot::Drive {
    //Commandables
    BaseCommandable::motor_commandable topleftmotor = nullptr;
    BaseCommandable::motor_commandable toprightmotor = nullptr;
    BaseCommandable::motor_commandable bottomleftmotor = nullptr;
    BaseCommandable::motor_commandable bottomrightmotor = nullptr;


    //Actions
    BaseAction::set_value_action<int16_t>*start_topleftmotor = nullptr;
    BaseAction::set_value_action<int16_t>*start_toprightmotor = nullptr;
    BaseAction::set_value_action<int16_t>*start_bottomrightmotor = nullptr;
    BaseAction::set_value_action<int16_t>*start_bottomleftmotor = nullptr;


    //Action Map
    std::unordered_map<std::string, action&> start_topleftmotor_map{};
    std::unordered_map<std::string, action&> start_toprightmotor_map{};
    std::unordered_map<std::string, action&> start_bottomrightmotor_map{};
    std::unordered_map<std::string, action&> start_bottomleftmotor_map{};

    //On-state entry functions
    std::function<error_t(std::string&)> on_start_entry{};


    //States
    state* start = nullptr;


    //State map
    std::unordered_map<std::string, state&> state_map{};

    //Commandable map
    std::unordered_map<std::string, commandable&> commandable_map{};

    //State controller
    state_controller* catapult_State_machine = nullptr;

    //Ordered inputs
    ordered_input* nautalus_limit_switch_order = nullptr;

    //Ordered input map
    std::unordered_map<std::string, ordered_input&> inputs{};

    //State controller map
    std::unordered_map<std::string, state_controller&> state_machines{};

    //Subsystem controller
    subsystem_controller* drive_subsystem = nullptr;
}
    void init();


    class drive {

    public:
       // std::int32_t topleftmotorport, toprightmotorport, bottomleftmotorport, bottomrightmotorport;

       drive();
       void arcadedrive(const std::int32_t &leftpower_, const std::int32_t &rightpower_);

    private:
//        AFR::VexU::BaseCommandable::motor_commandable topleftmotor;
//        AFR::VexU::BaseCommandable::motor_commandable toprightmotor;
//        AFR::VexU::BaseCommandable::motor_commandable bottomleftmotor;
//        AFR::VexU::BaseCommandable::motor_commandable bottomrightmotor;


    };


}
