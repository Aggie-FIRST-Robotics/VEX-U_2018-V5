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
    state* prime_tilted_cap = nullptr;
    state* score_tilted_cap = nullptr;
    state* suck_blue_cap = nullptr;
    state* slide_to_the_left = nullptr;
    state* slide_to_the_right = nullptr;
    state* charge_second_post = nullptr;
    state* score_second_post = nullptr;
    state* turn_to_aim_1 = nullptr;
    state* aim_high_1 = nullptr;
    state* shoot_high_1 = nullptr;
    state* set_shooter_1 = nullptr;
    state* aim_low_1 = nullptr;
    state* shoot_low_1 = nullptr;
    state* end = nullptr;

    void init(){
        auto_controller = new state_controller<auto_meta>{UPDATE_PERIOD, {0, pros::millis() + 14999}, "auto_controller"};

        zero = new state("zero");
        grab_tilted_cap = new state("grab_tilted_cap");
        move_tilted_cap = new state("move_tilted_cap");
        prime_tilted_cap = new state("prime_tilted_cap");
        score_tilted_cap = new state("score_tilted_cap");
        suck_blue_cap = new state("suck_blue_cap");
        slide_to_the_left = new state("slide_to_the_left");
        slide_to_the_right = new state("slide_to_the_right");
        charge_second_post = new state("charge_second_post");
        score_second_post = new state("score_second_post");
        turn_to_aim_1 = new state("turn_to_aim_1");
        aim_high_1 = new state("aim_high_1");
        shoot_high_1 = new state("shoot_high_1");
        set_shooter_1 = new state("set_shooter_1");
        aim_low_1 = new state("aim_low_1");
        shoot_low_1 = new state("shoot_low_1");
        end = new state("end");
        Drive::drive_machine->maintain_state(Drive::autonomous);

        /////Zero
        zero->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
        }));
        zero->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        zero->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::store;
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
            Drive::auto_drivetrain->auto_drive_radius_angle(15.75,Drive::PI*115.0/180.0,75,75,auto_controller->get_name());
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
        }),suck_blue_cap);
        /////Timeout
        score_tilted_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),suck_blue_cap);

        /////Suck Blue Cap
        suck_blue_cap->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            BallIntake::ball_intake_controller->maintain_state(BallIntake::choke);
            Cap::cap_arm->set_state(Cap::ground);
            Drive::auto_drivetrain->auto_drive_radius_angle(FUEGO_WIDTH/2.0 - 1,-Drive::PI*145.0/180.0,60,60,auto_controller->get_name());
        }));
        suck_blue_cap->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            Cap::cap_arm->set_state(Cap::flip_low);
        }));

        suck_blue_cap->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),slide_to_the_right);
        /////Timeout
        suck_blue_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),slide_to_the_right);

        /////Slide to the left
        slide_to_the_left->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_radius_angle(-20,-Drive::PI*35.0/180.0,70,70,auto_controller->get_name());
        }));
        slide_to_the_left->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            
        }));

        slide_to_the_left->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),slide_to_the_right);
        /////Timeout
        slide_to_the_left->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),slide_to_the_right);

        /////Slide to the right
        slide_to_the_right->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;

            Drive::auto_drivetrain->auto_drive_radius_angle(20,Drive::PI*35.0/180.0,70,70,auto_controller->get_name());
        }));
        slide_to_the_right->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        slide_to_the_right->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),charge_second_post);
        /////Timeout
        slide_to_the_right->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),charge_second_post);

        /////Charge_second_post
        charge_second_post->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            Cap::cap_arm->set_state(Cap::flip_high);
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_dist(-5, 50, 50, auto_controller->get_name());
        }));
        charge_second_post->set_on_state_exit(std::function<void(state*)>([](state* next_state){
             
        }));

        charge_second_post->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete() && Cap::cap_arm->get_current_state() == Cap::store;
        }),score_second_post);
        /////Timeout
        charge_second_post->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),score_second_post);

        /////Score second post
        score_second_post->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Cap::cap_arm->set_state(Cap::score_prime);
        }));
        score_second_post->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        score_second_post->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::store;
        }),turn_to_aim_1);
        /////Timeout
        score_second_post->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),turn_to_aim_1);

        /////Turn to aim 1
        turn_to_aim_1->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_radius_angle(FUEGO_WIDTH/2.0 - 1,-Drive::PI*105.0/180.0,60,0,auto_controller->get_name());
            Shooter::turret_state_controller->maintain_state(Shooter::set_point);
            Shooter::turret_state_controller->metadata().hood_set_point = Shooter::HOOD_HIGH_TARGET;
            Shooter::turret_state_controller->metadata().turret_set_point = Shooter::TURRET_MID_TARGET;
            Shooter::shooter_state_controller->maintain_state(Shooter::spin_up);
        }));
        turn_to_aim_1->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        turn_to_aim_1->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete() && Shooter::Hood::pid->is_in_range(50) && Shooter::Turret::pid->is_in_range(50);
        }),aim_high_1);
        /////Timeout
        turn_to_aim_1->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),aim_high_1);

        /////Aim High 1
        aim_high_1->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Shooter::turret_state_controller->maintain_state(Shooter::auto_aim);
        }));
        aim_high_1->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        aim_high_1->add_transition(std::function<bool()>([](){
            return Shooter::vision->aiming_complete() && Shooter::Flywheel::pid_controller->is_in_range(10);
        }),shoot_high_1);
        /////Timeout
        aim_high_1->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),shoot_high_1);

        /////Shoot High 1
        shoot_high_1->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Shooter::shooter_state_controller->set_state(Shooter::fire);
        }));
        shoot_high_1->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        shoot_high_1->add_transition(std::function<bool()>([](){
            return Shooter::shooter_state_controller->get_current_state() == Shooter::spin_up && Shooter::Loader::dead_band->is_in_range(Shooter::LOADER_TOLERANCE);
        }),set_shooter_1);
        /////Timeout
        shoot_high_1->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),set_shooter_1);

        /////Set Turret 1
        set_shooter_1->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Shooter::turret_state_controller->maintain_state(Shooter::set_point);
            Shooter::turret_state_controller->metadata().hood_set_point = Shooter::HOOD_MID_TARGET;
            Shooter::turret_state_controller->metadata().turret_set_point = Shooter::TURRET_MID_TARGET;
            Shooter::shooter_state_controller->maintain_state(Shooter::spin_up);
        }));
        set_shooter_1->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        set_shooter_1->add_transition(std::function<bool()>([](){
            return Shooter::Hood::pid->is_in_range(50) && Shooter::Turret::pid->is_in_range(50);
        }),aim_low_1);
        /////Timeout
        set_shooter_1->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),aim_low_1);

        /////Aim Low 1
        aim_low_1->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Shooter::turret_state_controller->maintain_state(Shooter::auto_aim);
        }));
        aim_low_1->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        aim_low_1->add_transition(std::function<bool()>([](){
            return Shooter::vision->aiming_complete() && Shooter::Flywheel::pid_controller->is_in_range(10);
        }),shoot_low_1);
        /////Timeout
        aim_low_1->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),shoot_low_1);

        /////Shoot High 1
        shoot_high_1->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Shooter::shooter_state_controller->set_state(Shooter::fire);
        }));
        shoot_high_1->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            Shooter::turret_state_controller->maintain_state(Shooter::manual);
            Shooter::Hood::pid->set_target(0);
            Shooter::Turret::pid->set_target(0);
            Shooter::shooter_state_controller->set_state(Shooter::rest);
        }));

        shoot_high_1->add_transition(std::function<bool()>([](){
            return Shooter::shooter_state_controller->get_current_state() == Shooter::spin_up && Shooter::Loader::dead_band->is_in_range(Shooter::LOADER_TOLERANCE);
        }),end);
        /////Timeout
        shoot_high_1->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),end);

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
        auto_controller->add_state(suck_blue_cap);
        auto_controller->add_state(slide_to_the_left);
        auto_controller->add_state(slide_to_the_right);
        auto_controller->add_state(charge_second_post);
        auto_controller->add_state(end);

        auto_controller->set_state(zero);
    }

    void destroy() {
        
    }
}