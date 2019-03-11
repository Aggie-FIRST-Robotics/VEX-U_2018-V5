//
//
//#include "fuego/drive/drive.h"
//
//namespace AFR::VexU::Fuego::Drive{
//    //Commandables
////    BaseCommandable::motor_commandable* front_left_motor = nullptr;
////    BaseCommandable::motor_commandable* front_right_motor = nullptr;
////    BaseCommandable::motor_commandable* back_left_motor = nullptr;
////    BaseCommandable::motor_commandable* back_right_motor = nullptr;
////
////    //Readables
////    BaseReadable::controller_analog_readable* left_stick = nullptr;
////    BaseReadable::controller_analog_readable* right_stick = nullptr;
////
////    //Actions
////    arcade_drive_action* start_front_left_motor = nullptr;
////    arcade_drive_action* start_front_right_motor = nullptr;
////    arcade_drive_action* start_back_right_motor = nullptr;
////    arcade_drive_action* start_back_left_motor = nullptr;
////
////    //Action Map
////    std::vector<action*> start_actions{};
////
////    //Transition vectors
////    std::vector<transition> start_transitions{};
////    //On-state entry functions
////    std::function<void(state*)> on_start_entry{};
////
////    //States
////    state *start = nullptr;
////
////    //State map
////    std::vector<state*> states{};
////
////    //Commandable map
////    std::vector<commandable*> commandables{};
////
////    //State controller
////    state_controller* drive_state_machine = nullptr;
////
////
////    //Ordered input map
////    std::vector<readable*> inputs{};
////
////    //State controller map
////    std::vector<state_controller*> state_machines{};
////
////    subsystem_controller* drive_subsystem = nullptr;
//
//    void init(){
////        using namespace BaseCommandable;
////        using namespace BaseReadable;
////        using namespace BaseAction;
////
////        front_left_motor = new motor_commandable{LEFT_RAIL_MOTOR_A_PORT, LEFT_RAIL_MOTOR_A_GEARSET, true,
////                                                 LEFT_RAIL_MOTOR_A_BRAKE_MODE, "front_left_motor"};
////        front_right_motor = new motor_commandable{RIGHT_RAIL_MOTOR_A_PORT, RIGHT_RAIL_MOTOR_A_GEARSET, false,
////                                                  RIGHT_RAIL_MOTOR_A_BRAKE_MODE, "front_right_motor"};
////        back_left_motor = new motor_commandable{LEFT_RAIL_MOTOR_B_PORT, LEFT_RAIL_MOTOR_B_GEARSET, true,
////                                                LEFT_RAIL_MOTOR_B_BRAKE_MODE, "back_left_motor"};
////        back_right_motor = new motor_commandable{RIGHT_RAIL_MOTOR_B_PORT, RIGHT_RAIL_MOTOR_B_GEARSET, false,
////                                                 RIGHT_RAIL_MOTOR_B_BRAKE_MODE, "back_right_motor"};
////
////        left_stick = get_controller_analog_readable(pros::E_CONTROLLER_MASTER, LEFT_DRIVE_STICK);
////        right_stick = get_controller_analog_readable(pros::E_CONTROLLER_MASTER, RIGHT_DRIVE_STICK);
////
////        start_front_left_motor = new arcade_drive_action{START_FRONT_LEFT_MOTOR_UPDATE_PERIOD, front_left_motor,
////                                                         left_stick, right_stick, false, "start_front_left_motor"};
////        start_front_right_motor = new arcade_drive_action{START_FRONT_RIGHT_MOTOR_UPDATE_PERIOD, front_right_motor,
////                                                          left_stick, right_stick, true, "start_front_right_motor"};
////        start_back_left_motor = new arcade_drive_action{START_BACK_LEFT_MOTOR_UPDATE_PERIOD, back_left_motor,
////                                                        left_stick, right_stick, false, "start_back_left_motor"};
////        start_back_right_motor = new arcade_drive_action{START_BACK_RIGHT_MOTOR_UPDATE_PERIOD, back_right_motor,
////                                                         left_stick, right_stick, true, "start_back_right_motor"};
////
////        on_start_entry = [](state* last_state) -> void{};
////
////        start_actions.push_back(start_front_left_motor);
////        start_actions.push_back(start_front_right_motor);
////        start_actions.push_back(start_back_left_motor);
////        start_actions.push_back(start_back_right_motor);
////
////        start = new state{start_actions, start_transitions, on_start_entry, "start"};
////
////        states.push_back(start);
////
////        commandables.push_back(front_left_motor);
////        commandables.push_back(front_right_motor);
////        commandables.push_back(back_left_motor);
////        commandables.push_back(back_right_motor);
////
////        drive_state_machine = new state_controller(START_UPDATE_PERIOD, states, commandables, start,
////                                                   "drive_state_machine");
////
////        state_machines.push_back(drive_state_machine);
////
////        drive_subsystem = new subsystem_controller(inputs, state_machines, "drive_subsystem");
//    }
//
//    void destroy(){
////        delete (front_left_motor);
////        delete (front_right_motor);
////        delete (back_left_motor);
////        delete (back_right_motor);
////
////        delete (left_stick);
////        delete (right_stick);
////
////        delete (start_front_left_motor);
////        delete (start_front_right_motor);
////        delete (start_back_right_motor);
////        delete (start_back_left_motor);
////
////        delete(start);
////
////        delete(drive_state_machine);
////
////        delete(drive_subsystem);
//    }
//};
