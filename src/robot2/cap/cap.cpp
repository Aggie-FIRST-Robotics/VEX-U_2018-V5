#include "robot2/cap/cap.h"
#include "robot2/robot.h"

#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "afr-vexu-lib/base-commandable/multi_motor_commandable.h"

#include "afr-vexu-lib/base-readable/adi_digital_readable.h"
#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"
#include "afr-vexu-lib/base-readable/controller_readable.h"

#include "afr-vexu-lib/base-action/zero_encoder_action.h"
#include "afr-vexu-lib/base-action/pid_action.h"

namespace AFR::VexU::Robot2::Cap{
    //Commandables
    BaseCommandable::motor_commandable* left_arm_motor = nullptr;
    BaseCommandable::motor_commandable* right_arm_motor = nullptr;
    BaseCommandable::motor_commandable* elbow_motor = nullptr;
    BaseCommandable::motor_commandable* wrist_motor = nullptr;

    BaseCommandable::multi_motor_commandable* arm_motors = nullptr;

    //Readables
    BaseReadable::adi_digital_readable* arm_limit_switch = nullptr;
    BaseReadable::adi_digital_readable* elbow_limit_switch = nullptr;
    BaseReadable::adi_digital_readable* wrist_limit_switch = nullptr;

    BaseReadable::motor_encoder_readable* arm_encoder = nullptr;
    BaseReadable::motor_encoder_readable* elbow_encoder = nullptr;
    BaseReadable::motor_encoder_readable* wrist_encoder = nullptr;

    BaseReadable::controller_digital_readable* up_button = nullptr;
    BaseReadable::controller_digital_readable* down_button = nullptr;
    BaseReadable::controller_digital_readable* flip_button = nullptr;
    BaseReadable::controller_digital_readable* score_button = nullptr;
    BaseReadable::controller_digital_readable* outtake_button = nullptr;

    //Actions
    BaseAction::zero_encoder_action<bool, int16_t>* arm_zero_action = nullptr;
    BaseAction::zero_encoder_action<bool, int16_t>* elbow_zero_action = nullptr;
    BaseAction::zero_encoder_action<bool, int16_t>* wrist_zero_action = nullptr;

    BaseAction::pid_action<double, int16_t>* arm_pid_action = nullptr;
    BaseAction::pid_action<double, int16_t>* elbow_pid_action = nullptr;
    BaseAction::pid_action<double, int16_t>* wrist_pid_action = nullptr;

    //Action Vectors
    std::vector<action*> storage_actions{};
    std::vector<action*> down_actions{};
    std::vector<action*> straight_up_actions{};
    std::vector<action*> hold_actions{};
    std::vector<action*> score_prime_actions{};
    std::vector<action*> score_actions{};
    std::vector<action*> pull_back_actions{};
    std::vector<action*> outtake_actions{};

    //Transition Functions
    std::function<bool()> storage_to_down{};
    std::function<bool()> storage_to_straight_up{};

    std::function<bool()> down_to_straight_up{};

    std::function<bool()> straight_up_to_storage{};
    std::function<bool()> straight_up_to_hold{};
    std::function<bool()> straight_up_to_outtake{};

    std::function<bool()> hold_to_storage{};
    std::function<bool()> hold_to_straight_up{};
    std::function<bool()> hold_to_score_prime{};
    std::function<bool()> hold_to_outtake{};

    std::function<bool()> score_prime_to_hold{};
    std::function<bool()> score_prime_to_score{};

    std::function<bool()> score_to_score_prime{};
    std::function<bool()> score_to_pull_back{};

    std::function<bool()> pull_back_to_hold{};

    std::function<bool()> outtake_to_straight_up{};

    //Transition Vectors
    std::vector<transition> storage_transitions{};
    std::vector<transition> down_transitions{};
    std::vector<transition> straight_up_transitions{};
    std::vector<transition> hold_transitions{};
    std::vector<transition> score_prime_transitions{};
    std::vector<transition> score_transitions{};
    std::vector<transition> pull_back_transitions{};
    std::vector<transition> outtake_transitions{};

    //On State Entry Functions
    std::function<void(state*)> on_storage_entry{};
    std::function<void(state*)> on_down_entry{};
    std::function<void(state*)> on_straight_up_entry{};
    std::function<void(state*)> on_hold_entry{};
    std::function<void(state*)> on_score_prime_entry{};
    std::function<void(state*)> on_score_entry{};
    std::function<void(state*)> on_pull_back_entry{};
    std::function<void(state*)> on_outtake_entry{};

    //States
    state* storage = nullptr;
    state* down = nullptr;
    state* straight_up = nullptr;
    state* hold = nullptr;
    state* score_prime = nullptr;
    state* score = nullptr;
    state* pull_back = nullptr;
    state* outtake = nullptr;

    //State Vector
    std::vector<state*> states{};

    //Commandable Vector
    std::vector<commandable*> commandables{};

    //State Controller
    state_controller* cap_state_machine = nullptr;

    //Readable Vector
    std::vector<readable*> readables{};

    //State Controller Vector
    std::vector<state_controller*> state_controllers{};

    //Subsystem Controller
    subsystem_controller* cap_subsystem = nullptr;

    void init(){
        using namespace BaseCommandable;
        using namespace BaseReadable;
        using namespace BaseAction;

        //Commandables
        left_arm_motor = new motor_commandable{ARM_LEFT_MOTOR_PORT, ARM_LEFT_GEARSET, false, ARM_LEFT_BRAKE_MODE,
                                               "left_arm_motor"};
        right_arm_motor = new motor_commandable{ARM_RIGHT_MOTOR_PORT, ARM_RIGHT_GEARSET, true, ARM_RIGHT_BRAKE_MODE,
                                                "right_arm_motor"};
        elbow_motor = new motor_commandable{ELBOW_MOTOR_PORT, ELBOW_GEARSET, false, ELBOW_BRAKE_MODE, "elbow_encoder"};
        wrist_motor = new motor_commandable{WRIST_MOTOR_PORT, WRIST_GEARSET, true, WRIST_BRAKE_MODE, "wrist_motor"};

        arm_motors = new multi_motor_commandable{"arm_motors"};
        arm_motors->add_motor(left_arm_motor);
        arm_motors->add_motor(right_arm_motor);

        //Readables
        arm_limit_switch = new adi_digital_readable{ARM_LIMIT_SWITCH_PORT, "arm_limit_switch"};
        elbow_limit_switch = new adi_digital_readable{ELBOW_LIMIT_SWITCH_PORT, "elbow_limit_switch"};
        wrist_limit_switch = new adi_digital_readable{WRIST_LIMIT_SWITCH_PORT, "wrist_limit_switch"};

        arm_encoder = new motor_encoder_readable{ARM_RIGHT_MOTOR_PORT, 1.0, "arm_encoder"};
        elbow_encoder = new motor_encoder_readable{ELBOW_MOTOR_PORT, 1.0, "elbow_encoder"};
        wrist_encoder = new motor_encoder_readable{WRIST_MOTOR_PORT, 1.0, "wrist_encoder"};

        up_button = get_controller_digital_readable(pros::E_CONTROLLER_MASTER, UP_BUTTON);
        down_button = get_controller_digital_readable(pros::E_CONTROLLER_MASTER, DOWN_BUTTON);
        flip_button = get_controller_digital_readable(pros::E_CONTROLLER_MASTER, FLIP_BUTTON);
        score_button = get_controller_digital_readable(pros::E_CONTROLLER_MASTER, SCORE_BUTTON);
        outtake_button = get_controller_digital_readable(pros::E_CONTROLLER_MASTER, OUTTAKE_BUTTON);

        //Actions
        arm_zero_action = new zero_encoder_action<bool, int16_t>{10, arm_motors, arm_limit_switch, arm_encoder, true,
                                                                 -6000, 0, "arm_zero_action"};
        elbow_zero_action = new zero_encoder_action<bool, int16_t>{10, elbow_motor, elbow_limit_switch, elbow_encoder,
                                                                   true, -6000, 0, "elbow_zero_action"};
        wrist_zero_action = new zero_encoder_action<bool, int16_t>{10, wrist_motor, wrist_limit_switch, wrist_encoder,
                                                                   true, -6000, 0, "wrist_zero_action"};

        arm_pid_action = new pid_action<double, int16_t>{10, arm_motors, 100, 0, 0, -12000, 12000, -6000, 6000, 0,
                                                         arm_encoder, 0, "arm_pid_action"};
        elbow_pid_action = new pid_action<double, int16_t>{10, elbow_motor, 100, 0, 0, -12000, 12000, -6000, 6000, 0,
                                                           elbow_encoder, 0, "elbow_pid_action"};
        wrist_pid_action = new pid_action<double, int16_t>{10, wrist_motor, 100, 0, 0, -12000, 12000, -6000, 6000, 0,
                                                           wrist_encoder, 0, "wrist_pid_action"};

        //Action Vectors
        storage_actions.push_back(arm_zero_action);
        storage_actions.push_back(elbow_zero_action);
        storage_actions.push_back(wrist_zero_action);

        down_actions.push_back(arm_pid_action);
        down_actions.push_back(elbow_pid_action);
        down_actions.push_back(wrist_pid_action);

        straight_up_actions.push_back(arm_pid_action);
        straight_up_actions.push_back(elbow_pid_action);
        straight_up_actions.push_back(wrist_pid_action);

        hold_actions.push_back(arm_pid_action);
        hold_actions.push_back(elbow_pid_action);
        hold_actions.push_back(wrist_pid_action);

        score_prime_actions.push_back(arm_pid_action);
        score_prime_actions.push_back(elbow_pid_action);
        score_prime_actions.push_back(wrist_pid_action);

        score_actions.push_back(arm_pid_action);
        score_actions.push_back(elbow_pid_action);
        score_actions.push_back(wrist_pid_action);

        pull_back_actions.push_back(arm_pid_action);
        pull_back_actions.push_back(elbow_pid_action);
        pull_back_actions.push_back(wrist_pid_action);

        outtake_actions.push_back(arm_pid_action);
        outtake_actions.push_back(elbow_pid_action);
        outtake_actions.push_back(wrist_pid_action);

        //Transition Functions
        storage_to_down = []() -> bool{
            return down_button->is_rising_edge();
        };
        storage_to_straight_up = []() -> bool{
            return up_button->is_rising_edge();
        };

        down_to_straight_up = []() -> bool{
            return up_button->is_rising_edge();
        };

        straight_up_to_storage = []() -> bool{
            return down_button->is_rising_edge();
        };
        straight_up_to_hold = []() -> bool{
            return up_button->is_rising_edge();
        };
        straight_up_to_outtake = []() -> bool{
            return outtake_button->is_pressed();
        };

        hold_to_storage = []() -> bool{
            return false;
        };
        hold_to_straight_up = []() -> bool{
            return down_button->is_rising_edge();
        };
        hold_to_score_prime = []() -> bool{
            return up_button->is_rising_edge();
        };
        hold_to_outtake = []() -> bool{
            return outtake_button->is_pressed();
        };

        score_prime_to_hold = []() -> bool{
            return down_button->is_rising_edge();
        };
        score_prime_to_score = []() -> bool{
            return score_button->is_rising_edge();
        };

        score_to_score_prime = []() -> bool{
            return up_button->is_rising_edge();
        };
        score_to_pull_back = []() -> bool{
            return !score_button->is_pressed()
                   && in_range(SCORE_ARM_LOWER_BOUND, arm_encoder->get_position(), SCORE_ARM_UPPER_BOUND)
                   && in_range(SCORE_ELBOW_LOWER_BOUND, elbow_encoder->get_position(), SCORE_ELBOW_UPPER_BOUND);
        };

        pull_back_to_hold = []() -> bool{
            return in_range(PULL_BACK_ARM_LOWER_BOUND, arm_encoder->get_position(), PULL_BACK_ARM_UPPER_BOUND)
                   && in_range(PULL_BACK_ELBOW_LOWER_BOUND, elbow_encoder->get_position(), PULL_BACK_ELBOW_UPPER_BOUND);
        };

        outtake_to_straight_up = []() -> bool{
            return !outtake_button->is_pressed();
        };

        //Transition Vectors
        storage_transitions.emplace_back(storage_to_down, down, "storage_to_down");
        storage_transitions.emplace_back(storage_to_straight_up, straight_up, "storage_to_straight_up");

        down_transitions.emplace_back(down_to_straight_up, straight_up, "down_to_straight_up");

        straight_up_transitions.emplace_back(straight_up_to_storage, storage, "straight_up_to_storage");
        straight_up_transitions.emplace_back(straight_up_to_hold, hold, "straight_up_to_hold");
        straight_up_transitions.emplace_back(straight_up_to_outtake, outtake, "straight_up_to_outtake");

        hold_transitions.emplace_back(hold_to_storage, storage, "hold_to_storage");
        hold_transitions.emplace_back(hold_to_straight_up, straight_up, "hold_to_straight_up");
        hold_transitions.emplace_back(hold_to_score_prime, score_prime, "hold_to_score_prime");
        hold_transitions.emplace_back(hold_to_outtake, outtake, "hold_to_outtake");

        score_prime_transitions.emplace_back(score_prime_to_hold, hold, "score_prime_to_hold");
        score_prime_transitions.emplace_back(score_prime_to_score, score, "score_prime_to_score");

        score_transitions.emplace_back(score_to_score_prime, score_prime, "score_to_score_prime");
        score_transitions.emplace_back(score_to_pull_back, pull_back, "score_to_pull_back");

        pull_back_transitions.emplace_back(pull_back_to_hold, hold, "pull_back_to_hold");

        outtake_transitions.emplace_back(outtake_to_straight_up, straight_up, "outtake_to_straight_up");

        //On State Entry Functions
        on_storage_entry = [](state* last_state) -> void{
            arm_pid_action->disable();
            elbow_pid_action->disable();
            wrist_pid_action->disable();
        };
        on_down_entry = [](state* last_state) -> void{
            arm_pid_action->set_target(DOWN_ARM_TARGET);
            elbow_pid_action->set_target(DOWN_ELBOW_TARGET);
            wrist_pid_action->set_target(0);
        };
        on_straight_up_entry = [](state* last_state) -> void{
            arm_pid_action->set_target(STRAIGHT_UP_ARM_TARGET);
            elbow_pid_action->set_target(STRAIGHT_UP_ELBOW_TARGET);
        };
        on_hold_entry = [](state* last_state) -> void{
            arm_pid_action->set_target(HOLD_ARM_TARGET);
            elbow_pid_action->set_target(HOLD_ELBOW_TARGET);
        };
        on_score_prime_entry = [](state* last_state) -> void{
            arm_pid_action->set_target(SCORE_PRIME_ARM_TARGET);
            elbow_pid_action->set_target(SCORE_PRIME_ELBOW_TARGET);
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

        //States
        storage = new state{storage_actions, storage_transitions, on_storage_entry, "storage"};
        down = new state{down_actions, down_transitions, on_down_entry, "down"};
        straight_up = new state{straight_up_actions, straight_up_transitions, on_straight_up_entry, "straight_up"};
        hold = new state{hold_actions, hold_transitions, on_hold_entry, "hold"};
        score_prime = new state{score_prime_actions, score_prime_transitions, on_score_prime_entry, "score_prime"};
        score = new state{score_actions, score_transitions, on_score_entry, "score"};
        pull_back = new state{pull_back_actions, pull_back_transitions, on_pull_back_entry, "pull_back"};
        outtake = new state{outtake_actions, outtake_transitions, on_outtake_entry, "outtake"};

        //State vector
        states.push_back(storage);
        states.push_back(down);
        states.push_back(straight_up);
        states.push_back(hold);
        states.push_back(score_prime);
        states.push_back(score);
        states.push_back(pull_back);
        states.push_back(outtake);

        commandables.push_back(left_arm_motor);
        commandables.push_back(right_arm_motor);
        commandables.push_back(elbow_motor);
        commandables.push_back(wrist_motor);

        cap_state_machine = new state_controller{10, states, commandables, storage, "cap_state_machine"};

        readables.push_back(arm_limit_switch);
        readables.push_back(elbow_limit_switch);
        readables.push_back(wrist_limit_switch);
        readables.push_back(arm_encoder);
        readables.push_back(elbow_encoder);
        readables.push_back(wrist_limit_switch);

        state_controllers.push_back(cap_state_machine);

        cap_subsystem = new subsystem_controller{readables, state_controllers, "cap_subsystem"};
    }
}
