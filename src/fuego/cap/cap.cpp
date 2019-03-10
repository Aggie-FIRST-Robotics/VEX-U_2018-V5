#include "fuego/cap/cap.h"

namespace AFR::VexU::Fuego::Cap{
//    //Commandables
//    BaseCommandable::motor_commandable* left_arm_motor{};
//    BaseCommandable::motor_commandable* right_arm_motor{};
//    BaseCommandable::motor_commandable* elbow_motor{};
//    BaseCommandable::motor_commandable* wrist_motor{};
//
//    BaseCommandable::motor_commandable* intake_motor{};
//
//    BaseCommandable::multi_motor_commandable* arm_motors{};
//
//    //Readables
//    BaseReadable::adi_digital_readable* arm_limit_switch{};
//    BaseReadable::adi_digital_readable* elbow_limit_switch{};
//    BaseReadable::adi_digital_readable* wrist_limit_switch{};
//
//    BaseReadable::motor_encoder_readable* arm_encoder{};
//    BaseReadable::motor_encoder_readable* elbow_encoder{};
//    BaseReadable::motor_encoder_readable* wrist_encoder{};
//
//    BaseReadable::controller_digital_readable* up_button{};
//    BaseReadable::controller_digital_readable* down_button{};
//    BaseReadable::controller_digital_readable* flip_button{};
//    BaseReadable::controller_digital_readable* flip_partner_button{};
//    BaseReadable::controller_digital_readable* score_button{};
//    BaseReadable::controller_digital_readable* intake_button{};
//    BaseReadable::controller_digital_readable* outtake_button{};
//    BaseReadable::controller_digital_readable* reset_button{};
//    BaseReadable::controller_digital_readable* descore_button{};
//
//    //Actions
//    BaseAction::zero_encoder_action<bool, double, int16_t>* arm_zero_action{};
//    BaseAction::zero_encoder_action<bool, double, int16_t>* elbow_zero_action{};
//    BaseAction::zero_encoder_action<bool, double, int16_t>* wrist_zero_action{};
//
//    BaseAction::pid_action<double, int16_t>* arm_pid_action{};
//    BaseAction::pid_action<double, int16_t>* elbow_pid_action{};
//    BaseAction::pid_action<double, int16_t>* wrist_pid_action{};
//
//    BaseAction::set_value_action<int16_t>* intake_suck_action{};
//    BaseAction::set_value_action<int16_t>* intake_hold_action{};
//    BaseAction::set_value_action<int16_t>* intake_spit_action{};
//
//    wrist_flip_action* wrist_flip{};
//
//    //Action Vectors
//    std::vector<action*> storage_actions{};
//    std::vector<action*> down_actions{};
//    std::vector<action*> flip_low_prime_actions{};
//    std::vector<action*> flip_low_actions{};
//    std::vector<action*> hold_actions{};
//    std::vector<action*> flip_high_prime_actions{};
//    std::vector<action*> flip_high_actions{};
//    std::vector<action*> descore_prime_actions{};
//    std::vector<action*> descore_grab_actions{};
//    std::vector<action*> score_prime_actions{};
//    std::vector<action*> score_actions{};
//    std::vector<action*> pull_back_actions{};
//    std::vector<action*> outtake_actions{};
//
//    std::vector<action*> intake_hold_actions{};
//    std::vector<action*> intake_suck_actions{};
//    std::vector<action*> intake_spit_actions{};

    //Transition Functions
    std::function<bool()> all_to_storage{};

    std::function<bool()> storage_to_down{};
    std::function<bool()> storage_to_hold{};

    std::function<bool()> down_to_hold{};
    std::function<bool()> down_to_flip_low_prime{};

    std::function<bool()> flip_low_prime_to_flip_low{};

    std::function<bool()> flip_low_to_down{};

    std::function<bool()> hold_to_down{};
    std::function<bool()> hold_to_flip_high_prime{};
    std::function<bool()> hold_to_descore_prime{};
    std::function<bool()> hold_to_score_prime{};
    std::function<bool()> hold_to_outtake{};

    std::function<bool()> flip_high_prime_to_flip_high{};

    std::function<bool()> flip_high_to_hold{};

    std::function<bool()> descore_prime_to_hold{};
    std::function<bool()> descore_prime_to_descore_grab{};

    std::function<bool()> descore_grab_to_score_prime{};

    std::function<bool()> score_prime_to_hold{};
    std::function<bool()> score_prime_to_score{};

    std::function<bool()> score_to_pull_back{};

    std::function<bool()> pull_back_to_hold{};

    std::function<bool()> outtake_to_hold{};

    std::function<bool()> intake_hold_to_intake_suck{};
    std::function<bool()> intake_hold_to_intake_spit{};

    std::function<bool()> intake_spit_to_intake_hold{};
    std::function<bool()> intake_spit_to_intake_suck{};

    std::function<bool()> intake_suck_to_intake_hold{};

    //Transition Vectors
//    std::vector<transition> storage_transitions{};
//    std::vector<transition> down_transitions{};
//    std::vector<transition> flip_low_prime_transitions{};
//    std::vector<transition> flip_low_transitions{};
//    std::vector<transition> hold_transitions{};
//    std::vector<transition> flip_high_prime_transitions{};
//    std::vector<transition> flip_high_transitions{};
//    std::vector<transition> descore_prime_transitions{};
//    std::vector<transition> descore_grab_transitions{};
//    std::vector<transition> score_prime_transitions{};
//    std::vector<transition> score_transitions{};
//    std::vector<transition> pull_back_transitions{};
//    std::vector<transition> outtake_transitions{};
//
//    std::vector<transition> intake_hold_transitions{};
//    std::vector<transition> intake_suck_transitions{};
//    std::vector<transition> intake_spit_transitions{};

    //On State Entry Functions
    std::function<void(state*)> on_storage_entry{};
    std::function<void(state*)> on_down_entry{};
    std::function<void(state*)> on_flip_low_prime_entry{};
    std::function<void(state*)> on_flip_low_entry{};
    std::function<void(state*)> on_hold_entry{};
    std::function<void(state*)> on_flip_high_prime_entry{};
    std::function<void(state*)> on_flip_high_entry{};
    std::function<void(state*)> on_descore_prime_entry{};
    std::function<void(state*)> on_descore_grab_entry{};
    std::function<void(state*)> on_score_prime_entry{};
    std::function<void(state*)> on_score_entry{};
    std::function<void(state*)> on_pull_back_entry{};
    std::function<void(state*)> on_outtake_entry{};

    std::function<void(state*)> on_intake_hold_entry{};
    std::function<void(state*)> on_intake_suck_entry{};
    std::function<void(state*)> on_intake_spit_entry{};

    //States
    state* storage{};
    state* down{};
    state* flip_low_prime{};
    state* flip_low{};
    state* hold{};
    state* flip_high_prime{};
    state* flip_high{};
    state* descore_prime{};
    state* descore_grab{};
    state* score_prime{};
    state* score{};
    state* pull_back{};
    state* outtake{};

    state* intake_hold{};
    state* intake_suck{};
    state* intake_spit{};

    //State Vector
    std::vector<state*> cap_states{};
    std::vector<state*> intake_states{};

    //Commandable Vector
//    std::vector<commandable*> cap_commandables{};
//    std::vector<commandable*> intake_commandables{};
//
//    //State Controller
//    state_controller* cap_state_machine{};
//    state_controller* intake_state_machine{};
//
//    //Readable Vector
//    std::vector<readable*> readables{};
//
//    //State Controller Vector
//    std::vector<state_controller*> state_controllers{};
//
//    //Subsystem Controller
//    subsystem_controller* cap_subsystem{};

    void init(){
//        using namespace BaseCommandable;
//        using namespace BaseReadable;
//        using namespace BaseAction;
//
//        //Commandables
//        left_arm_motor = new motor_commandable{ARM_LEFT_MOTOR_PORT, ARM_LEFT_GEARSET, false, ARM_LEFT_BRAKE_MODE,
//                                               "left_arm_motor"};
//        right_arm_motor = new motor_commandable{ARM_RIGHT_MOTOR_PORT, ARM_RIGHT_GEARSET, true, ARM_RIGHT_BRAKE_MODE,
//                                                "right_arm_motor"};
//        elbow_motor = new motor_commandable{ELBOW_MOTOR_PORT, ELBOW_GEARSET, false, ELBOW_BRAKE_MODE, "elbow_encoder"};
//        wrist_motor = new motor_commandable{WRIST_MOTOR_PORT, WRIST_GEARSET, true, WRIST_BRAKE_MODE, "wrist_motor"};
//
//        arm_motors = new multi_motor_commandable{"arm_motors"};
//        arm_motors->add_motor(left_arm_motor);
//        arm_motors->add_motor(right_arm_motor);
//
//        intake_motor = new motor_commandable{INTAKE_MOTOR_PORT, INTAKE_GEARSET, false, INTAKE_BRAKE_MODE,
//                                             "intake_motor"};
//
//        //Readables
//        arm_limit_switch = new adi_digital_readable{ARM_LIMIT_SWITCH_PORT, "arm_limit_switch"};
//        elbow_limit_switch = new adi_digital_readable{ELBOW_LIMIT_SWITCH_PORT, "elbow_limit_switch"};
//        wrist_limit_switch = new adi_digital_readable{WRIST_LIMIT_SWITCH_PORT, "wrist_limit_switch"};
//
//        arm_encoder = new motor_encoder_readable{ARM_RIGHT_MOTOR_PORT, 1.0, "arm_encoder"};
//        elbow_encoder = new motor_encoder_readable{ELBOW_MOTOR_PORT, 1.0, "elbow_encoder"};
//        wrist_encoder = new motor_encoder_readable{WRIST_MOTOR_PORT, 1.0, "wrist_encoder"};
//
//        up_button = get_controller_digital_readable(pros::E_CONTROLLER_MASTER, UP_BUTTON);
//        down_button = get_controller_digital_readable(pros::E_CONTROLLER_MASTER, DOWN_BUTTON);
//        flip_button = get_controller_digital_readable(pros::E_CONTROLLER_MASTER, FLIP_BUTTON);
//        flip_partner_button = get_controller_digital_readable(pros::E_CONTROLLER_PARTNER, FLIP_PARTNER_BUTTON);
//        score_button = get_controller_digital_readable(pros::E_CONTROLLER_MASTER, SCORE_BUTTON);
//        intake_button = get_controller_digital_readable(pros::E_CONTROLLER_MASTER, INTAKE_BUTTON);
//        outtake_button = get_controller_digital_readable(pros::E_CONTROLLER_MASTER, OUTTAKE_BUTTON);
//        reset_button = get_controller_digital_readable(pros::E_CONTROLLER_MASTER, RESET_BUTTON);
//        descore_button = get_controller_digital_readable(pros::E_CONTROLLER_MASTER, DESCORE_BUTTON);
//
//        //Actions
//        arm_pid_action = new pid_action<double, int16_t>{10, arm_motors, 100, 1, 0, -12000, 12000, -6000, 6000, 0,
//                                                         arm_encoder, 0, "arm_pid_action"};
//        elbow_pid_action = new pid_action<double, int16_t>{10, elbow_motor, 100, 1, 0, -12000, 12000, -6000, 6000, 0,
//                                                           elbow_encoder, 0, "elbow_pid_action"};
//        wrist_pid_action = new pid_action<double, int16_t>{10, wrist_motor, 50, 0, 0, -12000, 12000, -6000, 6000, 0,
//                                                           wrist_encoder, 0, "wrist_pid_action"};
//
//        arm_zero_action = new zero_encoder_action<bool, double, int16_t>{10, arm_motors, arm_limit_switch, arm_encoder,
//                                                                         true, -6000, arm_pid_action,
//                                                                         "arm_zero_action"};
//        elbow_zero_action = new zero_encoder_action<bool, double, int16_t>{10, elbow_motor, elbow_limit_switch,
//                                                                           elbow_encoder, true, -6000, elbow_pid_action,
//                                                                           "elbow_zero_action"};
//        wrist_zero_action = new zero_encoder_action<bool, double, int16_t>{10, wrist_motor, wrist_limit_switch,
//                                                                           wrist_encoder, true, -6000, wrist_pid_action,
//                                                                           "wrist_zero_action"};
//
//        intake_suck_action = new set_value_action<int16_t>{10, intake_motor, 12000, "intake_con_action"};
//        intake_hold_action = new set_value_action<int16_t>{10, intake_motor, 3000, "intake_hold_action"};
//        intake_spit_action = new set_value_action<int16_t>{10, intake_motor, -12000, "outtake_action"};
//
//        wrist_flip = new wrist_flip_action{10, wrist_pid_action, flip_button, FLIP_TARGET, "wrist_flip"};
//
//        //Action Vectors
//        storage_actions.push_back(arm_zero_action);
//        storage_actions.push_back(elbow_zero_action);
//        storage_actions.push_back(wrist_zero_action);
//
//        down_actions.push_back(arm_pid_action);
//        down_actions.push_back(elbow_pid_action);
//        down_actions.push_back(wrist_pid_action);
//
//        flip_low_actions.push_back(arm_pid_action);
//        flip_low_actions.push_back(elbow_pid_action);
//        flip_low_actions.push_back(wrist_pid_action);
//
//        flip_low_prime_actions.push_back(arm_pid_action);
//        flip_low_prime_actions.push_back(elbow_pid_action);
//        flip_low_prime_actions.push_back(wrist_pid_action);
//
//        hold_actions.push_back(arm_pid_action);
//        hold_actions.push_back(elbow_pid_action);
//        hold_actions.push_back(wrist_pid_action);
//
//        flip_high_prime_actions.push_back(arm_pid_action);
//        flip_high_prime_actions.push_back(elbow_pid_action);
//        flip_high_prime_actions.push_back(wrist_pid_action);
//
//        flip_high_actions.push_back(arm_pid_action);
//        flip_high_actions.push_back(elbow_pid_action);
//        flip_high_actions.push_back(wrist_pid_action);
//
//        descore_prime_actions.push_back(arm_pid_action);
//        descore_prime_actions.push_back(elbow_pid_action);
//        descore_prime_actions.push_back(wrist_pid_action);
//
//        descore_grab_actions.push_back(arm_pid_action);
//        descore_grab_actions.push_back(elbow_pid_action);
//        descore_grab_actions.push_back(wrist_pid_action);
//
//        score_prime_actions.push_back(arm_pid_action);
//        score_prime_actions.push_back(elbow_pid_action);
//        score_prime_actions.push_back(wrist_pid_action);
//
//        score_actions.push_back(arm_pid_action);
//        score_actions.push_back(elbow_pid_action);
//        score_actions.push_back(wrist_pid_action);
//
//        pull_back_actions.push_back(arm_pid_action);
//        pull_back_actions.push_back(elbow_pid_action);
//        pull_back_actions.push_back(wrist_pid_action);
//
//        outtake_actions.push_back(arm_pid_action);
//        outtake_actions.push_back(elbow_pid_action);
//        outtake_actions.push_back(wrist_pid_action);
//
//        intake_hold_actions.push_back(intake_hold_action);
//        intake_suck_actions.push_back(intake_suck_action);
//        intake_spit_actions.push_back(intake_spit_action);
//
//        //Transition Functions
//        all_to_storage = []() -> bool{
//            return reset_button->is_rising_edge();
//        };
//
//        storage_to_down = []() -> bool{
//            return down_button->is_rising_edge();
//        };
//        storage_to_hold = []() -> bool{
//            return up_button->is_rising_edge();
//        };
//
//        down_to_hold = []() -> bool{
//            return up_button->is_rising_edge();
//        };
//        down_to_flip_low_prime = []() -> bool{
//            return flip_button->is_rising_edge() || flip_partner_button->is_rising_edge();
//        };
//
//        flip_low_prime_to_flip_low = []() -> bool{
//            return arm_pid_action->is_in_range(50) && elbow_pid_action->is_in_range(50);
//        };
//
//        flip_low_to_down = []() -> bool{
//            return wrist_pid_action->is_in_range(50);
//        };
//
//        hold_to_down = []() -> bool{
//            return down_button->is_rising_edge();
//        };
//        hold_to_flip_high_prime = []() -> bool{
//            return flip_button->is_rising_edge() || flip_partner_button->is_rising_edge();
//        };
//        hold_to_descore_prime = []() -> bool{
//            return descore_button->is_rising_edge();
//        };
//        hold_to_score_prime = []() -> bool{
//            return score_button->is_rising_edge();
//        };
//        hold_to_outtake = []() -> bool{
//            return outtake_button->is_pressed();
//        };
//
//        flip_high_prime_to_flip_high = []() -> bool{
//            return arm_pid_action->is_in_range(50) && elbow_pid_action->is_in_range(50);
//        };
//
//        flip_high_to_hold = []() -> bool{
//            return wrist_pid_action->is_in_range(50);
//        };
//
//        descore_prime_to_hold = []() -> bool{
//            return down_button->is_rising_edge();
//        };
//        descore_prime_to_descore_grab = []() -> bool{
//            return !descore_button->is_pressed() && arm_pid_action->is_in_range(100) &&
//                   elbow_pid_action->is_in_range(50);
//        };
//
//        descore_grab_to_score_prime = []() -> bool{
//            return arm_pid_action->is_in_range(100) && wrist_pid_action->is_in_range(50);
//        };
//
//        score_prime_to_hold = []() -> bool{
//            return down_button->is_rising_edge();
//        };
//        score_prime_to_score = []() -> bool{
//            return !score_button->is_pressed()
//                   && arm_pid_action->is_in_range(100)
//                   && elbow_pid_action->is_in_range(50)
//                   && wrist_pid_action->is_in_range(50);
//        };
//
//        score_to_pull_back = []() -> bool{
//            return arm_pid_action->is_in_range(100) && elbow_pid_action->is_in_range(50);
//        };
//
//        pull_back_to_hold = []() -> bool{
//            return in_range(PULL_BACK_ARM_LOWER_BOUND, arm_encoder->get_position(), PULL_BACK_ARM_UPPER_BOUND)
//                   && in_range(PULL_BACK_ELBOW_LOWER_BOUND, elbow_encoder->get_position(), PULL_BACK_ELBOW_UPPER_BOUND);
//        };
//
//        outtake_to_hold = []() -> bool{
//            return !outtake_button->is_pressed();
//        };
//
//        intake_hold_to_intake_suck = []() -> bool{
//            return intake_button->is_pressed()
//                   || (down_button->is_pressed() && cap_state_machine->get_current_state() == down)
//                   || (cap_state_machine->get_current_state() == descore_grab);
//        };
//        intake_hold_to_intake_spit = []() -> bool{
//            return outtake_button->is_pressed()
//                   || (cap_state_machine->get_current_state() == pull_back);
//        };
//
//        intake_spit_to_intake_hold = []() -> bool{
//            return !intake_hold_to_intake_spit();
//        };
//        intake_spit_to_intake_suck = []() -> bool{
//            return intake_hold_to_intake_suck();
//        };
//
//        intake_suck_to_intake_hold = []() -> bool{
//            return !intake_hold_to_intake_suck();
//        };
//
//        //Transition Vectors
//        storage_transitions.emplace_back(storage_to_down, down, "storage_to_down");
//        storage_transitions.emplace_back(storage_to_hold, hold, "storage_to_hold");
//
//        down_transitions.emplace_back(down_to_hold, hold, "down_to_hold");
//        down_transitions.emplace_back(down_to_flip_low_prime, flip_low_prime, "down_to_flip_low_prime");
//        down_transitions.emplace_back(all_to_storage, storage, "down_to_storage");
//
//        flip_low_prime_transitions.emplace_back(flip_low_prime_to_flip_low, flip_low, "flip_low_prime_to_flip_low");
//        flip_low_prime_transitions.emplace_back(all_to_storage, storage, "flip_lo_prime_to_storage");
//
//        flip_low_transitions.emplace_back(flip_low_to_down, down, "flip_low_to_down");
//        flip_low_transitions.emplace_back(all_to_storage, storage, "flip_low_to_storage");
//
//        hold_transitions.emplace_back(hold_to_down, down, "hold_to_down");
//        hold_transitions.emplace_back(hold_to_flip_high_prime, flip_high_prime, "hold_to_flip_high_prime");
//        hold_transitions.emplace_back(hold_to_descore_prime, descore_prime, "hold_to_descore_prime");
//        hold_transitions.emplace_back(hold_to_score_prime, score_prime, "hold_to_score_prime");
//        hold_transitions.emplace_back(hold_to_outtake, outtake, "hold_to_outtake");
//        hold_transitions.emplace_back(all_to_storage, storage, "hold_to_storage");
//
//        flip_high_prime_transitions.emplace_back(flip_high_prime_to_flip_high, flip_high,
//                                                 "flip_high_prime_to_flip_high");
//        flip_high_prime_transitions.emplace_back(all_to_storage, storage, "flip_high_prime_to_storage");
//
//        flip_high_transitions.emplace_back(flip_high_to_hold, hold, "flip_high_to_hold");
//        flip_high_transitions.emplace_back(all_to_storage, storage, "flip_high_to_storage");
//
//        descore_prime_transitions.emplace_back(descore_prime_to_hold, hold, "descore_prime_to_hold");
//        descore_prime_transitions.emplace_back(descore_prime_to_descore_grab, descore_grab,
//                                               "descore_prime_to_descore_grab");
//        descore_prime_transitions.emplace_back(all_to_storage, storage, "descore_prime_to_storage");
//
//        descore_grab_transitions.emplace_back(descore_grab_to_score_prime, score_prime, "descore_grab_to_score_prime");
//        descore_grab_transitions.emplace_back(all_to_storage, storage, "descore_grab_to_storage");
//
//        score_prime_transitions.emplace_back(score_prime_to_hold, hold, "score_prime_to_hold");
//        score_prime_transitions.emplace_back(score_prime_to_score, score, "score_prime_to_score");
//        score_prime_transitions.emplace_back(all_to_storage, storage, "score_prime_to_storage");
//
//        score_transitions.emplace_back(score_to_pull_back, pull_back, "score_to_pull_back");
//        score_transitions.emplace_back(all_to_storage, storage, "score_to_storage");
//
//        pull_back_transitions.emplace_back(pull_back_to_hold, hold, "pull_back_to_hold");
//        pull_back_transitions.emplace_back(all_to_storage, storage, "pull_back_to_storage");
//
//        outtake_transitions.emplace_back(outtake_to_hold, hold, "outtake_to_hold");
//        outtake_transitions.emplace_back(all_to_storage, storage, "outtake_to_storage");
//
//        intake_hold_transitions.emplace_back(intake_hold_to_intake_suck, intake_suck, "intake_hold_to_intake_suck");
//        intake_hold_transitions.emplace_back(intake_hold_to_intake_spit, intake_spit, "intake_hold_to_intake_spit");
//
//        intake_spit_transitions.emplace_back(intake_spit_to_intake_hold, intake_hold, "intake_spit_to_intake_hold");
//        intake_spit_transitions.emplace_back(intake_spit_to_intake_suck, intake_suck, "intake_spit_to_intake_suck");
//
//        intake_suck_transitions.emplace_back(intake_suck_to_intake_hold, intake_hold, "intake_suck_to_intake_hold");

        //On State Entry Functions
        on_storage_entry = [](state* last_state) -> void{
            arm_pid_action->disable();
            elbow_pid_action->disable();
            wrist_flip->reset();
        };
        on_down_entry = [](state* last_state) -> void{
            arm_pid_action->set_target(DOWN_ARM_TARGET);
            elbow_pid_action->set_target(DOWN_ELBOW_TARGET);
            if(last_state != flip_low){
                wrist_flip->reset();
            }
        };
        on_flip_low_prime_entry = [](state* last_state) -> void{
            arm_pid_action->set_target(FLIP_LOW_PRIME_ARM_TARGET);
            elbow_pid_action->set_target(FLIP_LOW_PRIME_ELBOW_TARGET);
        };
        on_flip_low_entry = [](state* last_state) -> void{
            arm_pid_action->set_target(FLIP_LOW_ARM_TARGET);
            elbow_pid_action->set_target(FLIP_LOW_ELBOW_TARGET);
            wrist_flip->flip();
        };
        on_hold_entry = [](state* last_state) -> void{
            arm_pid_action->set_target(HOLD_ARM_TARGET);
            elbow_pid_action->set_target(HOLD_ELBOW_TARGET);
        };
        on_flip_high_prime_entry = [](state* last_state) -> void{
            arm_pid_action->set_target(FLIP_HIGH_PRIME_ARM_TARGET);
            elbow_pid_action->set_target(FLIP_HIGH_PRIME_ELBOW_TARGET);
        };
        on_flip_high_entry = [](state* last_state) -> void{
            arm_pid_action->set_target(FLIP_HIGH_ARM_TARGET);
            elbow_pid_action->set_target(FLIP_HIGH_ELBOW_TARGET);
            wrist_flip->flip();
        };
        on_descore_prime_entry = [](state* last_state) -> void{
            arm_pid_action->set_target(DESCORE_PRIME_ARM_TARGET);
            elbow_pid_action->set_target(DESCORE_PRIME_ELBOW_TARGET);
        };
        on_descore_grab_entry = [](state* last_state) -> void{
            arm_pid_action->set_target(DESCORE_GRAB_ARM_TARGET);
            elbow_pid_action->set_target(DESCORE_GRAB_ELBOW_TARGET);
        };
        on_score_prime_entry = [](state* last_state) -> void{
            arm_pid_action->set_target(SCORE_PRIME_ARM_TARGET);
            elbow_pid_action->set_target(SCORE_PRIME_ELBOW_TARGET);
            if(last_state == descore_grab){
                wrist_flip->flip();
            }
        };
        on_score_entry = [](state* last_state) -> void{
            arm_pid_action->set_target(SCORE_ARM_TARGET);
            elbow_pid_action->set_target(SCORE_ELBOW_TARGET);
        };
        on_pull_back_entry = [](state* last_state) -> void{
            arm_pid_action->set_target(PULL_BACK_ARM_TARGET);
            elbow_pid_action->set_target(PULL_BACK_ELBOW_TARGET);
        };
        on_outtake_entry = [](state* last_state) -> void{
            arm_pid_action->set_target(OUTTAKE_ARM_TARGET);
            elbow_pid_action->set_target(OUTTAKE_ELBOW_TARGET);
        };

        on_intake_hold_entry = [](state* last_state) -> void{};
        on_intake_suck_entry = [](state* last_state) -> void{};
        on_intake_spit_entry = [](state* last_state) -> void{};

        //States
//        storage = new state{storage_actions, storage_transitions, on_storage_entry, "storage"};
//        down = new state{down_actions, down_transitions, on_down_entry, "down"};
//        flip_low_prime = new state{flip_low_prime_actions, flip_low_prime_transitions, on_flip_low_prime_entry,
//                                   "flip_low_prime"};
//        flip_low = new state{flip_low_actions, flip_low_transitions, on_flip_low_entry, "flip_low"};
//        hold = new state{hold_actions, hold_transitions, on_hold_entry, "hold"};
//        flip_high_prime = new state{flip_high_prime_actions, flip_high_prime_transitions, on_flip_high_prime_entry,
//                                    "flip_high_prime"};
//        flip_high = new state{flip_high_actions, flip_high_transitions, on_flip_high_entry, "flip_high"};
//        descore_prime = new state{descore_prime_actions, descore_prime_transitions, on_descore_prime_entry,
//                                  "descore_prime"};
//        descore_grab = new state{descore_grab_actions, descore_grab_transitions, on_descore_grab_entry, "descore_grab"};
//        score_prime = new state{score_prime_actions, score_prime_transitions, on_score_prime_entry, "score_prime"};
//        score = new state{score_actions, score_transitions, on_score_entry, "score"};
//        pull_back = new state{pull_back_actions, pull_back_transitions, on_pull_back_entry, "pull_back"};
//        outtake = new state{outtake_actions, outtake_transitions, on_outtake_entry, "outtake"};
//
//        intake_hold = new state{intake_hold_actions, intake_hold_transitions, on_intake_hold_entry, "intake_hold"};
//        intake_suck = new state{intake_suck_actions, intake_suck_transitions, on_intake_suck_entry, "intake_suck"};
//        intake_spit = new state{intake_spit_actions, intake_spit_transitions, on_intake_spit_entry, "intake_spit"};

        //State vector
        cap_states.push_back(storage);
        cap_states.push_back(down);
        cap_states.push_back(flip_low_prime);
        cap_states.push_back(flip_low);
        cap_states.push_back(hold);
        cap_states.push_back(flip_high_prime);
        cap_states.push_back(flip_high);
        cap_states.push_back(descore_prime);
        cap_states.push_back(descore_grab);
        cap_states.push_back(score_prime);
        cap_states.push_back(score);
        cap_states.push_back(pull_back);
        cap_states.push_back(outtake);

        intake_states.push_back(intake_hold);
        intake_states.push_back(intake_suck);
        intake_states.push_back(intake_spit);

//        cap_commandables.push_back(left_arm_motor);
//        cap_commandables.push_back(right_arm_motor);
//        cap_commandables.push_back(elbow_motor);
//        cap_commandables.push_back(wrist_motor);
//        cap_commandables.push_back(arm_motors);
//
//        intake_commandables.push_back(intake_motor);
//
//        cap_state_machine = new state_controller{10, cap_states, cap_commandables, storage, "cap_state_machine"};
//        intake_state_machine = new state_controller{10, intake_states, intake_commandables, intake_hold,
//                                                    "intake_state_machine"};
//
//        readables.push_back(arm_limit_switch);
//        readables.push_back(elbow_limit_switch);
//        readables.push_back(wrist_limit_switch);
//        readables.push_back(arm_encoder);
//        readables.push_back(elbow_encoder);
//        readables.push_back(wrist_limit_switch);
//
//        state_controllers.push_back(cap_state_machine);
//        state_controllers.push_back(intake_state_machine);
//
//        cap_subsystem = new subsystem_controller{readables, state_controllers, "cap_subsystem"};
    }
}
