#include "robot2/cap/cap.h"
#include "robot2/ball-intake/ball_intake.h"
#include "robot2/drive/drive.h"
#include "robot2/auto.h"

#include "robot2/robot.h"

#include "afr-vexu-lib/auto_state_controller.h"
#include "afr-vexu-lib/base-commandable/multi_motor_commandable.h"
#include "afr-vexu-lib/base-commandable/multi_commandable.h"
#include "afr-vexu-lib/base-readable/motor_encoder_velocity_readable.h"

namespace AFR::VexU::Robot2{
    template<typename T>
    void add_all(std::vector<T> first, std::vector<T> second){
        for(T& val : second){
            first.push_back(val);
        }
    }

    scheduled_update_t timer = 0;

    BaseReadable::motor_encoder_readable* drive_right_encoder, * drive_left_encoder;
    BaseReadable::motor_encoder_velocity_readable* drive_right_velocity, * drive_left_velocity;

    BaseCommandable::multi_motor_commandable* drive_right;
    BaseCommandable::multi_motor_commandable* drive_left;

    BaseAction::pid_action<double, int16_t>* drive_right_pid;
    BaseAction::pid_action<double, int16_t>* drive_left_pid;

    BaseCommandable::multi_commandable<double>* drive_sub_pids;

    BaseAction::pid_action<double, double>* drive_pid;

    state* tare;
    state* drive_forward;
    state* drive_backward;
    state* score_prime;
    state* score;
    state* pull_back;
    state* stop;

    auto_state_controller* auto_state_con;

    subsystem_controller* robot2_auto_subsystem;

    void init_auto(){
        using namespace BaseAction;
        using namespace BaseCommandable;
        using namespace BaseReadable;

        drive_right_encoder = new motor_encoder_readable{RIGHT_RAIL_MOTOR_A_PORT, 1.0, "drive_right_encoder"};
        drive_left_encoder = new motor_encoder_readable{LEFT_RAIL_MOTOR_A_PORT, 1.0, "drive_left_encoder"};

        drive_right = new multi_motor_commandable{"drive_right"};
        drive_right->add_motor(Drive::front_right_motor);
        drive_right->add_motor(Drive::back_right_motor);

        drive_left = new multi_motor_commandable{"drive_left"};
        drive_left->add_motor(Drive::front_left_motor);
        drive_left->add_motor(Drive::back_left_motor);

        drive_right_pid = new pid_action<double, int16_t>{10, drive_right, 100, 0, 0, -3000, 3000, -6000, 6000, 0,
                                                          drive_right_velocity, 0, "drive_right_pid"};
        drive_left_pid = new pid_action<double, int16_t>{10, drive_left, 100, 0, 0, -3000, 3000, -6000, 6000, 0,
                                                         drive_left_velocity, 0, "drive_left_pid"};
        drive_sub_pids = new multi_commandable<double>(0, "drive_sub_pids");
        drive_sub_pids->add_commandable(drive_right_pid);
        drive_sub_pids->add_commandable(drive_left_pid);

        drive_pid = new pid_action<double, double>{10, drive_sub_pids, 1, 0, 0, -100, 100, -50, 50, 0,
                                                   drive_right_encoder, 0, "drive_pid"};

        std::vector<readable*> inputs{};
        add_all(inputs, BallIntake::ball_intake_subsystem->get_inputs());
        add_all(inputs, Cap::cap_subsystem->get_inputs());
        add_all(inputs, Drive::drive_subsystem->get_inputs());

        std::vector<action*> tare_actions{};
        tare_actions.push_back(Cap::arm_zero_action);
        tare_actions.push_back(Cap::elbow_zero_action);
        tare_actions.push_back(Cap::wrist_zero_action);
        tare_actions.push_back(drive_right_pid);
        tare_actions.push_back(drive_left_pid);
        tare_actions.push_back(drive_pid);

        std::vector<action*> pid_actions{};
        pid_actions.push_back(Cap::arm_pid_action);
        pid_actions.push_back(Cap::elbow_pid_action);
        pid_actions.push_back(Cap::wrist_pid_action);
        pid_actions.push_back(drive_right_pid);
        pid_actions.push_back(drive_left_pid);
        pid_actions.push_back(drive_pid);
        pid_actions.push_back(Cap::intake_hold_action);

        std::vector<action*> suck_actions{};
        suck_actions.push_back(Cap::arm_pid_action);
        suck_actions.push_back(Cap::elbow_pid_action);
        suck_actions.push_back(Cap::wrist_pid_action);
        suck_actions.push_back(drive_right_pid);
        suck_actions.push_back(drive_left_pid);
        suck_actions.push_back(drive_pid);
        suck_actions.push_back(Cap::intake_suck_action);

        std::vector<action*> outtake_actions{};
        outtake_actions.push_back(Cap::arm_pid_action);
        outtake_actions.push_back(Cap::elbow_pid_action);
        outtake_actions.push_back(Cap::wrist_pid_action);
        outtake_actions.push_back(drive_right_pid);
        outtake_actions.push_back(drive_left_pid);
        outtake_actions.push_back(drive_pid);
        outtake_actions.push_back(Cap::intake_spit_action);

        auto_state_con = new auto_state_controller{10, std::vector<commandable*>{}, "auto_state_controller"};
        tare = auto_state_con->add_state(
                tare_actions,
                [](state* last_state) -> void{
//                    std::cout << "Got to tare" << std::endl;
                    drive_left_encoder->tare_position();
                    drive_right_encoder->tare_position();
                    timer = pros::millis() + 250;
                },
                "tare",
                []() -> state*{
                    if(pros::millis() >= timer){
                        return drive_forward;
                    }
                    return nullptr;
                }
        );
        drive_forward = auto_state_con->add_state(
                suck_actions,
                [](state* last_state) -> void{
//                    std::cout << "Got to drive_forward" << std::endl;
                    drive_pid->set_target(DRIVE_FORWARD_TARGET);
                    Cap::elbow_pid_action->set_target(Cap::DOWN_ELBOW_TARGET);
                },
                "drive_forward",
                []() -> state*{
                    if(drive_pid->is_in_range(50)){
                        return drive_backward;
                    }
                    return nullptr;
                }
        );
        drive_backward = auto_state_con->add_state(
                pid_actions,
                [](state* last_state) -> void{
//                    std::cout << "Got to drive_backward" << std::endl;
                    drive_pid->set_target(0);
                    Cap::elbow_pid_action->set_target(Cap::HOLD_ELBOW_TARGET);
                },
                "drive_backward",
                []() -> state*{
                    if(drive_pid->is_in_range(50)){
                        return score_prime;
                    }
                    return nullptr;
                }
        );
        score_prime = auto_state_con->add_state(
                pid_actions,
                [](state* last_state) -> void{
                    std::cout << "Got to score_prime" << std::endl;
                    Cap::arm_pid_action->set_target(Cap::SCORE_PRIME_ARM_TARGET);
                    Cap::elbow_pid_action->set_target(Cap::SCORE_PRIME_ELBOW_TARGET);
                },
                "score_prime",
                []() -> state*{
                    if(Cap::arm_pid_action->is_in_range(50) && Cap::elbow_pid_action->is_in_range(50)){
                        return score;
                    }
                    return nullptr;
                }
        );
        score = auto_state_con->add_state(
                pid_actions,
                [](state* last_state) -> void{
                    std::cout << "Got to score" << std::endl;
                    Cap::arm_pid_action->set_target(Cap::SCORE_ARM_TARGET);
                    Cap::elbow_pid_action->set_target(Cap::SCORE_ELBOW_TARGET);
                },
                "score",
                []() -> state*{
                    if(Cap::arm_pid_action->is_in_range(50) && Cap::elbow_pid_action->is_in_range(50)){
                        return pull_back;
                    }
                    return nullptr;
                }
        );
        pull_back = auto_state_con->add_state(
                outtake_actions,
                [](state* last_state) -> void{
                    std::cout << "Got to pull_back" << std::endl;
                    Cap::arm_pid_action->set_target(Cap::PULL_BACK_ARM_TARGET);
                    Cap::elbow_pid_action->set_target(Cap::PULL_BACK_ELBOW_TARGET);
                },
                "pull_back",
                []() -> state*{
                    if(Cap::arm_pid_action->is_in_range(50) && Cap::elbow_pid_action->is_in_range(50)){
                        return stop;
                    }
                    return nullptr;
                }
        );
        stop = auto_state_con->add_state(
                pid_actions,
                [](state* last_state) -> void{
                    std::cout << "Got to stop" << std::endl;
                    Cap::arm_pid_action->set_target(Cap::HOLD_ARM_TARGET);
                    Cap::elbow_pid_action->set_target(Cap::HOLD_ELBOW_TARGET);
                },
                "stop",
                []() -> state*{
                    return nullptr;
                }
        );

        std::vector<state_controller*> state_controllers{};
        state_controllers.push_back(auto_state_con);

        robot2_auto_subsystem = new subsystem_controller{inputs, state_controllers, "robot2_auto_subsystem"};
    }
}
