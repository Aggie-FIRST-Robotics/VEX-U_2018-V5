#include <robot/cap/intake_action.h>
#include "afr-vexu-lib/base-readable/controller_readable.h"
#include "robot/cap/cap.h"
#include "robot/robot.h"

namespace AFR::VexU::Robot::Cap {
    std::chrono::steady_clock::time_point next_cock = std::chrono::steady_clock::now();

    //Commandables
    BaseCommandable::motor_commandable *elevator_motor = nullptr;
    BaseCommandable::motor_commandable *arm_a_motor = nullptr;
    BaseCommandable::motor_commandable *arm_b_motor = nullptr;
    BaseCommandable::motor_commandable *intake_motor = nullptr;

    //Readables
    BaseReadable::adi_digital_readable *arm_limit_switch_top = nullptr;
    BaseReadable::adi_digital_readable *arm_limit_switch_bottom = nullptr;
    BaseReadable::motor_encoder_readable *arm_encoder = nullptr;
    BaseReadable::motor_encoder_readable *elevator_encoder = nullptr;

    //Actions
    intake_action *intake_action_ = nullptr;
    intake_action *intake_hold_action = nullptr;
    intake_action *outtake_action = nullptr;
    intake_action *intake_outtake_action = nullptr;
    BaseAction::set_value_action<int16_t> *elevator_down_action = nullptr;
    BaseAction::set_value_action<int16_t> *elevator_zero_action = nullptr;
    BaseAction::set_value_action<int16_t> *elevator_high_pos_action = nullptr;
    BaseAction::set_value_action<int16_t> *arm_a_down_action = nullptr;
    BaseAction::set_value_action<int16_t> *arm_b_down_action = nullptr;
    BaseAction::set_value_action<int16_t> *arm_a_zero_action = nullptr;
    BaseAction::set_value_action<int16_t> *arm_b_zero_action = nullptr;
    BaseAction::set_value_action<int16_t> *arm_a_flip_pos_action = nullptr;
    BaseAction::set_value_action<int16_t> *arm_b_flip_pos_action = nullptr;
    BaseAction::set_value_action<int16_t> *arm_a_angle_pos_action = nullptr;
    BaseAction::set_value_action<int16_t> *arm_b_angle_pos_action = nullptr;
    BaseAction::set_value_action<int16_t> *arm_a_low_prime_pos_action = nullptr;
    BaseAction::set_value_action<int16_t> *arm_b_low_prime_pos_action = nullptr;
    BaseAction::set_value_action<int16_t> *arm_a_low_score_pos_action = nullptr;
    BaseAction::set_value_action<int16_t> *arm_b_low_score_pos_action = nullptr;
    BaseAction::set_value_action<int16_t> *arm_a_high_prime_pos_action = nullptr;
    BaseAction::set_value_action<int16_t> *arm_b_high_prime_pos_action = nullptr;
    BaseAction::set_value_action<int16_t> *arm_a_high_score_pos_action = nullptr;
    BaseAction::set_value_action<int16_t> *arm_b_high_score_pos_action = nullptr;

    //Action Maps
    std::vector<action *> ground_all_action_map{};
    std::vector<action *> ground_arm_action_map{};
    std::vector<action *> ground_elevator_action_map{};
    std::vector<action *> ground_action_map{};
    std::vector<action *> flip_action_map{};
    std::vector<action *> angle_action_map{};
    std::vector<action *> low_prime_action_map{};
    std::vector<action *> low_move_action_map{};
    std::vector<action *> low_score_action_map{};
    std::vector<action *> high_prime_action_map{};
    std::vector<action *> high_move_action_map{};
    std::vector<action *> high_score_action_map{};

    //Transition functions
    std::function<error_t(bool &)> ground_all_to_ground_elevator{};
    std::function<error_t(bool &)> ground_all_to_ground_arm{};
    std::function<error_t(bool &)> ground_all_to_angle{};
    std::function<error_t(bool &)> ground_all_to_low_prime{};
    std::function<error_t(bool &)> ground_elevator_to_ground{};
    std::function<error_t(bool &)> ground_elevator_to_angle{};
    std::function<error_t(bool &)> ground_elevator_to_low_prime{};
    std::function<error_t(bool &)> ground_arm_to_ground{};
    std::function<error_t(bool &)> ground_arm_to_angle{};
    std::function<error_t(bool &)> ground_arm_to_low_prime{};
    std::function<error_t(bool &)> ground_to_flip{};
    std::function<error_t(bool &)> ground_to_angle{};
    std::function<error_t(bool &)> flip_to_ground_all{};
    std::function<error_t(bool &)> flip_to_angle{};
    std::function<error_t(bool &)> flip_to_low_prime{};
    std::function<error_t(bool &)> angle_to_low_prime{};
    std::function<error_t(bool &)> low_prime_to_high_prime{};
    std::function<error_t(bool &)> low_prime_to_angle{};
    std::function<error_t(bool &)> low_prime_to_ground_all{};
    std::function<error_t(bool &)> low_prime_to_low_move{};
    std::function<error_t(bool &)> low_move_to_low_prime{};
    std::function<error_t(bool &)> low_move_to_low_score{};
    std::function<error_t(bool &)> low_score_to_ground_all{};
    std::function<error_t(bool &)> high_prime_to_low_prime{};
    std::function<error_t(bool &)> high_prime_to_angle{};
    std::function<error_t(bool &)> high_prime_to_high_move{};
    std::function<error_t(bool &)> high_move_to_high_prime{};
    std::function<error_t(bool &)> high_move_to_high_score{};
    std::function<error_t(bool &)> high_score_to_ground_all{};

    //Transition vectors
    std::vector<transition> ground_all_transitions{};
    std::vector<transition> ground_elevator_transitions{};
    std::vector<transition> ground_arm_transitions{};
    std::vector<transition> ground_transitions{};
    std::vector<transition> flip_transitions{};
    std::vector<transition> angle_transitions{};
    std::vector<transition> low_prime_transitions{};
    std::vector<transition> low_move_transitions{};
    std::vector<transition> low_score_transitions{};
    std::vector<transition> high_prime_transitions{};
    std::vector<transition> high_move_transitions{};
    std::vector<transition> high_score_transitions{};

    //On-state entry functions
    std::function<void(state *)> on_ground_all_entry{};
    std::function<void(state *)> on_ground_elevator_entry{};
    std::function<void(state *)> on_ground_arm_entry{};
    std::function<void(state *)> on_ground_entry{};
    std::function<void(state *)> on_flip_entry{};
    std::function<void(state *)> on_angle_entry{};
    std::function<void(state *)> on_low_prime_entry{};
    std::function<void(state *)> on_low_move_entry{};
    std::function<void(state *)> on_low_score_entry{};
    std::function<void(state *)> on_high_prime_entry{};
    std::function<void(state *)> on_high_move_entry{};
    std::function<void(state *)> on_high_score_entry{};

    //States
    state *ground_all = nullptr;
    state *ground_elevator = nullptr;
    state *ground_arm = nullptr;
    state *ground = nullptr;
    state *flip = nullptr;
    state *angle = nullptr;
    state *low_prime = nullptr;
    state *low_move = nullptr;
    state *low_score = nullptr;
    state *high_prime = nullptr;
    state *high_move = nullptr;
    state *high_score = nullptr;

    //State map
    std::vector<state *> states{};

    //Commandable map
    //  std::unordered_map<std::string, commandable &> commandable_map{};

    //State controller
    state_controller *cap_state_machine = nullptr;
    std::vector<readable *> inputs{};
    /*//Ordered inputs
    ordered_input *arm_limit_switch_top_order = nullptr;
    ordered_input *arm_limit_switch_bottom_order = nullptr;
    ordered_input *arm_encoder_order = nullptr;
    ordered_input *elevator_encoder_order = nullptr;

    //Ordered input map
    std::unordered_map<std::string, ordered_input &> inputs{};*/

    //State controller map
    std::vector<state_controller *> state_machines{};

    //Subsystem controller
    subsystem_controller *cap_subsystem = nullptr;

    void init() {
        using namespace BaseCommandable;
        using namespace BaseReadable;
        using namespace BaseAction;

        //Commandables
        elevator_motor = new motor_commandable{
                ELEVATOR_MOTOR_PORT,
                pros::E_MOTOR_GEARSET_INVALID,
                false,
                pros::E_MOTOR_BRAKE_INVALID, "elevator_motor"
        };

        arm_a_motor = new motor_commandable{
                ARM_MOTOR_LEFT_PORT,
                pros::E_MOTOR_GEARSET_INVALID,
                false,
                pros::E_MOTOR_BRAKE_INVALID, "arm_a_motor"
        };

        arm_b_motor = new motor_commandable{
                ARM_MOTOR_RIGHT_PORT,
                pros::E_MOTOR_GEARSET_INVALID,
                false,
                pros::E_MOTOR_BRAKE_INVALID, "arm_b_motor"
        };

        intake_motor = new motor_commandable{
                INTAKE_MOTOR_PORT,
                pros::E_MOTOR_GEARSET_INVALID,
                false,
                pros::E_MOTOR_BRAKE_INVALID, "intake_motor"
        };

        //Readables


        arm_limit_switch_bottom = new adi_digital_readable{

                ARM_LIMIT_SWITCH_BOTTOM_PORT, "arm_limit_switch_bottom"
        };

        arm_encoder = new motor_encoder_readable{
                ARM_MOTOR_LEFT_PORT,
                1.0,
                "arm_encoder"
        };

        elevator_encoder = new motor_encoder_readable{
                ELEVATOR_MOTOR_PORT,

                1.0,
                "elevator_encoder"
        };

        //Action initializations
        BaseReadable::controller_digital_readable *left = nullptr;
        BaseReadable::controller_digital_readable *right = nullptr;
        intake_action_ = new intake_action{INTAKE_UPDATE_PERIOD, intake_motor, left, right, "intake_action"};
        intake_hold_action = new intake_action{INTAKE_HOLD_UPDATE_PERIOD, intake_motor, left, right,
                                               "intake_hold_action"};
        outtake_action = new intake_action{OUTTAKE_UPDATE_PERIOD, intake_motor, left, right, "outtake_action"};
        intake_outtake_action = new intake_action{INTAKE_OUTTAKE_UPDATE_PERIOD, intake_motor, left, right,
                                                  "intake_outtake_action"};
        //tare_elevator_encoder_action = new set_value_action<int16_t>{TARE_ELEVATOR_ENCODER_UPDATE_PERIOD, *elevator_encoder, 0};
        //tare_arm_encoder_action = new set_value_action<int16_t>{TARE_ARM_ENCODER_UPDATE_PERIOD, *arm_a_motor, 0};
        elevator_down_action = new set_value_action<int16_t>{ELEVATOR_DOWN_UPDATE_PERIOD, elevator_motor, -100,
                                                             "elevator_down"};
        elevator_zero_action = new set_value_action<int16_t>{ELEVATOR_ZERO_UPDATE_PERIOD, elevator_motor, 0,
                                                             "elevator_zero"};
        //elevator_high_pos_action = new /*pid action*/<int16_t>{ELEVATOR_HIGH_POS_UPDATE_PERIOD, *elevator_motor, 0};
        arm_a_down_action = new set_value_action<int16_t>{ARM_DOWN_UPDATE_PERIOD, arm_a_motor, -100,
                                                          "arm_a_down_action"};
        arm_b_down_action = new set_value_action<int16_t>{ARM_DOWN_UPDATE_PERIOD, arm_b_motor, -100,
                                                          "arm_b_down_action"};
        arm_a_zero_action = new set_value_action<int16_t>{ARM_ZERO_UPDATE_PERIOD, arm_a_motor, 0, "arm_a_zero_action"};
        arm_b_zero_action = new set_value_action<int16_t>{ARM_ZERO_UPDATE_PERIOD, arm_b_motor, 0, "arm_b_action"};
        //   arm_a_flip_pos_action = new /*pid action*/<int16_t>{ARM_FLIP_POS_UPDATE_PERIOD, *arm_a_motor, 0};
        // arm_b_flip_pos_action = new /*pid action*/<int16_t>{ARM_FLIP_POS_UPDATE_PERIOD, *arm_b_motor, 0};
        //arm_a_angle_pos_action = new /*pid action*/<int16_t>{ARM_ANGLE_POS_UPDATE_PERIOD, *arm_a_motor, 0};
        //arm_b_angle_pos_action = new /*pid action*/<int16_t>{ARM_ANGLE_POS_UPDATE_PERIOD, *arm_b_motor, 0};
        //arm_a_low_prime_pos_action = new /*pid action*/<int16_t>{ARM_LOW_PRIME_POS_UPDATE_PERIOD, *arm_a_motor, 0};
        //arm_b_low_prime_pos_action = new /*pid action*/<int16_t>{ARM_LOW_PRIME_POS_UPDATE_PERIOD, *arm_b_motor, 0};
        //arm_a_low_score_pos_action = new /*pid action*/<int16_t>{ARM_LOW_SCORE_POS_UPDATE_PERIOD, *arm_a_motor, 0};
        //arm_b_low_score_pos_action = new /*pid action*/<int16_t>{ARM_LOW_SCORE_POS_UPDATE_PERIOD, *arm_b_motor, 0};
        //arm_a_high_prime_pos_action = new /*pid action*/<int16_t>{ARM_HIGH_PRIME_POS_UPDATE_PERIOD, *arm_a_motor, 0};
        //arm_b_high_prime_pos_action = new /*pid action*/<int16_t>{ARM_HIGH_PRIME_POS_UPDATE_PERIOD, *arm_b_motor, 0};
        //arm_a_high_score_pos_action = new /*pid action*/<int16_t>{ARM_HIGH_SCORE_POS_UPDATE_PERIOD, *arm_a_motor, 0};
        //arm_b_high_score_pos_action = new /*pid action*/<int16_t>{ARM_HIGH_SCORE_POS_UPDATE_PERIOD, *arm_b_motor, 0};

        //Action maps
        //Ground all
        ground_all_action_map.push_back(intake_action_);
        ground_all_action_map.push_back(arm_a_down_action);
        ground_all_action_map.push_back(arm_b_down_action);
        //Ground arm
        //ground_arm_action_map.emplace("ground_arm_tare_elevator_encoder_action", *tare_elevator_encoder_action);
        ground_arm_action_map.push_back(arm_a_down_action);
        ground_arm_action_map.push_back(arm_b_down_action);
        ground_arm_action_map.push_back(elevator_zero_action);
        ground_arm_action_map.push_back(intake_action_);
        //Ground elevator
        //ground_elevator_action_map.emplace("tare_arm_a_encoder_action", *tare_arm_a_encoder_action);
        //ground_elevator_action_map.emplace("tare_arm_b_encoder_action", *tare_arm_b_encoder_action);
        ground_elevator_action_map.push_back(elevator_down_action);
        ground_elevator_action_map.push_back(arm_a_zero_action);
        ground_elevator_action_map.push_back(arm_b_zero_action);
        ground_elevator_action_map.push_back(intake_action_);
        //Ground
        ground_action_map.push_back(elevator_zero_action);
        ground_action_map.push_back(arm_a_zero_action);
        ground_action_map.push_back(arm_b_zero_action);
        //intake/outtake action?????
        //Flip
        flip_action_map.push_back(arm_a_flip_pos_action);
        flip_action_map.push_back(arm_b_flip_pos_action);
        flip_action_map.push_back(elevator_zero_action);
        flip_action_map.push_back(intake_hold_action);
        //Angle
        angle_action_map.push_back(arm_a_angle_pos_action);
        angle_action_map.push_back(arm_b_angle_pos_action);
        angle_action_map.push_back(elevator_zero_action);
        angle_action_map.push_back(intake_action_);
        //Low prime
        low_prime_action_map.push_back(arm_a_low_prime_pos_action);
        low_prime_action_map.push_back(arm_b_low_prime_pos_action);
        low_prime_action_map.push_back(elevator_zero_action);
        low_prime_action_map.push_back(intake_hold_action);
        //Low move
        low_move_action_map.push_back(arm_a_low_score_pos_action);
        low_move_action_map.push_back(arm_b_low_score_pos_action);
        low_move_action_map.push_back(elevator_zero_action);
        low_move_action_map.push_back(intake_hold_action);
        //Low score
        low_score_action_map.push_back(arm_a_low_score_pos_action);
        low_score_action_map.push_back(arm_b_low_score_pos_action);
        low_score_action_map.push_back(elevator_zero_action);
        low_score_action_map.push_back(outtake_action);
        //High prime
        high_prime_action_map.push_back(arm_a_high_prime_pos_action);
        high_prime_action_map.push_back(arm_b_high_prime_pos_action);
        high_prime_action_map.push_back(elevator_high_pos_action);
        high_prime_action_map.push_back(intake_hold_action);
        //High move
        high_move_action_map.push_back(arm_a_high_score_pos_action);
        high_move_action_map.push_back(arm_b_high_score_pos_action);
        high_move_action_map.push_back(elevator_high_pos_action);
        high_move_action_map.push_back(intake_hold_action);
        //High score
        high_score_action_map.push_back(arm_a_high_score_pos_action);
        high_score_action_map.push_back(arm_b_high_score_pos_action);
        high_score_action_map.push_back(elevator_high_pos_action);
        high_score_action_map.push_back(outtake_action);

        //Transition functions
        ground_all_to_ground_elevator = [](bool &result) -> error_t { return SUCCESS; };
        ground_all_to_ground_arm = [](bool &result) -> error_t { return SUCCESS; };
        ground_all_to_angle = [](bool &result) -> error_t { return SUCCESS; };
        ground_all_to_low_prime = [](bool &result) -> error_t { return SUCCESS; };
        ground_elevator_to_ground = [](bool &result) -> error_t { return SUCCESS; };
        ground_elevator_to_angle = [](bool &result) -> error_t { return SUCCESS; };
        ground_elevator_to_low_prime = [](bool &result) -> error_t { return SUCCESS; };
        ground_arm_to_ground = [](bool &result) -> error_t { return SUCCESS; };
        ground_arm_to_angle = [](bool &result) -> error_t { return SUCCESS; };
        ground_arm_to_low_prime = [](bool &result) -> error_t { return SUCCESS; };
        ground_to_flip = [](bool &result) -> error_t { return SUCCESS; };
        ground_to_angle = [](bool &result) -> error_t { return SUCCESS; };
        flip_to_ground_all = [](bool &result) -> error_t { return SUCCESS; };
        flip_to_angle = [](bool &result) -> error_t { return SUCCESS; };
        flip_to_low_prime = [](bool &result) -> error_t { return SUCCESS; };
        angle_to_low_prime = [](bool &result) -> error_t { return SUCCESS; };
        low_prime_to_high_prime = [](bool &result) -> error_t { return SUCCESS; };
        low_prime_to_angle = [](bool &result) -> error_t { return SUCCESS; };
        low_prime_to_ground_all = [](bool &result) -> error_t { return SUCCESS; };
        low_prime_to_low_move = [](bool &result) -> error_t { return SUCCESS; };
        low_move_to_low_prime = [](bool &result) -> error_t { return SUCCESS; };
        low_move_to_low_score = [](bool &result) -> error_t { return SUCCESS; };
        low_score_to_ground_all = [](bool &result) -> error_t { return SUCCESS; };
        high_prime_to_low_prime = [](bool &result) -> error_t { return SUCCESS; };
        high_prime_to_angle = [](bool &result) -> error_t { return SUCCESS; };
        high_prime_to_high_move = [](bool &result) -> error_t { return SUCCESS; };
        high_move_to_high_prime = [](bool &result) -> error_t { return SUCCESS; };
        high_move_to_high_score = [](bool &result) -> error_t { return SUCCESS; };
        high_score_to_ground_all = [](bool &result) -> error_t { return SUCCESS; };

        //Transition vectors
        ground_all_transitions.emplace_back(ground_all_to_ground_elevator, "ground_elevator");
        ground_all_transitions.emplace_back(ground_all_to_ground_arm, "ground_arm");
        ground_all_transitions.emplace_back(ground_all_to_angle, "angle");
        ground_all_transitions.emplace_back(ground_all_to_low_prime, "low_prime");
        ground_elevator_transitions.emplace_back(ground_elevator_to_ground, "ground");
        ground_elevator_transitions.emplace_back(ground_elevator_to_angle, "angle");
        ground_elevator_transitions.emplace_back(ground_elevator_to_low_prime, "low_prime");
        ground_arm_transitions.emplace_back(ground_arm_to_ground, "ground");
        ground_arm_transitions.emplace_back(ground_arm_to_angle, "angle");
        ground_arm_transitions.emplace_back(ground_arm_to_low_prime, "low_prime");
        ground_transitions.emplace_back(ground_to_flip, "flip");
        ground_transitions.emplace_back(ground_to_angle, "angle");
        flip_transitions.emplace_back(flip_to_ground_all, "ground_all");
        flip_transitions.emplace_back(flip_to_angle, "angle");
        flip_transitions.emplace_back(flip_to_low_prime, "low_prime");
        angle_transitions.emplace_back(angle_to_low_prime, "low_prime");
        low_prime_transitions.emplace_back(low_prime_to_high_prime, "high_prime");
        low_prime_transitions.emplace_back(low_prime_to_angle, "angle");
        low_prime_transitions.emplace_back(low_prime_to_ground_all, "ground_all");
        low_prime_transitions.emplace_back(low_prime_to_low_move, "low_move");
        low_move_transitions.emplace_back(low_move_to_low_prime, "low_prime");
        low_move_transitions.emplace_back(low_move_to_low_score, "low_score");
        low_score_transitions.emplace_back(low_score_to_ground_all, "ground_all");
        high_prime_transitions.emplace_back(high_prime_to_low_prime, "low_prime");
        high_prime_transitions.emplace_back(high_prime_to_angle, "angle");
        high_prime_transitions.emplace_back(high_prime_to_high_move, "high_move");
        high_move_transitions.emplace_back(high_move_to_high_prime, "high_prime");
        high_move_transitions.emplace_back(high_move_to_high_score, "high_score");
        high_score_transitions.emplace_back(high_score_to_ground_all, "ground_all");

        //On-state entry functions
        on_ground_all_entry = [](state *last_state) -> void {};

        on_ground_elevator_entry = [](state *last_state) -> void {};

        on_ground_arm_entry = [](state *last_state) -> void {};

        on_ground_entry = [](state *last_state) -> void {};

        on_flip_entry = [](state *last_state) -> void {};

        on_angle_entry = [](state *last_state) -> void {};
        on_low_prime_entry = [](state *last_state) -> void {};

        on_low_move_entry = [](state *last_state) -> void {};

        on_low_score_entry = [](state *last_state) -> void {};

        on_high_prime_entry = [](state *last_state) -> void {};

        on_high_move_entry = [](state *last_state) -> void {};

        on_high_score_entry = [](state *last_state) -> void {};

        //States
        ground_all = new state{ground_all_action_map, ground_all_transitions, on_ground_all_entry, "ground_all"};
        ground_elevator = new state{ground_elevator_action_map, ground_elevator_transitions, on_ground_elevator_entry,
                                    "ground_elevator"};
        ground_arm = new state{ground_arm_action_map, ground_arm_transitions, on_ground_arm_entry, "ground_arm"};
        ground = new state{ground_action_map, ground_transitions, on_ground_entry, "ground"};
        flip = new state{flip_action_map, flip_transitions, on_flip_entry, "flip"};

        angle = new state{angle_action_map, angle_transitions, on_angle_entry, "angle"};
        low_prime = new state{low_prime_action_map, low_prime_transitions, on_low_prime_entry, "low_prime"};
        low_move = new state{low_move_action_map, low_move_transitions, on_low_move_entry, "low_move"};
        low_score = new state{low_score_action_map, low_score_transitions, on_low_score_entry, "low_score"};
        high_prime = new state{high_prime_action_map, high_prime_transitions, on_high_prime_entry, "high_score"};
        high_move = new state{high_move_action_map, high_move_transitions, on_high_move_entry, "high_move"};
        high_score = new state{high_score_action_map, high_score_transitions, on_high_score_entry, "high_score"};

        //State map
        states.push_back(ground_all);
        states.push_back(ground_elevator);
        states.push_back(ground_arm);
        states.push_back(ground);
        states.push_back(flip);
        states.push_back(angle);
        states.push_back(low_prime);
        states.push_back(low_move);
        states.push_back(low_score);
        states.push_back(high_prime);
        states.push_back(high_move);
        states.push_back(high_score);
        std::vector<commandable *> commandables{};
        //Commandable map
        commandables.push_back(intake_motor);
        commandables.push_back(arm_a_motor);
        commandables.push_back(arm_b_motor);
        commandables.push_back(elevator_motor);

        cap_state_machine = new state_controller{CAP_SYSTEM_UPDATE_PERIOD, states, commandables, ground_all,
                                                 "ground_all"};

        //Ordered inputs
        /*arm_limit_switch_top_order = new ordered_input{ARM_LIMIT_SWITCH_TOP_ORDER, arm_limit_switch_top};
         arm_limit_switch_bottom_order = new ordered_input{ARM_LIMIT_SWITCH_BOTTOM_ORDER, arm_limit_switch_bottom};
         arm_encoder_order = new ordered_input{ARM_ENCODER_ORDER, arm_encoder};
         elevator_encoder_order = new ordered_input{ELEVATOR_ENCODER_ORDER, elevator_encoder};*/

        inputs.push_back(arm_limit_switch_top);
        inputs.push_back(arm_limit_switch_top);
        inputs.push_back(arm_encoder);
        inputs.push_back(elevator_encoder);

        state_machines.push_back(cap_state_machine);

        cap_subsystem = new subsystem_controller{inputs, state_machines, "cap"};
    }

    void destroy() {
        delete (elevator_motor);
        delete (arm_a_motor);
        delete (arm_b_motor);
        delete (intake_motor);

        delete (arm_limit_switch_bottom);
        delete (arm_limit_switch_top);
        delete (arm_encoder);
        delete (elevator_encoder);

        //delete (intake_action);
        delete (outtake_action);
        //delete(intake_outtake_action);
        //delete(tare_elevator_encoder_action);
        //delete(tare_arm_encoder_action);
        delete (elevator_down_action);
        delete (elevator_zero_action);
        //delete(elevator_high_pos_action);
        delete (arm_a_down_action);
        delete (arm_b_down_action);
        delete (arm_a_zero_action);
        delete (arm_b_zero_action);
        //delete(arm_a_flip_pos_action);
        //delete(arm_b_flip_pos_action);
        //delete(arm_a_angle_pos_action);
        //delete(arm_b_angle_pos_action);
        //delete(arm_a_low_prime_pos_action);
        //delete(arm_b_low_prime_pos_action);
        //delete(arm_a_low_score_pos_action);
        //delete(arm_b_low_score_pos_action);
        //delete(arm_a_high_prime_pos_action);F
        //delete(arm_b_high_prime_pos_action);
        //delete(arm_a_high_score_pos_action);
        //delete(arm_b_high_score_pos_action);

        delete (ground_all);
        delete (ground_elevator);
        delete (ground_arm);
        delete (ground);
        delete (flip);
        delete (angle);
        delete (low_prime);
        delete (low_move);
        delete (low_score);
        delete (high_prime);
        delete (high_move);
        delete (high_score);

        delete (cap_state_machine);

        /*  delete (arm_limit_switch_bottom_order);
          delete (arm_limit_switch_top_order);
          delete (arm_encoder_order);*/
        delete (elevator_encoder);

        delete (cap_subsystem);

    }
}