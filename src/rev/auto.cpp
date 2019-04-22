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
    state* turn_to_low_flag = nullptr;
    state* score_low_flag_1 = nullptr;
    state* back_off_low_flag = nullptr;
    state* turn_to_cap = nullptr;
    state* grab_cap = nullptr;
    state* turn_to_post = nullptr;
    state* go_to_post = nullptr;
    state* score_post = nullptr;
    state* drive_to_plat = nullptr;
    state* turn_to_flag = nullptr;
    state* score_low_flag_2 = nullptr;
    state* line_up = nullptr;
    state* shoot = nullptr;
    state* end = nullptr;

    void init(){
        auto_controller = new state_controller<auto_meta>{UPDATE_PERIOD, {0, pros::millis() + 44000}, "auto_controller"};

        zero = new state("zero");


        grab_ball = new state("grab_ball");
        turn_to_low_flag = new state("turn_to_low_flag");
        score_low_flag_1 = new state("score_low_flag_1");


        back_off_low_flag = new state("back_off_low_flag");
        turn_to_cap = new state("turn_to_cap");
        grab_cap = new state("grab_cap");


        turn_to_post = new state("turn_to_post");
        go_to_post = new state("go_to_post");
        score_post = new state("score_post");


        drive_to_plat = new state("drive_to_plat");
        turn_to_flag = new state("turn_to_flag");
        score_low_flag_2 = new state("score_low_flag_2");


        line_up = new state("line_up");
        shoot = new state("shoot");

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
        }),grab_ball);
        /////Timeout
        zero->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),grab_ball);
        zero->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);













        /////Zero
        grab_ball->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_dist(47, 50, 0, auto_controller->get_name());
        }));
        grab_ball->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        grab_ball->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::ground;
            // return false;
        }),turn_to_low_flag);
        /////Timeout
        grab_ball->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),turn_to_low_flag);
        grab_ball->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);


        /////Zero
        turn_to_low_flag->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_radius_angle(15.1,PI*115.0/180.0,75,75,auto_controller->get_name());
        }));
        zero->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        turn_to_low_flag->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::ground;
            // return false;
        }),score_low_flag_1);
        /////Timeout
        turn_to_low_flag->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),score_low_flag_1);
        turn_to_low_flag->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);

        /////Zero
        score_low_flag_1->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
        }));
        score_low_flag_1->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        score_low_flag_1->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::ground;
            // return false;
        }),back_off_low_flag);
        /////Timeout
        score_low_flag_1->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),back_off_low_flag);
        score_low_flag_1->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);

























        /////Zero
        back_off_low_flag->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
        }));
        back_off_low_flag->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        back_off_low_flag->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::ground;
            // return false;
        }),turn_to_cap);
        /////Timeout
        back_off_low_flag->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),turn_to_cap);
        back_off_low_flag->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);

        /////Zero
        turn_to_cap->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
        }));
        turn_to_cap->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        turn_to_cap->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::ground;
            // return false;
        }),turn_to_cap);
        /////Timeout
        turn_to_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),turn_to_cap);
        turn_to_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);

        /////Zero
        turn_to_cap->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
        }));
        zero->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        turn_to_cap->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::ground;
            // return false;
        }),grab_cap);
        /////Timeout
        turn_to_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),grab_cap);
        turn_to_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);

        /////Zero
        grab_cap->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
        }));
        grab_cap->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        grab_cap->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::ground;
            // return false;
        }),turn_to_post);
        /////Timeout
        grab_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),turn_to_post);
        grab_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);






























        /////Zero
        turn_to_post->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
        }));
        turn_to_post->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        turn_to_post->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::ground;
            // return false;
        }),go_to_post);
        /////Timeout
        turn_to_post->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),go_to_post);
        turn_to_post->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);

        /////Zero
        go_to_post->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
        }));
        go_to_post->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        go_to_post->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::ground;
            // return false;
        }),score_post);
        /////Timeout
        go_to_post->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),score_post);
        go_to_post->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);

        /////Zero
        score_post->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
        }));
        score_post->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        score_post->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::ground;
            // return false;
        }),drive_to_plat);
        /////Timeout
        score_post->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),drive_to_plat);
        score_post->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);





























        /////Zero
        drive_to_plat->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
        }));
        drive_to_plat->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        drive_to_plat->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::ground;
            // return false;
        }),turn_to_flag);
        /////Timeout
        drive_to_plat->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),turn_to_flag);
        drive_to_plat->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);

        /////Zero
        turn_to_flag->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
        }));
        turn_to_flag->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        turn_to_flag->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::ground;
            // return false;
        }),score_low_flag_2);
        /////Timeout
        turn_to_flag->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),score_low_flag_2);
        turn_to_flag->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);

        /////Zero
        score_low_flag_2->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
        }));
        score_low_flag_2->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        score_low_flag_2->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::ground;
            // return false;
        }),line_up);
        /////Timeout
        score_low_flag_2->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),line_up);
        score_low_flag_2->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);





























        /////Zero
        line_up->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
        }));
        line_up->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        line_up->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::ground;
            // return false;
        }),shoot);
        /////Timeout
        line_up->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),shoot);
        line_up->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);

        /////Zero
        shoot->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
        }));
        shoot->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        shoot->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::ground;
            // return false;
        }),grab_ball);
        /////Timeout
        shoot->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),grab_ball);
        shoot->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);











        /////END
        end->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            
        }));
        end->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));








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