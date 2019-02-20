#include "afr-vexu-lib/base-action/intake_control_action.h"
#include "afr-vexu-lib/base-action/pid_action.h"
#include "afr-vexu-lib/base-readable/controller_readable.h"
#include "afr-vexu-lib/base-commandable/multi_motor_commandable.h"
#include "robot/cap/cap.h"
#include "robot/robot.h"

namespace AFR::VexU::Robot::Cap {
    scheduled_update_t score_timer = 0;
    scheduled_update_t limit_timer = 0;

    template<typename T>
    bool in_range(const T& lower, const T& val, const T& upper){
        return val >= lower && val <= upper;
    }

    //Commandables
    BaseCommandable::motor_commandable* elevator_motor = nullptr;
    BaseCommandable::motor_commandable* arm_left_motor = nullptr;
    BaseCommandable::motor_commandable* arm_right_motor = nullptr;
    BaseCommandable::motor_commandable* intake_motor = nullptr;
    BaseCommandable::multi_motor_commandable* arm_motors = nullptr;

    //Readables
//    BaseReadable::adi_digital_readable* arm_limit_switch_left = nullptr;
    BaseReadable::adi_digital_readable* arm_limit_switch_right = nullptr;
    BaseReadable::adi_digital_readable* elevator_limit_switch = nullptr;
    BaseReadable::adi_digital_readable* vee_limit_switch = nullptr;
    BaseReadable::motor_encoder_readable* arm_encoder = nullptr;
    BaseReadable::motor_encoder_readable* elevator_encoder = nullptr;

    BaseReadable::controller_digital_readable* intake_button = nullptr;
    BaseReadable::controller_digital_readable* outtake_button = nullptr;
    BaseReadable::controller_digital_readable* flip_button = nullptr;
    BaseReadable::controller_digital_readable* angle_button = nullptr;
    BaseReadable::controller_digital_readable* low_button = nullptr;
    BaseReadable::controller_digital_readable* high_button = nullptr;
    BaseReadable::controller_digital_readable* score_button = nullptr;

    //Actions
//    BaseAction::set_value_action<int16_t>* intake_action = nullptr;
    BaseAction::set_value_action<int16_t>* intake_hold_action = nullptr;
    BaseAction::set_value_action<int16_t>* outtake_action = nullptr;
    BaseAction::intake_control_action* intake_outtake_action = nullptr;

    BaseAction::set_value_action<int16_t>* elevator_down_action = nullptr;
    BaseAction::set_value_action<int16_t>* arm_left_down_action = nullptr;
    BaseAction::set_value_action<int16_t>* arm_right_down_action = nullptr;

    BaseAction::set_value_action<int16_t>* arm_left_stop_action = nullptr;
    BaseAction::set_value_action<int16_t>* arm_right_stop_action = nullptr;

    BaseAction::pid_action<double, int16_t>* arm_pid_action = nullptr;
    BaseAction::pid_action<double, int16_t>* elevator_pid_action = nullptr;

    //Action Maps
    std::vector<action*> ground_all_action_map{};
    std::vector<action*> ground_arm_both_action_map{};
    std::vector<action*> ground_arm_left_elevator_action_map{};
    std::vector<action*> ground_arm_right_elevator_action_map{};
    std::vector<action*> ground_arm_left_action_map{};
    std::vector<action*> ground_arm_right_action_map{};
    std::vector<action*> ground_elevator_action_map{};
    std::vector<action*> ground_action_map{};
//    std::vector<action*> intake_action_map{};
//    std::vector<action*> outtake_action_map{};

    std::vector<action*> flip_action_map{};
    std::vector<action*> angle_action_map{};
    std::vector<action*> low_prime_action_map{};
    std::vector<action*> low_move_action_map{};
    std::vector<action*> low_score_action_map{};
    std::vector<action*> high_prime_action_map{};
    std::vector<action*> high_move_action_map{};
    std::vector<action*> high_score_action_map{};

    //Transition functions
    std::function<bool()> ground_all_to_ground_arm_both{};
    std::function<bool()> ground_all_to_ground_arm_left_elevator{};
//    std::function<bool()> ground_all_to_ground_arm_right_elevator{};
    std::function<bool()> ground_all_to_angle{};
    std::function<bool()> ground_all_to_low_prime{};

//    std::function<bool()> ground_arm_both_to_ground_arm_right{};
    std::function<bool()> ground_arm_both_to_ground_arm_left{};
    std::function<bool()> ground_arm_both_to_angle{};
    std::function<bool()> ground_arm_both_to_low_prime{};

    std::function<bool()> ground_arm_left_elevator_to_ground_arm_left{};
    std::function<bool()> ground_arm_left_elevator_to_ground_elevator{};
    std::function<bool()> ground_arm_left_elevator_to_angle{};
    std::function<bool()> ground_arm_left_elevator_to_low_prime{};

//    std::function<bool()> ground_arm_right_elevator_to_ground_arm_right{};
//    std::function<bool()> ground_arm_right_elevator_to_ground_elevator{};
//    std::function<bool()> ground_arm_right_elevator_to_angle{};
//    std::function<bool()> ground_arm_right_elevator_to_low_prime{};

    std::function<bool()> ground_arm_left_to_ground{};
    std::function<bool()> ground_arm_left_to_angle{};
    std::function<bool()> ground_arm_left_to_low_prime{};

//    std::function<bool()> ground_arm_right_to_ground{};
//    std::function<bool()> ground_arm_right_to_angle{};
//    std::function<bool()> ground_arm_right_to_low_prime{};

    std::function<bool()> ground_elevator_to_ground{};
    std::function<bool()> ground_elevator_to_angle{};
    std::function<bool()> ground_elevator_to_low_prime{};

    std::function<bool()> ground_to_flip{};
    std::function<bool()> ground_to_angle{};
    std::function<bool()> ground_to_low_prime{};
//    std::function<bool()> ground_to_intake{};
//    std::function<bool()> ground_to_outtake{};

//    std::function<bool()> intake_to_flip{};
//    std::function<bool()> intake_to_angle{};
//    std::function<bool()> intake_to_low_prime{};
//    std::function<bool()> intake_to_ground{};
//
//    std::function<bool()> outtake_to_flip{};
//    std::function<bool()> outtake_to_angle{};
//    std::function<bool()> outtake_to_low_prime{};
//    std::function<bool()> outtake_to_ground{};

    std::function<bool()> flip_to_ground_all{};
    std::function<bool()> flip_to_angle{};
    std::function<bool()> flip_to_low_prime{};

    std::function<bool()> angle_to_low_prime{};
    std::function<bool()> angle_to_ground_all{};

    std::function<bool()> low_prime_to_high_prime{};
    std::function<bool()> low_prime_to_angle{};
    std::function<bool()> low_prime_to_ground_all{};
    std::function<bool()> low_prime_to_low_move{};

    std::function<bool()> low_move_to_low_prime{};
    std::function<bool()> low_move_to_low_score{};

    std::function<bool()> low_score_to_ground_all{};

    std::function<bool()> high_prime_to_low_prime{};
    std::function<bool()> high_prime_to_angle{};
    std::function<bool()> high_prime_to_high_move{};

    std::function<bool()> high_move_to_high_prime{};
    std::function<bool()> high_move_to_high_score{};

    std::function<bool()> high_score_to_ground_all{};

    //Transition vectors
    std::vector<transition> ground_all_transitions{};
    std::vector<transition> ground_arm_both_transitions{};
    std::vector<transition> ground_arm_left_elevator_transitions{};
//    std::vector<transition> ground_arm_right_elevator_transitions{};
    std::vector<transition> ground_arm_left_transitions{};
//    std::vector<transition> ground_arm_right_transitions{};
    std::vector<transition> ground_elevator_transitions{};
    std::vector<transition> ground_transitions{};
//    std::vector<transition> intake_transitions{};
//    std::vector<transition> outtake_transitions{};
    std::vector<transition> flip_transitions{};
    std::vector<transition> angle_transitions{};
    std::vector<transition> low_prime_transitions{};
    std::vector<transition> low_move_transitions{};
    std::vector<transition> low_score_transitions{};
    std::vector<transition> high_prime_transitions{};
    std::vector<transition> high_move_transitions{};
    std::vector<transition> high_score_transitions{};

    //On-state entry functions
    std::function<void(state*)> on_ground_all_entry{};
    std::function<void(state*)> on_ground_arm_both_entry{};
    std::function<void(state*)> on_ground_arm_left_elevator_entry{};
//    std::function<void(state*)> on_ground_arm_right_elevator_entry{};
    std::function<void(state*)> on_ground_arm_left_entry{};
//    std::function<void(state*)> on_ground_arm_right_entry{};
    std::function<void(state*)> on_ground_elevator_entry{};
    std::function<void(state*)> on_ground_entry{};
//    std::function<void(state*)> on_intake_entry{};
//    std::function<void(state*)> on_outtake_entry{};
    std::function<void(state*)> on_flip_entry{};
    std::function<void(state*)> on_angle_entry{};
    std::function<void(state*)> on_low_prime_entry{};
    std::function<void(state*)> on_low_move_entry{};
    std::function<void(state*)> on_low_score_entry{};
    std::function<void(state*)> on_high_prime_entry{};
    std::function<void(state*)> on_high_move_entry{};
    std::function<void(state*)> on_high_score_entry{};

    //States
    state* ground_all = nullptr;
    state* ground_arm_both = nullptr;
    state* ground_arm_left_elevator = nullptr;
//    state* ground_arm_right_elevator = nullptr;
    state* ground_arm_left = nullptr;
//    state* ground_arm_right = nullptr;
    state* ground_elevator = nullptr;
    state* ground = nullptr;
//    state* intake = nullptr;
//    state* outtake = nullptr;
    state* flip = nullptr;
    state* angle = nullptr;
    state* low_prime = nullptr;
    state* low_move = nullptr;
    state* low_score = nullptr;
    state* high_prime = nullptr;
    state* high_move = nullptr;
    state* high_score = nullptr;

    //State map
    std::vector<state*> states{};

    //Commandable vector
    std::vector<commandable*> commandables{};

    //State controller
    state_controller* cap_state_machine = nullptr;
    std::vector<readable*> inputs{};

    //State controller vector
    std::vector<state_controller*> state_machines{};

    //Subsystem controller
    subsystem_controller* cap_subsystem = nullptr;

    void init() {
        using namespace BaseCommandable;
        using namespace BaseReadable;
        using namespace BaseAction;

        //Commandables
        elevator_motor = new motor_commandable{
                ELEVATOR_MOTOR_PORT,
                ELEVATOR_MOTOR_GEARSET,
                false,
                pros::E_MOTOR_BRAKE_COAST, "elevator_motor"
        };

        arm_left_motor = new motor_commandable{
                ARM_MOTOR_LEFT_PORT,
                ARM_MOTOR_LEFT_GEARSET,
                true,
                pros::E_MOTOR_BRAKE_COAST,
                "arm_left_motor"
        };

        arm_right_motor = new motor_commandable{
                ARM_MOTOR_RIGHT_PORT,
                ARM_MOTOR_RIGHT_GEARSET,
                false,
                pros::E_MOTOR_BRAKE_COAST,
                "arm_right_motor"
        };

        intake_motor = new motor_commandable{
                INTAKE_MOTOR_PORT,
                INTAKE_MOTOR_GEARSET,
                false,
                pros::E_MOTOR_BRAKE_COAST,
                "intake_motor"
        };

        arm_motors = new multi_motor_commandable{
                "arm_motors"
        };
        arm_motors->add_motor(arm_left_motor);
        arm_motors->add_motor(arm_right_motor);

        //Readables

//        arm_limit_switch_left = new adi_digital_readable{ARM_LIMIT_SWITCH_LEFT_PORT, "arm_limit_switch_left"};
        arm_limit_switch_right = new adi_digital_readable{ARM_LIMIT_SWITCH_RIGHT_PORT, "arm_limit_switch_right"};
        elevator_limit_switch = new adi_digital_readable{ELEVATOR_LIMIT_SWITCH_PORT, "elevator_limit_switch"};
        vee_limit_switch = new adi_digital_readable{VEE_LIMIT_SWITCH_PORT, "vee_limit_switch"};

        arm_encoder = new motor_encoder_readable{ARM_MOTOR_RIGHT_PORT, 1.0, "arm_encoder"};
        elevator_encoder = new motor_encoder_readable{ELEVATOR_MOTOR_PORT, 1.0, "elevator_encoder"};

        intake_button = get_controller_digital_readable(pros::E_CONTROLLER_MASTER, INTAKE_BUTTON);
        outtake_button = get_controller_digital_readable(pros::E_CONTROLLER_MASTER, OUTTAKE_BUTTON);
        flip_button = get_controller_digital_readable(pros::E_CONTROLLER_MASTER, FLIP_BUTTON);
        angle_button = get_controller_digital_readable(pros::E_CONTROLLER_MASTER, ANGLE_BUTTON);
        low_button = get_controller_digital_readable(pros::E_CONTROLLER_MASTER, LOW_BUTTON);
        high_button = get_controller_digital_readable(pros::E_CONTROLLER_MASTER, HIGH_BUTTON);
        score_button = get_controller_digital_readable(pros::E_CONTROLLER_MASTER, SCORE_BUTTON);

        //Action initializations
//        intake_action = new set_value_action<int16_t>{INTAKE_UPDATE_PERIOD, intake_motor, 12000, "intake_action"};
        intake_hold_action = new set_value_action<int16_t>{INTAKE_HOLD_UPDATE_PERIOD, intake_motor, 6000,
                                                           "intake_hold_action"};
        outtake_action = new set_value_action<int16_t>{OUTTAKE_UPDATE_PERIOD, intake_motor, -12000, "outtake_action"};
        intake_outtake_action = new intake_control_action{INTAKE_OUTTAKE_UPDATE_PERIOD, intake_motor, intake_button,
                                                          outtake_button, "intake_outtake_action"};

        elevator_down_action = new set_value_action<int16_t>{ELEVATOR_DOWN_UPDATE_PERIOD, elevator_motor, -12000,
                                                             "elevator_down"};
        arm_left_down_action = new set_value_action<int16_t>{ARM_DOWN_UPDATE_PERIOD, arm_left_motor, -12000,
                                                             "arm_left_down_action"};
        arm_right_down_action = new set_value_action<int16_t>{ARM_DOWN_UPDATE_PERIOD, arm_right_motor, -12000,
                                                              "arm_right_down_action"};

        arm_left_stop_action = new set_value_action<int16_t>{ARM_STOP_UPDATE_PERIOD, arm_left_motor, 0,
                                                             "arm_left_stop_action"};
        arm_right_stop_action = new set_value_action<int16_t>{ARM_STOP_UPDATE_PERIOD, arm_right_motor, 0,
                                                              "arm_right_stop_action"};

        arm_pid_action = new pid_action<double, int16_t>{ARM_PID_UPDATE_PERIOD, arm_motors, 200, 50, 0, -12000, 12000,
                                                         -6000, 6000, 0, arm_encoder, 0, "arm_pid_action"};
        elevator_pid_action = new pid_action<double, int16_t>{ELEVATOR_PID_UPDATE_PERIOD, elevator_motor, 200, 50, 0,
                                                              -12000, 12000, -6000, 6000, 0, elevator_encoder, 0,
                                                              "elevator_pid_action"};

        //Action maps
        //Ground all
        ground_all_action_map.push_back(intake_outtake_action);
        ground_all_action_map.push_back(arm_left_down_action);
        ground_all_action_map.push_back(arm_right_down_action);
        ground_all_action_map.push_back(elevator_down_action);
        //Ground arm both
        ground_arm_both_action_map.push_back(arm_left_down_action);
        ground_arm_both_action_map.push_back(arm_right_down_action);
        ground_arm_both_action_map.push_back(elevator_pid_action);
        ground_arm_both_action_map.push_back(intake_outtake_action);
        //Ground arm left elevator
        ground_arm_left_elevator_action_map.push_back(arm_left_down_action);
        ground_arm_left_elevator_action_map.push_back(arm_right_stop_action);
        ground_arm_left_elevator_action_map.push_back(elevator_down_action);
        ground_arm_left_elevator_action_map.push_back(intake_outtake_action);
        //Ground arm right elevator
        ground_arm_right_elevator_action_map.push_back(arm_left_stop_action);
        ground_arm_right_elevator_action_map.push_back(arm_right_down_action);
        ground_arm_right_elevator_action_map.push_back(elevator_down_action);
        ground_arm_right_elevator_action_map.push_back(intake_outtake_action);
        //Ground arm left
        ground_arm_left_action_map.push_back(arm_left_down_action);
        ground_arm_left_action_map.push_back(arm_right_stop_action);
        ground_arm_left_action_map.push_back(elevator_pid_action);
        ground_arm_left_action_map.push_back(intake_outtake_action);
        //Ground arm right
        ground_arm_right_action_map.push_back(arm_left_stop_action);
        ground_arm_right_action_map.push_back(arm_right_down_action);
        ground_arm_right_action_map.push_back(elevator_pid_action);
        ground_arm_right_action_map.push_back(intake_outtake_action);
        //Ground elevator
        ground_elevator_action_map.push_back(arm_left_stop_action);
        ground_elevator_action_map.push_back(arm_right_stop_action);
        ground_elevator_action_map.push_back(elevator_down_action);
        ground_elevator_action_map.push_back(intake_outtake_action);
        //Ground
        ground_action_map.push_back(arm_pid_action);
        ground_action_map.push_back(elevator_pid_action);
        ground_action_map.push_back(intake_outtake_action);
        //Intake
//        intake_action_map.push_back(intake_action);
        //Outtake
//        outtake_action_map.push_back(outtake_action);
        //Flip
        flip_action_map.push_back(arm_pid_action);
        flip_action_map.push_back(elevator_pid_action);
        flip_action_map.push_back(intake_hold_action);
        //Angle
        angle_action_map.push_back(arm_pid_action);
        angle_action_map.push_back(elevator_pid_action);
        angle_action_map.push_back(intake_outtake_action);
        //Low prime
        low_prime_action_map.push_back(arm_pid_action);
        low_prime_action_map.push_back(elevator_pid_action);
        low_prime_action_map.push_back(intake_hold_action);
        //Low move
        low_move_action_map.push_back(arm_pid_action);
        low_move_action_map.push_back(elevator_pid_action);
        low_move_action_map.push_back(intake_hold_action);
        //Low score
        low_score_action_map.push_back(arm_pid_action);
        low_score_action_map.push_back(elevator_pid_action);
        low_score_action_map.push_back(outtake_action);
        //High prime
        high_prime_action_map.push_back(arm_pid_action);
        high_prime_action_map.push_back(elevator_pid_action);
        high_prime_action_map.push_back(intake_hold_action);
        //High move
        high_move_action_map.push_back(arm_pid_action);
        high_move_action_map.push_back(elevator_pid_action);
        high_move_action_map.push_back(intake_hold_action);
        //High score
        high_score_action_map.push_back(arm_pid_action);
        high_score_action_map.push_back(elevator_pid_action);
        high_score_action_map.push_back(outtake_action);

        //Transition functions
        ground_all_to_ground_arm_both = []() -> bool{ return elevator_limit_switch->is_pressed(); };
        ground_all_to_ground_arm_left_elevator = []() -> bool{ return arm_limit_switch_right->is_pressed(); };
//        ground_all_to_ground_arm_right_elevator = []() -> bool{ return arm_limit_switch_left->is_pressed(); };
        ground_all_to_angle = []() -> bool{ return angle_button->is_rising_edge(); };
        ground_all_to_low_prime = []() -> bool{ return high_button->is_rising_edge(); };

//        ground_arm_both_to_ground_arm_right = []() -> bool{ return arm_limit_switch_left->is_pressed(); };
        ground_arm_both_to_ground_arm_left = []() -> bool{ return arm_limit_switch_right->is_pressed(); };
        ground_arm_both_to_angle = []() -> bool{ return angle_button->is_rising_edge(); };
        ground_arm_both_to_low_prime = []() -> bool{ return high_button->is_rising_edge(); };

        ground_arm_left_elevator_to_ground_arm_left = []() -> bool{ return elevator_limit_switch->is_pressed(); };
        ground_arm_left_elevator_to_ground_elevator = []() -> bool{
//            return arm_limit_switch_left->is_pressed();
            return limit_timer <= pros::millis();
        };
        ground_arm_left_elevator_to_angle = []() -> bool{
            return angle_button->is_rising_edge();
        };
        ground_arm_left_elevator_to_low_prime = []() -> bool{ return high_button->is_rising_edge(); };

//        ground_arm_right_elevator_to_ground_arm_right = []() -> bool{ return elevator_limit_switch->is_pressed(); };
//        ground_arm_right_elevator_to_ground_elevator = []() -> bool{ return arm_limit_switch_right->is_pressed(); };
//        ground_arm_right_elevator_to_angle = []() -> bool{ return angle_button->is_pressed(); };
//        ground_arm_right_elevator_to_low_prime = []() -> bool{ return high_button->is_pressed(); };

        ground_arm_left_to_ground = []() -> bool{
//            return arm_limit_switch_left->is_pressed();
            return limit_timer <= pros::millis();
        };
        ground_arm_left_to_angle = []() -> bool{
            return angle_button->is_rising_edge();
        };
        ground_arm_left_to_low_prime = []() -> bool{ return high_button->is_rising_edge(); };

//        ground_arm_right_to_ground = []() -> bool{ return arm_limit_switch_right->is_rising_edge(); };
//        ground_arm_right_to_angle = []() -> bool{ return angle_button->is_pressed(); };
//        ground_arm_right_to_low_prime = []() -> bool{ return high_button->is_pressed(); };

        ground_elevator_to_ground = []() -> bool { return elevator_limit_switch->is_pressed(); };
        ground_elevator_to_angle = []() -> bool{ return angle_button->is_rising_edge(); };
        ground_elevator_to_low_prime = []() -> bool{ return high_button->is_rising_edge(); };

        ground_to_flip = []() -> bool{ return flip_button->is_rising_edge(); };
        ground_to_angle = []() -> bool{
            return angle_button->is_rising_edge();
        };
        ground_to_low_prime = []() -> bool{ return high_button->is_rising_edge(); };
//        ground_to_intake = []() -> bool { return intake_button->is_pressed(); };
//        ground_to_outtake = []() -> bool { return outtake_button->is_pressed(); };
//
//        intake_to_ground = []() -> bool { return !(intake_button->is_pressed()); };
//
//        outtake_to_ground = []() -> bool { return !(outtake_button->is_pressed()); };

        flip_to_ground_all = []() -> bool{ return !(flip_button->is_rising_edge()); };
        flip_to_angle = []() -> bool{
            return angle_button->is_rising_edge();
        };
        flip_to_low_prime = []() -> bool{ return high_button->is_rising_edge(); };

        angle_to_low_prime = []() -> bool{ return high_button->is_rising_edge(); };
        angle_to_ground_all = []() -> bool{
            return angle_button->is_rising_edge();
        };

        low_prime_to_high_prime = []() -> bool {
            return high_button->is_rising_edge();
        };
        low_prime_to_angle = []() -> bool{
            return angle_button->is_rising_edge();
        };
        low_prime_to_ground_all = []() -> bool{ return low_button->is_rising_edge(); };
        low_prime_to_low_move = []() -> bool{
            return score_button->is_rising_edge() || vee_limit_switch->is_pressed();
        };

        low_move_to_low_prime = []() -> bool { return false; /*check for error*/ };
        low_move_to_low_score = []() -> bool{
            return in_range(ARM_LOW_SCORE_LOWER, arm_encoder->get_position(), ARM_LOW_SCORE_UPPER) &&
                   in_range(ELEVATOR_LOW_SCORE_LOWER, elevator_encoder->get_position(), ELEVATOR_LOW_SCORE_UPPER);
        };

        low_score_to_ground_all = []() -> bool { return score_timer <= pros::millis(); };

        high_prime_to_low_prime = []() -> bool{ return low_button->is_rising_edge(); };
        high_prime_to_angle = []() -> bool{
            return angle_button->is_rising_edge();
        };
        high_prime_to_high_move = []() -> bool{
            return score_button->is_rising_edge() || vee_limit_switch->is_pressed();
        };
        high_move_to_high_prime = []() -> bool { return false; /*check for error*/ };
        high_move_to_high_score = []() -> bool{
            return in_range(ARM_HIGH_SCORE_LOWER, arm_encoder->get_position(), ARM_HIGH_SCORE_UPPER) &&
                   in_range(ELEVATOR_HIGH_SCORE_LOWER, elevator_encoder->get_position(), ELEVATOR_HIGH_SCORE_UPPER);
        };

        high_score_to_ground_all = []() -> bool { return score_timer <= pros::millis(); };

        //Transition vectors
        ground_all_transitions.emplace_back(ground_all_to_ground_arm_both, ground_arm_both,
                                            "ground_all_to_ground_arm_both");
        ground_all_transitions.emplace_back(ground_all_to_ground_arm_left_elevator, ground_arm_left_elevator,
                                            "ground_all_to_ground_arm_left_elevator");
//        ground_all_transitions.emplace_back(ground_all_to_ground_arm_right_elevator, ground_arm_right_elevator, "ground_all_to_ground_arm_right_elevator");
        ground_all_transitions.emplace_back(ground_all_to_angle, low_prime, "ground_all_to_low_prime");
        ground_all_transitions.emplace_back(ground_all_to_low_prime, low_prime, "ground_all_to_low_prime");

        ground_arm_both_transitions.emplace_back(ground_arm_both_to_ground_arm_left, ground_arm_left,
                                                 "ground_arm_both_to_ground_arm_right");
//        ground_arm_both_transitions.emplace_back(ground_arm_both_to_ground_arm_right, ground_arm_right, "ground_arm_both_to_ground_arm_right");
        ground_arm_both_transitions.emplace_back(ground_arm_both_to_angle, angle, "ground_arm_both_to_angle");
        ground_arm_both_transitions.emplace_back(ground_arm_both_to_low_prime, low_prime,
                                                 "ground_arm_both_to_low_prime");

        ground_arm_left_elevator_transitions.emplace_back(ground_arm_left_elevator_to_ground_arm_left, ground_arm_left,
                                                          "ground_arm_left_elevator_to_ground_arm_left");
        ground_arm_left_elevator_transitions.emplace_back(ground_arm_left_elevator_to_ground_elevator, ground_elevator,
                                                          "ground_arm_left_elevator_to_ground_elevator");
        ground_arm_left_elevator_transitions.emplace_back(ground_arm_left_elevator_to_angle, angle,
                                                          "ground_arm_left_elevator_to_angle");
        ground_arm_left_elevator_transitions.emplace_back(ground_arm_left_elevator_to_low_prime, low_prime,
                                                          "ground_arm_left_elevator_to_low_prime");

//        ground_arm_right_elevator_transitions.emplace_back(ground_arm_right_elevator_to_ground_arm_right, ground_arm_right, "ground_arm_right_elevator_to_ground_arm_right");
//        ground_arm_right_elevator_transitions.emplace_back(ground_arm_right_elevator_to_ground_elevator, ground_elevator, "ground_arm_right_elevator_to_ground_elevator");
//        ground_arm_right_elevator_transitions.emplace_back(ground_arm_right_elevator_to_angle, angle, "ground_arm_right_elevator_to_angle");
//        ground_arm_right_elevator_transitions.emplace_back(ground_arm_right_elevator_to_low_prime, low_prime, "ground_arm_right_elevator_to_low_prime");

        ground_arm_left_transitions.emplace_back(ground_arm_left_to_ground, ground, "ground_arm_left_to_ground");
        ground_arm_left_transitions.emplace_back(ground_arm_left_to_angle, angle, "ground_arm_left_to_angle");
        ground_arm_left_transitions.emplace_back(ground_arm_left_to_low_prime, low_prime,
                                                 "ground_arm_left_to_low_prime");

//        ground_arm_right_transitions.emplace_back(ground_arm_right_to_ground, ground, "ground_arm_right_to_ground");
//        ground_arm_right_transitions.emplace_back(ground_arm_right_to_angle, angle, "ground_arm_right_to_angle");
//        ground_arm_right_transitions.emplace_back(ground_arm_right_to_low_prime, low_prime, "ground_arm_right_to_low_prime");

        ground_elevator_transitions.emplace_back(ground_elevator_to_ground, ground, "ground_elevator_to_ground");
        ground_elevator_transitions.emplace_back(ground_elevator_to_angle, angle, "ground_elevator_to_angle");
        ground_elevator_transitions.emplace_back(ground_elevator_to_low_prime, low_prime, "ground_elevator_to_low_prime");

        ground_transitions.emplace_back(ground_to_flip, flip, "ground_to_flip");
        ground_transitions.emplace_back(ground_to_angle, angle, "ground_to_angle");
        ground_transitions.emplace_back(ground_to_low_prime, low_prime, "ground_to_low_prime");

//        intake_transitions.emplace_back(intake_to_ground, intake, "intake_to_ground");
//
//        outtake_transitions.emplace_back(outtake_to_ground, outtake, "outtake_to_ground");

        flip_transitions.emplace_back(flip_to_ground_all, ground_all, "flip_to_ground_all");
        flip_transitions.emplace_back(flip_to_angle, angle, "flip_to_angle");
        flip_transitions.emplace_back(flip_to_low_prime, low_prime, "flip_to_low_prime");

        angle_transitions.emplace_back(angle_to_low_prime, low_prime, "angle_to_low_prime");
        angle_transitions.emplace_back(angle_to_ground_all, ground_all, "angle_to_ground_all");

        low_prime_transitions.emplace_back(low_prime_to_high_prime, high_prime, "low_prime_to_high_prime");
        low_prime_transitions.emplace_back(low_prime_to_angle, angle, "low_prime_to_angle");
        low_prime_transitions.emplace_back(low_prime_to_ground_all, ground_all, "low_prime_to_ground_all");
        low_prime_transitions.emplace_back(low_prime_to_low_move, low_move, "low_prime_to_low_move");

        low_move_transitions.emplace_back(low_move_to_low_prime, low_prime, "low_move_to_low_prime");
        low_move_transitions.emplace_back(low_move_to_low_score, low_score, "low_move_to_low_score");

        low_score_transitions.emplace_back(low_score_to_ground_all, ground_all, "low_score_to_ground_all");

        high_prime_transitions.emplace_back(high_prime_to_low_prime, low_prime, "high_prime_to_low_prime");
        high_prime_transitions.emplace_back(high_prime_to_angle, angle, "high_prime_to_angle");
        high_prime_transitions.emplace_back(high_prime_to_high_move, high_move, "high_prime_to_high_move");

        high_move_transitions.emplace_back(high_move_to_high_prime, high_prime, "high_move_to_high_prime");
        high_move_transitions.emplace_back(high_move_to_high_score, high_score, "high_move_to_high_score");

        high_score_transitions.emplace_back(high_score_to_ground_all, ground_all, "high_score_to_ground_all");

        //On-state entry functions
        on_ground_all_entry = [](state* last_state) -> void{};

        on_ground_arm_both_entry = [](state* last_state) -> void{
            elevator_encoder->tare_position();
            elevator_pid_action->set_target(0);
        };

        on_ground_arm_left_elevator_entry = [](state* last_state) -> void{
            limit_timer = pros::millis() + LEFT_DOWN_TIME;
        };

//        on_ground_arm_right_elevator_entry = [](state* last_state) -> void{};

        on_ground_arm_left_entry = [](state* last_state) -> void{
            limit_timer = pros::millis() + LEFT_DOWN_TIME;
            elevator_encoder->tare_position();
            elevator_pid_action->set_target(0);
        };

//        on_ground_arm_right_entry = [](state* last_state) -> void{
//            elevator_encoder->tare_position();
//            elevator_pid_action->set_target(0);
//        };

        on_ground_elevator_entry = [](state* last_state) -> void{
            arm_encoder->tare_position();
            arm_pid_action->set_target(0);
        };

        on_ground_entry = [](state* last_state) -> void{
            if(last_state == ground_elevator){
                elevator_encoder->tare_position();
                elevator_pid_action->set_target(0);
            }
            else{
                arm_encoder->tare_position();
                arm_pid_action->set_target(0);
            }
        };

//        on_intake_entry = [](state* last_state) -> void{};
//
//        on_outtake_entry = [](state* last_state) -> void{};

        on_flip_entry = [](state* last_state) -> void{
            arm_pid_action->set_target(ARM_FLIP_TARGET);
            elevator_pid_action->set_target(0);
        };

        on_angle_entry = [](state* last_state) -> void{
            arm_pid_action->set_target(ARM_ANGLE_TARGET);
            elevator_pid_action->set_target(ELEVATOR_ANGLE_TARGET);
        };

        on_low_prime_entry = [](state* last_state) -> void{
            elevator_pid_action->set_target(ELEVATOR_LOW_PRIME_TARGET);
            arm_pid_action->set_target(ARM_LOW_PRIME_TARGET);
        };

        on_low_move_entry = [](state* last_state) -> void{
            elevator_pid_action->set_target(ELEVATOR_LOW_MOVE_TARGET);
            arm_pid_action->set_target(ARM_LOW_MOVE_TARGET);
        };

        on_low_score_entry = [](state* last_state) -> void{
            score_timer = pros::millis() + SCORE_TIME;
            elevator_pid_action->set_target(ELEVATOR_LOW_SCORE_TARGET);
            arm_pid_action->set_target(ARM_LOW_SCORE_TARGET);
        };

        on_high_prime_entry = [](state* last_state) -> void{
            elevator_pid_action->set_target(ELEVATOR_HIGH_PRIME_TARGET);
            arm_pid_action->set_target(ARM_HIGH_PRIME_TARGET);
        };

        on_high_move_entry = [](state* last_state) -> void{
            elevator_pid_action->set_target(ELEVATOR_HIGH_MOVE_TARGET);
            arm_pid_action->set_target(ARM_HIGH_MOVE_TARGET);
        };

        on_high_score_entry = [](state* last_state) -> void{
            score_timer = pros::millis() + SCORE_TIME;
            elevator_pid_action->set_target(ELEVATOR_HIGH_SCORE_TARGET);
            arm_pid_action->set_target(ARM_HIGH_SCORE_TARGET);
        };

        //States
        ground_all = new state{ground_all_action_map, ground_all_transitions, on_ground_all_entry, "ground_all"};
        ground_arm_both = new state{ground_arm_both_action_map, ground_arm_both_transitions, on_ground_arm_both_entry,
                                    "ground_arm_both"};
        ground_arm_left_elevator = new state{ground_arm_left_elevator_action_map, ground_arm_left_elevator_transitions,
                                             on_ground_arm_left_elevator_entry, "ground_arm_left_elevator"};
        ground_arm_left = new state{ground_arm_left_action_map, ground_arm_left_transitions, on_ground_arm_left_entry,
                                    "ground_arm_left"};
        ground_elevator = new state{ground_elevator_action_map, ground_elevator_transitions, on_ground_elevator_entry,
                                    "ground_elevator"};
        ground = new state{ground_action_map, ground_transitions, on_ground_entry, "ground"};
//        intake = new state{intake_action_map, intake_transitions, on_intake_entry, "intake"};
//        outtake = new state{outtake_action_map, outtake_transitions, on_outtake_entry, "outtake"};
        flip = new state{flip_action_map, flip_transitions, on_flip_entry, "flip"};
        angle = new state{angle_action_map, angle_transitions, on_angle_entry, "angle"};
        low_prime = new state{low_prime_action_map, low_prime_transitions, on_low_prime_entry, "low_prime"};
        low_move = new state{low_move_action_map, low_move_transitions, on_low_move_entry, "low_move"};
        low_score = new state{low_score_action_map, low_score_transitions, on_low_score_entry, "low_score"};
        high_prime = new state{high_prime_action_map, high_prime_transitions, on_high_prime_entry, "high_prime"};
        high_move = new state{high_move_action_map, high_move_transitions, on_high_move_entry, "high_move"};
        high_score = new state{high_score_action_map, high_score_transitions, on_high_score_entry, "high_score"};

        //State map
        states.push_back(ground_all);
        states.push_back(ground_arm_both);
        states.push_back(ground_arm_left_elevator);
        states.push_back(ground_arm_left);
        states.push_back(ground_elevator);
//        states.push_back(ground_arm);
        states.push_back(ground);
//        states.push_back(intake);
//        states.push_back(outtake);
        states.push_back(flip);
        states.push_back(angle);
        states.push_back(low_prime);
        states.push_back(low_move);
        states.push_back(low_score);
        states.push_back(high_prime);
        states.push_back(high_move);
        states.push_back(high_score);

        //Commandable map
        commandables.push_back(intake_motor);
        commandables.push_back(arm_left_motor);
        commandables.push_back(arm_right_motor);
        commandables.push_back(elevator_motor);
        commandables.push_back(arm_motors);

        cap_state_machine = new state_controller{CAP_SYSTEM_UPDATE_PERIOD, states, commandables, ground_all,
                                                 "ground_all"};

        //Ordered inputs
        /*arm_limit_switch_order = new ordered_input{ARM_LIMIT_SWITCH_ORDER, arm_limit_switch};
         elevator_limit_switch_order = new ordered_input{ELEVATOR_LIMIT_SWITCH_ORDER, elevator_limit_switch};
         arm_encoder_order = new ordered_input{ARM_ENCODER_ORDER, arm_encoder};
         elevator_encoder_order = new ordered_input{ELEVATOR_ENCODER_ORDER, elevator_encoder};*/

        inputs.push_back(arm_limit_switch_right);
        inputs.push_back(elevator_limit_switch);
        inputs.push_back(arm_encoder);
        inputs.push_back(elevator_encoder);

        state_machines.push_back(cap_state_machine);

        cap_subsystem = new subsystem_controller{inputs, state_machines, "cap"};
    }

    void destroy() {
        delete (elevator_motor);
        delete (arm_left_motor);
        delete (arm_right_motor);
        delete (intake_motor);
        delete (arm_motors);

        delete (arm_limit_switch_right);
        delete (elevator_limit_switch);
        delete (arm_encoder);
        delete (elevator_encoder);

//        delete (intake_action);
        delete (intake_hold_action);
        delete (outtake_action);
//      delete (intake_outtake_action);
        delete (elevator_down_action);
        delete (arm_left_down_action);
        delete (arm_right_down_action);
        delete (arm_left_stop_action);
        delete (arm_right_stop_action);
        delete (arm_pid_action);
        delete (elevator_pid_action);

        delete (ground_all);
        delete (ground_elevator);
//      delete (ground_arm);
        delete (ground);
//        delete (intake);
//        delete (outtake);
        delete (flip);
        delete (angle);
        delete (low_prime);
        delete (low_move);
        delete (low_score);
        delete (high_prime);
        delete (high_move);
        delete (high_score);

        delete (cap_state_machine);

        /*delete (arm_limit_switch_order);
          delete (elevator_limit_switch_order);
          delete (arm_encoder_order);*/

        delete (cap_subsystem);

    }
}