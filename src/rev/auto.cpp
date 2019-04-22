#include "rev/auto.h"

namespace AFR::VexU::Rev::Auto{
    /////Commandables
    BaseCommandable::motor_commandable* ball_intake_motor = nullptr;

    /////Readables
    BaseReadable::digital_edge_detector* swallow_button = nullptr;

    /////State Controller
    
    struct auto_meta {
        unsigned int timeout;
        unsigned int end_auto;
    };

    state_controller<auto_meta>* auto_controller = nullptr;

    /////States
    state* zero = nullptr;
    state* grab_ball = nullptr;
    state* move_tilted_cap = nullptr;
    state* prime_tilted_cap = nullptr;
    state* score_tilted_cap = nullptr;
    state* succ_blue_cap = nullptr;
    state* end = nullptr;

    void init(){
        auto_controller = new state_controller<auto_meta>{UPDATE_PERIOD, {0, pros::millis() + 44000}, "auto_controller"};

        //Score Cap #1
        zero = new state("zero");
        grab_ball = new state("grab_ball");
        move_tilted_cap = new state("move_tilted_cap");
        prime_tilted_cap = new state("prime_tilted_cap");
        score_tilted_cap = new state("score_tilted_cap");

        //Score Cap #2
        succ_blue_cap = new state("succ_blue_cap");

        end = new state("end");










        Drive::drive_machine->maintain_state(Drive::autonomous);
        /////Zero
        zero->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
        }));
        zero->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        zero->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::ground;
            // return false;
        }),grab_tilted_cap);
        /////Timeout
        zero->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),grab_tilted_cap);
        zero->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);

        /////Grab Tilted Cap
        grab_tilted_cap->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Cap::cap_arm->maintain_state(Cap::angled_pickup);
            BallIntake::ball_intake_controller->maintain_state(BallIntake::swallow);
            Drive::auto_drivetrain->auto_drive_dist(47, 50, 0, auto_controller->get_name());
        }));
        grab_tilted_cap->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        grab_tilted_cap->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),move_tilted_cap);
        /////Timeout
        grab_tilted_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),move_tilted_cap);
        grab_tilted_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);


        /////Move Tilted Cap
        move_tilted_cap->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Cap::Arm::pid_controller->set_bounds(1000,-1000);
            Cap::cap_arm->set_state(Cap::store);
            Cap::Wrist::pid_controller->set_target(Cap::wrist_flip_target());
            Drive::auto_drivetrain->auto_drive_radius_angle(15.1,Drive::PI*115.0/180.0,75,75,auto_controller->get_name());
        }));
        move_tilted_cap->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            Cap::Arm::pid_controller->set_bounds(12000,-12000);
        }));

        move_tilted_cap->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),prime_tilted_cap);
        /////Timeout
        move_tilted_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),prime_tilted_cap);
        move_tilted_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);

        /////Prime Tilted Cap
        prime_tilted_cap->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Cap::cap_arm->maintain_state(Cap::score_prime);
            Drive::auto_drivetrain->auto_drive_dist(-5, 50, 50, auto_controller->get_name());
        }));
        prime_tilted_cap->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        prime_tilted_cap->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),score_tilted_cap);
        /////Timeout
        prime_tilted_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),score_tilted_cap);

        /////Score Tilted Cap
        score_tilted_cap->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Cap::cap_arm->set_state(Cap::score_prime);

        }));
        score_tilted_cap->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        score_tilted_cap->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::store;
        }),succ_blue_cap);
        /////Timeout
        score_tilted_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),succ_blue_cap);



























        /////Suck Blue Cap
        succ_blue_cap->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            BallIntake::ball_intake_controller->maintain_state(BallIntake::choke);
            Cap::cap_arm->set_state(Cap::ground);
            Drive::auto_drivetrain->auto_drive_radius_angle(FUEGO_WIDTH/2.0 - 1,-Drive::PI*150.0/180.0,60,60,auto_controller->get_name());
            Cap::Wrist::intake_motor->set_value(Cap::INTAKE_VOLTAGE, Cap::cap_arm->get_name());
        }));
        succ_blue_cap->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            Cap::cap_arm->set_state(Cap::angled_pickup);
        }));

        succ_blue_cap->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),slide_to_the_right);
        /////Timeout
        succ_blue_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),slide_to_the_right);

        /////END
        end->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            
        }));
        end->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));




















        auto_controller->add_state(zero);
        auto_controller->add_state(grab_tilted_cap);
        auto_controller->add_state(move_tilted_cap);
        auto_controller->add_state(prime_tilted_cap);
        auto_controller->add_state(score_tilted_cap);
        auto_controller->add_state(succ_blue_cap);
        auto_controller->add_state(slide_to_the_right);
        auto_controller->add_state(cha_cha_real_smooth);
        auto_controller->add_state(end);

        auto_controller->set_state(zero);
    }

    void destroy() {
        
    }
}