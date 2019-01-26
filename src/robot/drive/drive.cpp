
#include <robot/drive/drive.h>

#include "robot/drive/drive.h"

namespace AFR::VexU::Robot::Drive {
    //Commandables
    BaseCommandable::motor_commandable *topleftmotor = nullptr;
    BaseCommandable::motor_commandable *toprightmotor = nullptr;
    BaseCommandable::motor_commandable *bottomleftmotor = nullptr;
    BaseCommandable::motor_commandable *bottomrightmotor = nullptr;


    //Actions
    BaseAction::set_value_action<int16_t> *start_topleftmotor = nullptr;
    BaseAction::set_value_action<int16_t> *start_toprightmotor = nullptr;
    BaseAction::set_value_action<int16_t> *start_bottomrightmotor = nullptr;
    BaseAction::set_value_action<int16_t> *start_bottomleftmotor = nullptr;


    //Action Map
    std::unordered_map<std::string, action &> start_map{};

    //Transition functions
    std::function<error_t(bool &)> to_start{};

    //Transition vectors
    std::vector<transition> start_transitions{};
    //On-state entry functions
    std::function<error_t(const std::string &)> on_start_entry{};


    //States
    state *start = nullptr;


    //State map
    std::unordered_map<std::string, state &> state_map{};

    //Commandable map
    std::unordered_map<std::string, commandable &> commandable_map{};

    //State controller
    state_controller *drive_state_machine = nullptr;


    //Ordered input map
    std::unordered_map<std::string, ordered_input &> inputs{};

    //State controller map
    std::unordered_map<std::string, state_controller &> state_machines{};


    void arcadedrive(const std::int32_t &leftpower_, const std::int32_t &rightpower_) {
        topleftmotor.set_value(rightpower_ - leftpower_);
        bottomleftmotor.set_value(rightpower_ - leftpower_);
        toprightmotor.set_value(rightpower_ + leftpower_);
        bottomrightmotor.set_value(rightpower_ + leftpower_);
    }

    void init() {
        using namespace BaseCommandable;
        using namespace BaseReadable;
        using namespace BaseAction;

        topleftmotor = new motor_commandable{LEFT_RAIL_MOTOR_A_PORT, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_BRAKE_BRAKE, nullptr};
        toprightmotor = new BaseCommandable::motor_commandable{RIGHT_RAIL_MOTOR_A_PORT, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_BRAKE_BRAKE, nullptr};
        bottomleftmotor = new BaseCommandable::motor_commandable{LEFT_RAIL_MOTOR_B_PORT, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_BRAKE_BRAKE, nullptr};
        bottomrightmotor = new BaseCommandable::motor_commandable{RIGHT_RAIL_MOTOR_B_PROT, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_BRAKE_BRAKE, nullptr};


        start_topleftmotor = new set_value_action<int16_t>{START_BOTTOMLEFTMOTOR_UPDATE_PERIOD, *topleftmotor, 0};
        start_toprightmotor = new set_value_action<int16_t>{START_TOPRIGHTMOTOR_UPDATE_PERIOD, *toprightmotor, 0};
        start_bottomleftmotor = new set_value_action<int16_t>{START_BOTTOMLEFTMOTOR_UPDATE_PERIOD, *bottomleftmotor, 0};
        start_bottomrightmotor = new set_value_action<int16_t>{START_BOTTOMRIGHTMOTOR_UPDATE_PERIOD, *bottomrightmotor, 0};

        to_start=[](bool& result) -> error_t{

                return SUCCESS;
        };
        start_transitions.emplace_back(to_start, "to_start");

        on_start_entry=[](const std::string& last_state) -> error_t{
            return SUCCESS;
        };


        start_map.emplace("start_topleftmotor", *start_topleftmotor);
        start_map.emplace("start_toprightmotor", *start_toprightmotor);
        start_map.emplace("start_bottomleftmotor", *start_bottomleftmotor);
        start_map.emplace("start_bottomrightmotor", *start_bottomrightmotor);
      //  AFR::VexU::Robot::BaseAction::set_value_action<int> stop_action_int{800, int_motor, 0};
        start = new state{start_map, start_transitions, on_start_entry};
        state_map.emplace("start", *start);

        commandable_map.emplace("topleftmotor", *topleftmotor);
        commandable_map.emplace("toprightmotor", *toprightmotor);
        commandable_map.emplace("bottomleftmotor", *bottomleftmotor);
        commandable_map.emplace("bottomrightmotor", *bottomrightmotor);

        drive_state_machine = new state_controller(START_UPDATE_PERIOD, state_map, commandable_map, "start" );

        state_machines.emplace("main", *drive_state_machine);

        drive_subsystem = new subsystem_controller(inputs, state_machines);



    }

    void destroy(){
        delete(topleftmotor);
        delete(toprightmotor);
        delete(bottomleftmotor);
        delete(bottomrightmotor);
        delete(start_topleftmotor);
        delete(start_toprightmotor);
        delete(start_bottomrightmotor);
        delete(start_bottomleftmotor);
        delete(start);
        delete(drive_state_machine);
        delete(drive_subsystem);


    }



};



