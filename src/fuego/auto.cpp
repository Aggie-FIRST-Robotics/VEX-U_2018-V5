#include "fuego/auto.h"

namespace AFR::VexU::Fuego::Auto{
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
    state* drive_test = nullptr;
    state* grab_tilted_cap = nullptr;
    state* move_tilted_cap = nullptr;
    state* score_tilted_cap = nullptr;
    state* aim_high_1 = nullptr;
    state* aim_low_1 = nullptr;
    state* end = nullptr;

    void init(){

        auto_controller = new state_controller<auto_meta>{UPDATE_PERIOD, {0, pros::millis() + 14999}, "auto_controller"};

        zero = new state("zero");
        drive_test = new state("drive_test");
        grab_tilted_cap = new state("grab_tilted_cap");
        move_tilted_cap = new state("move_tilted_cap");
        score_tilted_cap = new state("score_tilted_cap");
        aim_high_1 = new state("aim_high_1");
        aim_low_1 = new state("aim_low_1");
        end = new state("end");

        /////Zero
        zero->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
        }));
        zero->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        zero->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::store;
        }),drive_test);
        /////Timeout
        zero->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),drive_test);
        zero->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);


        /////Drive test
        drive_test->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            Drive::drive_machine->maintain_state(Drive::autonomous);
            Drive::auto_drivetrain->auto_drive_dist(-24, -24, 10, 0, auto_controller->get_name());
        }));
        drive_test->set_on_state_exit(std::function<void(state*)>([](state* next_state){
        }));

        drive_test->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),end);

        /////Gram Tilted Cap
        grab_tilted_cap->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 10000;
            Cap::cap_arm->maintain_state(Cap::angled_pickup);
            BallIntake::ball_intake_controller->maintain_state(BallIntake::swallow);
        }));
        grab_tilted_cap->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        grab_tilted_cap->add_transition(std::function<bool()>([](){
            return false;
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
            BallIntake::ball_intake_controller->maintain_state(BallIntake::choke);
        }));
        move_tilted_cap->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            Cap::Arm::pid_controller->set_bounds(12000,-12000);
        }));

        move_tilted_cap->add_transition(std::function<bool()>([](){
            return false;
        }),score_tilted_cap);
        /////Timeout
        move_tilted_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),score_tilted_cap);
        move_tilted_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);

        /////Score Tilted Cap
        score_tilted_cap->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Cap::cap_arm->set_state(Cap::score_prime);
        }));
        score_tilted_cap->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        score_tilted_cap->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::store;
        }),end);
        /////Timeout
        score_tilted_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),end);

        /////Score Tilted Cap
        end->set_on_state_entry(std::function<void(state*)>([](state* prev_state){

        }));
        end->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));


        auto_controller->add_state(zero);
        auto_controller->add_state(drive_test);
        auto_controller->add_state(grab_tilted_cap);
        auto_controller->add_state(move_tilted_cap);
        auto_controller->add_state(score_tilted_cap);
        auto_controller->add_state(end);

        auto_controller->set_state(zero);
    }

    void destroy() {
        
    }
}