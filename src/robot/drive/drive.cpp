#include "afr-vexu-lib/base-readable/controller_readable.h"
#include "robot/drive/arcade_drive_action.h"
#include "robot/drive/drive.h"

namespace AFR::VexU::Robot::Drive {
    //Commandables
    BaseCommandable::motor_commandable *topleftmotor = nullptr;
    BaseCommandable::motor_commandable *toprightmotor = nullptr;
    BaseCommandable::motor_commandable *bottomleftmotor = nullptr;
    BaseCommandable::motor_commandable *bottomrightmotor = nullptr;
    //Readables
    BaseReadable::controller_readable *controller = nullptr;

    //Actions
    arcade_drive_action* start_topleftmotor = nullptr;
    arcade_drive_action* start_toprightmotor = nullptr;
    arcade_drive_action* start_bottomrightmotor = nullptr;
    arcade_drive_action* start_bottomleftmotor = nullptr;


    //Action Map
    std::unordered_map<std::string, action &> start_map{};

    //Transition functions
    std::function<error_t(bool &)> to_start{};

    //Transition vectors
    std::vector<transition> start_transitions{};
    //On-state entry functions
    std::function<error_t(const std::string &)> on_start_entry{};

    //Ordered inputs
    ordered_input* joystick_order = nullptr;

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

    subsystem_controller* drive_subsystem = nullptr;


    /*void arcadedrive(const std::int32_t &leftpower_, const std::int32_t &rightpower_) {
        topleftmotor->set_value(rightpower_ - leftpower_);
        bottomleftmotor->set_value(rightpower_ - leftpower_);
        toprightmotor->set_value(rightpower_ + leftpower_);
        bottomrightmotor->set_value(rightpower_ + leftpower_);
    }*/

    void init(){
        using namespace BaseCommandable;
        using namespace BaseReadable;
        using namespace BaseAction;

        topleftmotor = new motor_commandable{LEFT_RAIL_MOTOR_A_PORT, LEFT_RAIL_MOTOR_A_GEARSET, true,
                                             LEFT_RAIL_MOTOR_A_BRAKE_MODE, nullptr};
        toprightmotor = new motor_commandable{RIGHT_RAIL_MOTOR_A_PORT, RIGHT_RAIL_MOTOR_A_GEARSET, true,
                                              RIGHT_RAIL_MOTOR_A_BRAKE_MODE, nullptr};
        bottomleftmotor = new motor_commandable{LEFT_RAIL_MOTOR_B_PORT, LEFT_RAIL_MOTOR_B_GEARSET, true,
                                                LEFT_RAIL_MOTOR_B_BRAKE_MODE, nullptr};
        bottomrightmotor = new motor_commandable{RIGHT_RAIL_MOTOR_B_PORT, RIGHT_RAIL_MOTOR_B_GEARSET, true,
                                                 RIGHT_RAIL_MOTOR_B_BRAKE_MODE, nullptr};

        start_topleftmotor = new arcade_drive_action{START_BOTTOM_LEFT_MOTOR_UPDATE_PERIOD, *topleftmotor,
                                                     LEFT_DRIVE_STICK, RIGHT_DRIVE_STICK, false};
        start_toprightmotor = new arcade_drive_action{START_BOTTOM_LEFT_MOTOR_UPDATE_PERIOD, *toprightmotor,
                                                      LEFT_DRIVE_STICK, RIGHT_DRIVE_STICK, true};
        start_bottomleftmotor = new arcade_drive_action{START_BOTTOM_LEFT_MOTOR_UPDATE_PERIOD, *bottomrightmotor,
                                                        LEFT_DRIVE_STICK, RIGHT_DRIVE_STICK, false};
        start_bottomrightmotor = new arcade_drive_action{START_BOTTOM_LEFT_MOTOR_UPDATE_PERIOD, *bottomrightmotor,
                                                         LEFT_DRIVE_STICK, RIGHT_DRIVE_STICK, true};

        to_start=[](bool& result) -> error_t{
                return SUCCESS;
        };
        start_transitions.emplace_back(to_start, "start");

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

//        joystick_order = new ordered_input{1, controller};

        //inputs.emplace("controller", *controller);



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



